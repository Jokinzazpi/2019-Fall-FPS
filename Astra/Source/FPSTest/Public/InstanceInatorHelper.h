#include "Platform.h"

#if PLATFORM_WINDOWS

#include "AssertionMacros.h"

#include <string>
#include <system_error>
#include <type_traits>

// Have to include this instead of <Windows.h>. See:
// https://stackoverflow.com/questions/54212677/upgrading-ue4-19-project-to-4-20
#include "Windows/MinWindows.h"

enum class TryLockNamedMutexErrorCode
{
  ok,
  mutex_already_locked,
  windows_error
};

struct WindowsHandle
{
  WindowsHandle() = default;
  FORCEINLINE explicit WindowsHandle(const std::nullptr_t)
  {}

  FORCEINLINE explicit WindowsHandle(const ::HANDLE handle)
    : native_handle(handle)
  {}

  FORCEINLINE bool operator==(const std::nullptr_t) const
  {
    return native_handle == invalid_handle;
  }

  FORCEINLINE bool operator!=(const std::nullptr_t) const
  {
    return !operator==(nullptr);
  }

  FORCEINLINE::HANDLE get() const
  {
    return native_handle;
  }

  FORCEINLINE void operator=(const std::nullptr_t)
  {
    native_handle = invalid_handle;
  }

  WindowsHandle(const WindowsHandle &) = delete;
  WindowsHandle & operator=(const WindowsHandle &) = delete;

  FORCEINLINE WindowsHandle(WindowsHandle && other)
    : native_handle(other.native_handle)
  {
    other.native_handle = invalid_handle;
  }

  FORCEINLINE void operator=(WindowsHandle && other)
  {
    check(this != &other);

    this->~WindowsHandle();

    native_handle = other.native_handle;
    other.native_handle = invalid_handle;
  }

  FORCEINLINE ~WindowsHandle()
  {
    if (*this != nullptr)
      ::CloseHandle(native_handle);
  }

private:
  static constexpr ::HANDLE invalid_handle = INVALID_HANDLE_VALUE;

  ::HANDLE native_handle = INVALID_HANDLE_VALUE;
};

struct MutexHandleDeleter
{
  using pointer = ::HANDLE; // Customization point for std::unique_ptr

  void operator()(const pointer aHandle) const noexcept
  {
    ::CloseHandle(aHandle);
  }
};

struct TryLockNamedMutexResult
{
  TryLockNamedMutexResult(
    const ::HANDLE						mutex,
    const TryLockNamedMutexErrorCode	error_code,
    const ::DWORD						windows_error)
    : m_mutex(mutex)
    , m_error(error_code)
    , m_windows_error(static_cast<int>(windows_error), std::system_category())
  {}

  static_assert(std::is_same<::DWORD, decltype(::GetLastError())>::value, "Unexpected return type from ::GetLastError()");
  static_assert(sizeof(::DWORD) == sizeof(int), "The sizes should match so that 'std::error_code' works with ::GetLastError()");

  WindowsHandle m_mutex;
  TryLockNamedMutexErrorCode m_error;
  std::error_code m_windows_error; // Holds error code returned by ::GetLastError()
};

struct null_terminated_string_tag
{};

namespace detail
{
  inline TryLockNamedMutexResult check_try_lock_named_mutex(const ::HANDLE named_mutex_handle)
  {
    const auto last_error = ::GetLastError();

    if (named_mutex_handle == nullptr)
    {
      return TryLockNamedMutexResult{ nullptr, TryLockNamedMutexErrorCode::windows_error, last_error };
    }

    // CreateMutexW might succeed and return a valid mutex handle,
    // but set 'ERROR_ALREADY_EXISTS' as last error,
    // in which case we haven't acquired the mutex
    if (last_error == ERROR_ALREADY_EXISTS)
    {
      return TryLockNamedMutexResult{ named_mutex_handle, TryLockNamedMutexErrorCode::mutex_already_locked, last_error };
    }

    return TryLockNamedMutexResult{ named_mutex_handle, TryLockNamedMutexErrorCode::ok, last_error };
  }
} // namespace detail

FORCEINLINE TryLockNamedMutexResult try_lock_named_mutex(const wchar_t * mutex_name, const null_terminated_string_tag)
{
  check(mutex_name != nullptr);

  // https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexw
  return ::detail::check_try_lock_named_mutex(::CreateMutexW(nullptr, true, mutex_name));
}

FORCEINLINE TryLockNamedMutexResult try_lock_named_mutex(const char * mutex_name, const null_terminated_string_tag)
{
  check(mutex_name != nullptr);

  // https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexa
  return ::detail::check_try_lock_named_mutex(::CreateMutexA(nullptr, true, mutex_name));
}

FORCEINLINE TryLockNamedMutexResult try_lock_named_mutex(const std::wstring & mutex_name)
{
  return ::try_lock_named_mutex(mutex_name.c_str(), null_terminated_string_tag{});
}

FORCEINLINE TryLockNamedMutexResult try_lock_named_mutex(const std::string & mutex_name)
{
  return ::try_lock_named_mutex(mutex_name.c_str(), null_terminated_string_tag{});
}

#endif // PLATFORM_WINDOWS
