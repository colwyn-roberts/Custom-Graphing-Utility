#pragma once
#include <iostream>
#include <ctime>
#include <string.h>
#include <vector>
class player {
public:
    std::string username,hero;
    int kills, deaths, assists, solo, head, lastKills, damage, blocked, healing;
    double accuracy;
    bool mvp;
};

class Match {
public:
    uint8_t scoreA, scoreB;
    time_t date;
    int secondsElapsed;
    std::vector<player> Players;
    Match() {
        scoreA = 0;
        scoreB = 0;
        date = 0;
        secondsElapsed = 0;
    }
    Match(uint8_t scoreA, uint8_t scoreB,int secondsElapsed) {
        scoreA = 0;
        scoreB = 0;
        date = 0;
        secondsElapsed = 0;
    }
};