#pragma once

#include <iostream>
#include <vector>
#include "soccerPlayer.h"

#define RUN 8

// insertion sort
void insertionSort(std::vector<SoccerPlayer> &list, int left, int right, bool (*compare)(SoccerPlayer&, SoccerPlayer&, op));

// merge
void merge(std::vector<SoccerPlayer> &list, int left, int mid, int right, bool (*compare)(SoccerPlayer&, SoccerPlayer&, op));

// tim sort
void timSort(std::vector<SoccerPlayer> &list, bool (*compare)(SoccerPlayer&, SoccerPlayer&, op));

// merge sort
void mergeSort(std::vector<SoccerPlayer> &list, int left, int right, bool (*compare)(SoccerPlayer&, SoccerPlayer&, op));