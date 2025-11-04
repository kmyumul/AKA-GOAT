#include "tim.h"
#include <algorithm>
#include <iostream>

// sorts a list using insertion sort starting from left index to the right index
void insertionSort(std::vector<SoccerPlayer> &list, int left, int right, bool (*compare)(SoccerPlayer&, SoccerPlayer&, op))
{
    for (int i = (left + 1); i <= right; i++)
    {
        SoccerPlayer temp = list.at(i);
        int j = i - 1;

        // insert temp into the sorted list
        // start at the end of the list, and move the value temp left.
        while (j >= left && compare(list.at(j), temp, GREATER_THAN))
        {
            list.at(j+1) = list.at(j);
            j--;
        }
        // place temp into sorted list
        list.at(j + 1) = temp;
    }
}

// combines 2 sub array in list, from left to mid and from right to mid
void merge(std::vector<SoccerPlayer> &list, int left, int mid, int right, bool (*compare)(SoccerPlayer&, SoccerPlayer&, op))
{
    // Array is broken into 2 parts, get both parts of the array
    int len1 = mid - left + 1;
    int len2 = right - mid;
    std::vector<SoccerPlayer> left_arr;
    std::vector<SoccerPlayer> right_arr;
    
    left_arr.reserve(len1);
    right_arr.reserve(len2);

    // get left array
    for (int i = 0; i < len1; i++)
    {
        left_arr.push_back(list.at(left + i));
    }
    
    // get right array
    for (int i = 0; i < len2; i++)
    {
        right_arr.push_back(list.at(mid + 1 + i));
    }

    // merge the 2 sorted sub arrays
    int i = 0;
    int j = 0;
    int k = left;

    while (i < len1 && j < len2)
    {
        // pick one, whichever is less
        if (compare(left_arr.at(i), right_arr.at(j), LESS_THAN_OR_EQUAL))
        {
            list.at(k) = left_arr.at(i);
            i++;
        }
        else
        {
            list.at(k) = right_arr.at(j);
            j++;
        }
        // move to next position
        k++;
    }

    // if one array is emptied but the other isn't, then we need to copy the rest of the elements
    while (i < len1)
    {
        list.at(k) = left_arr.at(i);
        i++;
        k++;
    }

    while (j < len2)
    {
        list.at(k) = right_arr.at(j);
        j++;
        k++;
    }
}

// void timSort(std::vector<SoccerPlayer> &list, bool (*compare)(SoccerPlayer&, SoccerPlayer&, op))
// {
//     // first, run an insertion sort of size RUN across the list
//     for (int i = 0; i < list.size(); i += RUN)
//     {
//         // call insertion sort to either i + RUN or till end of list
//         if ((i + RUN - 1) < (list.size() - 1))
//         {
//             insertionSort(list, i, (i + RUN - 1), compare);
//         }
//         else
//         {
//             insertionSort(list, i, (list.size() - 1), compare);
//         }
//     }

//     // start merging of size RUN until length of the list
//     // each size of RUN is already sorted, so we just need to merge everything
//     for (int size = RUN; size < list.size(); size = 2*size)
//     {
//         for (int left = 0; left < list.size(); left += (2 * size))
//         {
//             int mid = left + size - 1;
//             int right;

//             // right = left + size + size, or end of list
//             if ((left + 2 * size - 1) < (list.size() - 1))
//             {
//                 right = left + 2 * size - 1;
//             }
//             else
//             {
//                 right = list.size() - 1;
//             }

//             // merge left - mid, mid - right
//             if (mid < right)
//             {
//                 merge(list, left, mid, right, compare);
//             }
//         }
//     }
// }

void timSort(std::vector<SoccerPlayer> &list, bool (*compare)(SoccerPlayer&, SoccerPlayer&, op))
{
    // parse through and get the runs
    int start = 0;
    int end;
    while (start < list.size())
    {
        end = start + 1;

        if (compare(list.at(end), list.at(start), LESS_THAN))
        {
            while (end < list.size() && compare(list.at(end), list.at(end-1), LESS_THAN))
            {
                end++;
                if ((end - start) >= RUN)
                {
                    break;
                }
            }
            std::reverse(list.begin() + start, list.begin() + end);
        }
        else
        {
            while (end < list.size() && compare(list.at(end), list.at(end-1), GREATER_THAN_OR_EQUAL))
            {
                end++;
                if ((end - start) >= RUN)
                {
                    break;
                }
            }   
        }

        int run_len = end - start;
        if (run_len < RUN)
        {
            int extend = std::min(start + RUN, (int)list.size());
            insertionSort(list, start, extend-1, compare);
            end = extend;
        }

        start = end;
    }


    // start merging of size RUN until length of the list
    // each size of RUN is already sorted, so we just need to merge everything
    for (int size = RUN; size < list.size(); size = 2*size)
    {
        for (int left = 0; left < list.size(); left += (2 * size))
        {
            int mid = left + size - 1;
            int right;

            // right = left + size + size, or end of list
            if ((left + 2 * size - 1) < (list.size() - 1))
            {
                right = left + 2 * size - 1;
            }
            else
            {
                right = list.size() - 1;
            }

            // merge left - mid, mid - right
            if (mid < right)
            {
                merge(list, left, mid, right, compare);
            }
        }
    }
}

void mergeSort(std::vector<SoccerPlayer> &list, int left, int right, bool (*compare)(SoccerPlayer&, SoccerPlayer&, op))
{
    // size == 1, return
    if (left >= right)
    {
        return;
    }

    // get a midpoint
    int mid = left + (right - left) / 2;

    // split based off mid
    mergeSort(list, left, mid, compare);
    mergeSort(list, mid + 1, right, compare);

    // merge parts back together
    merge(list, left, mid, right, compare);
}

