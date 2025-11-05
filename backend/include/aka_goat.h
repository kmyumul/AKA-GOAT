#pragma once

#include "soccerPlayer.h"

#define TIMEOUT 5000
#define BREAK "-------------------------------------------------------------------------------"

typedef bool (*compare_func)(SoccerPlayer&, SoccerPlayer&, op);

void run();