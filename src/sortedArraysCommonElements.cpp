/*
OVERVIEW: You are given 2 bank statements that are ordered by date. Write a function that returns dates common to both statements
(ie both statements have transactions in these dates).
E.g.: Input: [A3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[3] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" }, { 320, "27-08-2015", "Seventh" } };
Output: { { 10, "09-10-2003", "First" } }
[-=
INPUTS: Two bank statements (array of transactions).

OUTPUT: Transactions having same dates.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>

struct transaction {
	int amount;
	char date[11];
	char description[20];
};
char * reverseMethod(char *str)
{
	int i, len, j;
	char temp;
	for (len = 0; str[len] != '\0'; len++);
	j = len - 1;
	for (i = 0; i<(len / 2); i++)
	{
		//	printf("in loop%d %d\n",i,j);
		if (i == j)
			break;
		//	printf("%d%d\n",i,j);
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		j--;
	}
	return str;
}
int strtoIntmethod(char *str)
{
	int len, i, inte = 0, counter = 1;
	len = strlen(str);
	reverseMethod(str);
	for (i = 0; i<len; i++)
	{
		inte = inte + ((str[i] - '0')*counter);
		counter = counter * 10;
	}
	return inte;
}
int yearCheckmethod(char *date1, char date2[])
{
	char year1[5];
	char year2[5];
	int intYear1, intYear2;
	int i, j = 0;
	for (i = (int)strlen(date1) - 1; date1[i] != '-'; i--)
	{
		year1[j] = date1[i];
		j++;
	}
	year1[j] = '\0';
	reverseMethod(year1);								//as it storing from left to right
	j = 0;
	intYear1 = strtoIntmethod(year1);
	for (i = (int)strlen(date2) - 1; date2[i] != '-'; i--)
	{
		year2[j] = date2[i];
		j++;
	}
	year2[j] = '\0';
	reverseMethod(year2);
	intYear2 = strtoIntmethod(year2);
	if (intYear1<intYear2)
	{
		return 1;
	}
	if (intYear1 == intYear2)
	{
		return 2;
	}
	return 0;
}
int monthCheckmethod(char date1[], char date2[])
{
	char mm1[3], mm2[3];
	int Mm1, Mm2;
	int i, j = 0, k;
	for (i = 0; date1[i] != '\0'; i++)
	{
		if (date1[i] == '-')
		{
			for (k = i + 1; date1[k] != '-'; k++)
			{
				mm1[j] = date1[k];
				j++;
			}
			mm1[j] = '\0';
			break;
		}
	}
	Mm1 = strtoIntmethod(mm1);
	j = 0;
	for (i = 0; date2[i] != '\0'; i++)
	{
		if (date2[i] == '-')
		{
			for (k = i + 1; date2[k] != '-'; k++)
			{
				mm2[j] = date2[k];
				j++;
			}
			mm2[j] = '\0';
			break;
		}
	}

	Mm2 = strtoIntmethod(mm2);
	if (Mm1<Mm2)
	{
		return 1;
	}
	if (Mm1 == Mm2)
	{
		return 2;
	}
	return 0;
}
int dayCheckmethod(char date1[], char date2[])
{
	char dd1[3], dd2[3];
	int Dd1, Dd2;
	int i, j = 0;
	for (i = 0; date1[i] != '-'; i++)
	{
		dd1[j] = date1[i];
		j++;
	}
	dd1[j] = '\0';
	Dd1 = strtoIntmethod(dd1);
	j = 0;
	for (i = 0; date2[i] != '-'; i++)
	{
		dd2[j] = date2[i];
		j++;
	}
	dd2[j] = '\0';
	j = 0;

	Dd2 = strtoIntmethod(dd2);
	if (Dd1 < Dd2)
	{
		return 1;
	}
	if (Dd1 == Dd2)
	{
		return 2;
	}
	return 0;
}
int checkDatesmethod(char date1[], char date2[])
{
	int yearflag, monthflag, dayflag;
	yearflag = yearCheckmethod(date1, date2);
	if (yearflag == 2)
		monthflag = monthCheckmethod(date1, date2);
	else if (yearflag == 1)
		monthflag = 1;
	else
		monthflag = 0;
	if (monthflag == 2)
		dayflag = dayCheckmethod(date1, date2);
	else if (monthflag == 1)
		dayflag = 1;
	else
		dayflag = 0;
	if (yearflag == 2 && monthflag == 2 && dayflag == 2)
		return 2;
	if (yearflag&&monthflag&&dayflag)
		return 1;
	else
		return 0;
}
struct transaction * sortedArraysCommonElements(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	struct transaction *C;
	C = (struct transaction *)malloc((ALen + BLen)*sizeof(struct transaction));
	if (A == nullptr || B == nullptr)
		return NULL;
	//printf("%d%d", sizeof(A[2]), sizeof(C[5]));
	int i = 0, j = 0, k = 0, fvar;
	while (i < ALen)
	{
		while (j < BLen)
		{
			if (checkDatesmethod(A[i].date, B[j].date) == 2)
			{
				C[k].amount = A[i].amount;
				for (fvar = 0; A[i].date[fvar] != '\0'; fvar++)
					C[k].date[fvar] = A[i].date[fvar];
				C[k].date[fvar] = '\0';
				for (fvar = 0; A[i].description[fvar] != '\0'; fvar++)
					C[k].description[fvar] = A[i].description[fvar];
				C[k].description[fvar] = '\0';
				k++;
				j++;
			}
			else
				j++;
		}
		i++;
		j = 0;
	}
	if (k == 0)
		return NULL;
	return C;
	return NULL;
}