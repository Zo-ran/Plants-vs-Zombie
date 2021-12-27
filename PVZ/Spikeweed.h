#pragma once
#include "Plant.h"
class Spikeweed : public Plant
{
    friend class SpkwdList;
private:
    double height = 10;
    int dirct = -1;
public:
    Spikeweed(int x, int y);
};

class SpkwdList : public PlantsList
{
public:
    SpkwdList();

    bool Add(int x, int y);

    void DrawBloodStrip(int base);

    double GetHeight(int row, int col);
};

