#include "InstanceInator.h"
#include "Platform.h"

#if PLATFORM_WINDOWS
#include "Windows/MinWindows.h"
#include <system_error>
#endif

#define MUTEX_NAME "astra_absolut_games_single_instance_mutex"

void UInstanceInator::check_for_multiple_instances()
{

#if PLATFORM_WINDOWS
    const HANDLE mutex_handle = ::CreateMutexA(nullptr, true, MUTEX_NAME);
    const auto last_error = ::GetLastError();

    if (mutex_handle == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Error when trying to create named mutex with name \"") TEXT(MUTEX_NAME) TEXT("\" for single-instance mode. Error: %s"), std::error_code(last_error, std::system_category()).message().c_str());
        return;
    }

    // CreateMutexW might succeed and return a valid mutex handle,
    // but set 'ERROR_ALREADY_EXISTS' as last error,
    // in which case we haven't acquired the mutex
    if (last_error == ERROR_ALREADY_EXISTS)
    {
        CloseHandle(mutex_handle);
        std::exit(0);
    }
#endif

}
