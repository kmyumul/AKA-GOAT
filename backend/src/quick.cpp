#include "quick.h"
#include <algorithm>
#include <iostream>

int partition(std::vector<SoccerPlayer>& list, int start, int end, bool (*compare)(SoccerPlayer&, SoccerPlayer&, op), op operation){
    SoccerPlayer pivot = list   .at(end);
    int i = start - 1;
    for (int j = start; j < end; j++) {
        if (compare(list.at(j), pivot, LESS_THAN)) {
            i++;
            SoccerPlayer temp = list.at(i);
            list.at(i) = list.at(j);
            list.at(j) = temp;
        }
    }
    i++;
    SoccerPlayer temp = list.at(i);
    list.at(i) = list.at(end);
    list.at(end) = temp;

    return i;
}

void quickSort(std::vector<SoccerPlayer>& list, int start, int end, bool (*compare)(SoccerPlayer&, SoccerPlayer&, op), op operation){
    if (end <= start) {
        return;
    }
    int pivot = partition(list, start, end, compare, operation);
    quickSort(list, start, pivot - 1, compare, operation);
    quickSort(list, pivot + 1, end, compare, operation);

    return;
}

/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

// #include <stdio.h>
// #include <iostream>
// #include <vector>


// int partition(std::vector<int>& arr, int start, int end) {
//     int pivot = arr[end];
//     int i = start - 1;
//     for (int j = start; j < end; j++) {
//         if (arr[j] < pivot) {
//             i++;
//             int temp = arr[i];
//             arr[i] = arr[j];
//             arr[j] = temp;
//         }
//     }
//     i++;
//     int temp = arr[i];
//     arr[i] = arr[end];
//     arr[end] = temp;
    
//     return i;
// }

// void quicksort(std::vector<int>& arr, int start, int end) {
    
//     if (end <= start){
//         return;
//     }
//     int pivot = partition(arr, start, end);
//     quicksort(arr, start, pivot - 1);
//     quicksort(arr, pivot + 1, end);
    
//     // for (int num: arr) {
//     //     std::cout << num << " ";
//     // }
//     //std::cout << pivot;
//     return;
// }


// int main()
// {
//     //std::vector<int> numsSorted = {1, 2, 3, 4, 5, 6, 7, 8};
//     std::vector<int> numsUnsorted = {5, 3, 7, 4, 8, 1, 2, 6};
//     quicksort(numsUnsorted, 0, numsUnsorted.size() - 1);
//     for (int num: numsUnsorted){
//         std::cout << num << " ";
//     }

//     return 0;
// }