#pragma once

#include <iostream>
#include <vector>
#include "soccerPlayer.h"

void quickSort(std::vector<SoccerPlayer>& list, int start, int end, bool (*compare)(SoccerPlayer&, SoccerPlayer&, op), op operation);

int partition(std::vector<SoccerPlayer>& list, int start, int end, bool (*compare)(SoccerPlayer&, SoccerPlayer&, op), op operation);