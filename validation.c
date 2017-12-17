#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include "validation.h"
#include "member.h"

bool validateNegative(int n)
{
    if(n<0) return false;
    else return true;
}

bool vali_date(char buffer[]){
  int dd,mm,yyyy;
  int check = sscanf(buffer,"%d/%d/%d",&dd,&mm,&yyyy);
  if(check!=3) return false;//check if sscanf couldn't fill all variables with numbers

  else //validate those numbers entered
  {
      if(dd<0||dd>30) return false;
      else if(mm<0||mm>12) return false;
      else if(yyyy!=2017) return false;
      else return true;
  }
}
bool mobile(){
int phone,start,end;
scanf("  %n%d%n",&start,&phone,&end);
if (end > 0 && (end-start)==11 && phone > 0) return true;
else return false;
}
