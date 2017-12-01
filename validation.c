# include<stdbool.h>
#include "validation.h"
bool validateNegative(int n)
{
    if(n<0) return false;
    else return true;
}

bool vali_date(dateStruct date)
{
    if(date.day<1||date.day>31) return false;
    else if(date.month<1||date.month>12) return false;
    else if (date.year!=2017) return false;
    else return true;
}

char* validate_mail(char* email) {
    for (char* ptr = email; *ptr; ptr++) {
        if (*ptr == '@' && ptr != email) {
            /// check that we saw at least one character
            return ptr+1;
        } else if (*ptr == ' ') { ///email should not have spaces in it
            return 0;
        }
    }
    return 0;
