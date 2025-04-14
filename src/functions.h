#pragma once
#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>
Color background = {173,204,96,255};
Color darkg = {43,51,24,255};

int cellSize=30;
int cellCount=25; 
int offset = 75;
double gameSpeed = 0.2;
double lastUpdateTime=0;
bool ElementInDeque(Vector2 element, std::deque<Vector2> deque)
{
    for (unsigned int i=0;i<deque.size();i++)
    {
        if (Vector2Equals(deque[i],element))
        {
            return true;
        }
    }
    return false;
}

bool eventTriggered(double interval)
{
    double currentTime= GetTime();
    if (currentTime - lastUpdateTime >=interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}
