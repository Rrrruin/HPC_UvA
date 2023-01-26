#ifndef GAME_LIFE_H
#define GAME_LIFE_H


#include <string>
#include <iostream>

namespace hpcGameLife
{

enum CoordinateStatus
{
	COORDINATE_STATUS_ALIVE = 1,
	COORDINATE_STATUS_DEATH,
};

typedef struct {
	CoordinateStatus *Map;
	unsigned long ulMapSideLength;
}HPCGameLifeData;

class HPCGameLife
{

public:
	HPCGameLife(); 
	HPCGameLife(unsigned long ulMapSideLength); 
	HPCGameLife(HPCGameLifeData HPCGameLifeData);
	~HPCGameLife();


public:
	std::string GetLifeMap();
	void SkipOneTime();

private:
	void CreateMap();
	void RandomSetMap();
	int WhetherAlive(unsigned long ulCoordinatesX, unsigned long ulCoordinatesY);

private:
	unsigned long m_ulMapSideLength;
	unsigned long m_ulTime;
	CoordinateStatus *m_mapLife;
	CoordinateStatus *m_mapNextTimeLife;
};


}



#endif


#pragma once
