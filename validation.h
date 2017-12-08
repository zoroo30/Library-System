//validates negative input
int validateNegative(int n)
{
    if(n<0) return 0;
    else return 1;
}

int validate_date(int day,int month,int year)
{
    if((day>0&&day<=31) &&  (month>0&&month<=12) && (year>0))
        return 1;
    else
        return 0;
}
