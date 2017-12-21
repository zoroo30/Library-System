#ifndef VALIDATION_H_INCLUDED
#define VALIDATION_H_INCLUDED

extern char errors[10][150];
extern int errors_number;


int validateNegative(int n);
//int vali_date(dateStruct date);
int validate_mail(char* s);

int validateNegative(int n);
int vali_date(char buffer[]);
int mobile(void);

#endif // VALIDATION_H_INCLUDED
