#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include "members.h"

int search_ID(int ID)
{
    int j=0;
    while(member_array[j].ID!=ID && j<i)
    {
        j++;
    }
    if(member_array[j].ID!=ID) return -1;
    else return j;

}
