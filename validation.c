# include<stdbool.h>
#include "validation.h"
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

int validate_mail(char *s)
{
    int length=strlen(s), ind1=0, ind2=0, ind3=0; 
 
 
    if ( (s[0]<'a') || (s[0]>'z') ) return 0;
    else
    {
    for (int i=1;i<length;i++)
    {
        if (s[i]=='@')
        {   
            ind1=i+1;
            break;
        }
        else
            if ( (s[i]<'a') || (s[i]>'z') ) return 0;
    }
 
 
    for (int j=ind1;j<length;j++)
    {
        if (s[j]=='.')
        {   
            ind2=j+1;
            break;
        }
        else
            if ( (s[j]<'a') || (s[j]>'z') ) return 0;
    }
 
 
    for (int k=ind2;k<length;k++)
    {
        if (s[k]=='.')
        {   
            ind3=k+1;
            break;
        }
        else
            if ( (s[k]<'a') || (s[k]>'z') ) return 0;
    }
    }
 
 
    if (s[ind3] == 'i' && s[ind3+1] == 'l') return 1;
    else return 0;
}
