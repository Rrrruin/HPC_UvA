#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "HPCGameLife.h"

#define DEFAULT_MAPSIDELENGTH (10)

namespace hpcGameLife
{

HPCGameLife::HPCGameLife()
{
	m_ulMapSideLength = DEFAULT_MAPSIDELENGTH;
	m_ulTime = 0;
	m_mapLife = 0;
	CreateMap();
	RandomSetMap();
}

HPCGameLife::~HPCGameLife()
{
	if (m_mapLife)
	{
		free(m_mapLife);
	}
	if (m_mapNextTimeLife)
	{
		free(m_mapNextTimeLife);
	}
}


std::string HPCGameLife::GetLifeMap()
{
	std::string Map;
	// print coordinates of the Map
	for (unsigned long i = 0; i < m_ulMapSideLength; i++)
	{
		char buf[10] = { 0 };
		snprintf(buf, sizeof(buf), "%02lu ", i + 1);
		Map += buf;
	}
	Map += "\n";
	for (unsigned long i = 0; i < m_ulMapSideLength; i++)
	{
		char buf[10] = { 0 };
		snprintf(buf, sizeof(buf), "___");
		Map += buf;
	}
	Map += "\n";
	for (unsigned long i = 0; i < m_ulMapSideLength * m_ulMapSideLength; i++)
	{
		unsigned long ulCoordinatesNodeX = 0, ulCoordinatesNodeY = 0;

		ulCoordinatesNodeY = (i + 1) / m_ulMapSideLength + (0 == (i + 1) % m_ulMapSideLength ? 0 : 1);
		ulCoordinatesNodeX = (i + 1) - m_ulMapSideLength * (ulCoordinatesNodeY - 1);

		switch (m_mapLife[i])
		{
		case COORDINATE_STATUS_ALIVE:
			Map += "X  ";
			break;
		case COORDINATE_STATUS_DEATH:
			Map += "   ";
			break;
		}
		if (0 == (i+1) % m_ulMapSideLength && 0 != i)
		{
			char buf[10] = { 0 };
			snprintf(buf, sizeof(buf), "| %02lu\n", ulCoordinatesNodeY);
			Map += buf;
		}
	}
	return Map;
}

int HPCGameLife::WhetherAlive(unsigned long ulCoordinatesX, unsigned long ulCoordinatesY)
{
	if (ulCoordinatesX <= 0 || ulCoordinatesX > m_ulMapSideLength ||
		ulCoordinatesY <= 0 || ulCoordinatesY > m_ulMapSideLength)
	{
		return 0;
	}

	unsigned long site = ((ulCoordinatesY - 1) * m_ulMapSideLength) + (ulCoordinatesX - 1);


	return m_mapLife[site] == COORDINATE_STATUS_ALIVE ? 1 : 0;
}



void HPCGameLife::SkipOneTime()
{
	for (unsigned long i = 0; i < m_ulMapSideLength * m_ulMapSideLength; i++)
	{
		unsigned int uiAliveNum = 0;
		unsigned long ulCoordinatesNodeX = 0, ulCoordinatesNodeY = 0;

		ulCoordinatesNodeY = (i + 1) / m_ulMapSideLength + ( 0 == (i + 1) % m_ulMapSideLength ? 0 : 1);
		ulCoordinatesNodeX = (i + 1) - m_ulMapSideLength * (ulCoordinatesNodeY - 1);


		// Survival number of surrounding cells 
		uiAliveNum += WhetherAlive(ulCoordinatesNodeX + 1, ulCoordinatesNodeY);
		uiAliveNum += WhetherAlive(ulCoordinatesNodeX - 1, ulCoordinatesNodeY);
		uiAliveNum += WhetherAlive(ulCoordinatesNodeX, ulCoordinatesNodeY + 1);
		uiAliveNum += WhetherAlive(ulCoordinatesNodeX + 1, ulCoordinatesNodeY + 1);
		uiAliveNum += WhetherAlive(ulCoordinatesNodeX - 1, ulCoordinatesNodeY + 1);
		uiAliveNum += WhetherAlive(ulCoordinatesNodeX, ulCoordinatesNodeY - 1);
		uiAliveNum += WhetherAlive(ulCoordinatesNodeX + 1, ulCoordinatesNodeY - 1);
		uiAliveNum += WhetherAlive(ulCoordinatesNodeX - 1, ulCoordinatesNodeY - 1);
		if (uiAliveNum == 3)
		{
			m_mapNextTimeLife[i] = COORDINATE_STATUS_ALIVE;
		}
		else if (2 <= uiAliveNum && 3 > uiAliveNum && m_mapLife[i] == COORDINATE_STATUS_ALIVE)
		{
			m_mapNextTimeLife[i] = COORDINATE_STATUS_ALIVE;
		}
		else
		{
			m_mapNextTimeLife[i] = COORDINATE_STATUS_DEATH;
		}
	}
	CoordinateStatus *pmapLife = m_mapNextTimeLife;
	m_mapNextTimeLife = m_mapLife;
	m_mapLife = pmapLife;
}

void HPCGameLife::CreateMap()
{
	m_mapLife = (CoordinateStatus *)calloc(m_ulMapSideLength, m_ulMapSideLength * sizeof(CoordinateStatus));
	m_mapNextTimeLife = (CoordinateStatus *)calloc(m_ulMapSideLength, m_ulMapSideLength * sizeof(CoordinateStatus));
}

void HPCGameLife::RandomSetMap()
{
	CoordinateStatus status[] = { COORDINATE_STATUS_ALIVE, COORDINATE_STATUS_DEATH };
	int statusSize = sizeof(status) / sizeof(CoordinateStatus);
	
	srand((unsigned)time(NULL));
	for (unsigned long i = 0; i < m_ulMapSideLength * m_ulMapSideLength; i++)
	{
		m_mapLife[i] = status[rand() % statusSize];
	}
}


}