// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveSystem.h"

Wave::Wave(unsigned minion, unsigned exp_minion, unsigned grunts, unsigned tanks, unsigned flying) : 
	m_number_of_minions(minion), m_number_of_exp_minions(exp_minion), m_number_of_grunts(grunts), m_number_of_tanks(tanks), m_number_of_flying(flying)
{

}

unsigned Wave::get_number_of_minions()
{
	return m_number_of_minions;
}

unsigned Wave::get_number_of_exp_minions()
{
	return m_number_of_exp_minions;
}

unsigned Wave::get_number_of_grunts()
{
	return m_number_of_grunts;
}

unsigned Wave::get_number_of_tanks()
{
	return m_number_of_tanks;
}

unsigned Wave::get_number_of_flying()
{
	return m_number_of_flying;
}

void Wave::set_number_of_minions(unsigned number)
{
	m_number_of_minions = number;
}

void Wave::set_number_of_exp_minions(unsigned number)
{
	m_number_of_exp_minions = number;
}

void Wave::set_number_of_grunts(unsigned number)
{
	m_number_of_grunts = number;
}

void Wave::set_number_of_tanks(unsigned number)
{
	m_number_of_tanks = number;
}

void Wave::set_number_of_flying(unsigned number)
{
	m_number_of_flying = number;
}


WaveSystem::WaveSystem()
{
	m_waves.reserve(m_max_number_of_waves);

	for (unsigned i = 0; i < m_max_number_of_waves; i++)
	{
		unsigned aux_wave = i + 1;
		unsigned number_enemies = pow(aux_wave, 1.5f);
		m_waves[i] = Wave(number_enemies, number_enemies, number_enemies, number_enemies, number_enemies);
	}
	m_actual_wave = m_waves[m_wave_number];
}

WaveSystem::~WaveSystem()
{
}

void WaveSystem::new_wave_started()
{
	m_wave_number++;
	m_actual_wave = m_waves[m_wave_number];
}

bool WaveSystem::has_new_wave_started()
{
	if (m_actual_wave.get_number_of_minions() <= 0 && m_actual_wave.get_number_of_exp_minions() <= 0
		&& m_actual_wave.get_number_of_grunts() <= 0 && m_actual_wave.get_number_of_tanks() <= 0
		&& m_actual_wave.get_number_of_flying() <= 0)
	{
		return true;
	}
	return false;
}
