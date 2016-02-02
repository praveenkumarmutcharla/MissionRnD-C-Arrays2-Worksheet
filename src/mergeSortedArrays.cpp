/*
OVERVIEW: You are given 2 bank statements that are ordered by date - Write a function that produces a single merged statement ordered by dates.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[2] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" } };
Output: { { 10, "09-10-2003", "First" }, { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" },  30, "03-03-2005", "Third" }, { 220, "18-01-2010", "Sixth" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Combined statement ordered by transaction date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/
#include<string.h>
#include <stdio.h>
#include<malloc.h>
#include<conio.h>
struct transaction {
	int amount;
	char date[11];
	char description[20];
};
char * reversemethod(char *str)
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
int strtointmethod(char *str)
{
	int len, i, inte = 0, counter = 1;
	len = strlen(str);
	reversemethod(str);
	for (i = 0; i<len; i++)
	{
		inte = inte + ((str[i] - '0')*counter);
		counter = counter * 10;
	}
	return inte;
}
int yearcheckmethod(char *date1, char date2[])
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
	reversemethod(year1);								//as it storing from left to right
	j = 0;
	intYear1 = strtointmethod(year1);
	for (i = (int)strlen(date2) - 1; date2[i] != '-'; i--)
	{
		year2[j] = date2[i];
		j++;
	}
	year2[j] = '\0';
	reversemethod(year2);
	intYear2 = strtointmethod(year2);
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
int monthcheckmethod(char date1[], char date2[])
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
	Mm1 = strtointmethod(mm1);
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

	Mm2 = strtointmethod(mm2);
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
int daycheckmethod(char date1[], char date2[])
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
	Dd1 = strtointmethod(dd1);
	j = 0;
	for (i = 0; date2[i] != '-'; i++)
	{
		dd2[j] = date2[i];
		j++;
	}
	dd2[j] = '\0';
	j = 0;

	Dd2 = strtointmethod(dd2);
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
int checkdatesmethod(char date1[], char date2[])
{
	int yearflag, monthflag, dayflag;
	yearflag = yearcheckmethod(date1, date2);
	if (yearflag == 2)
		monthflag = monthcheckmethod(date1, date2);
	else if (yearflag == 1)
		monthflag = 1;
	else
		monthflag = 0;
	if (monthflag == 2)
		dayflag = daycheckmethod(date1, date2);
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
struct transaction * mergeSortedArrays(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	struct transaction *C;
	C = (struct transaction *)malloc((ALen + BLen)*sizeof(struct transaction));
	if (A == nullptr || B == nullptr)
		return NULL;
	//printf("%d%d", sizeof(A[2]), sizeof(C[5]));
	int i = 0, j = 0, k = 0, fvar;
	while (i < ALen&&j < BLen)
	{
		if (checkdatesmethod(A[i].date, B[j].date) == 2)
		{
			C[k].amount = A[i].amount;
			for (fvar = 0; A[i].date[fvar] != '\0'; fvar++)
				C[k].date[fvar] = A[i].date[fvar];
			C[k].date[fvar] = '\0';
			for (fvar = 0; A[i].description[fvar] != '\0'; fvar++)
				C[k].description[fvar] = A[i].description[fvar];
			C[k].description[fvar] = '\0';
			k++;
			C[k].amount = B[j].amount;
			for (fvar = 0; B[j].date[fvar] != '\0'; fvar++)
				C[k].date[fvar] = B[j].date[fvar];
			C[k].date[fvar] = '\0';
			for (fvar = 0; B[j].description[fvar] != '\0'; fvar++)
				C[k].description[fvar] = B[j].description[fvar];
			C[k].description[fvar] = '\0';
			k++;
			i++;
			j++;
		}
		else if (checkdatesmethod(A[i].date, B[j].date) == 1)
		{
			C[k].amount = A[i].amount;
			for (fvar = 0; A[i].date[fvar] != '\0'; fvar++)
				C[k].date[fvar] = A[i].date[fvar];
			C[k].date[fvar] = '\0';
			for (fvar = 0; A[i].description[fvar] != '\0'; fvar++)
				C[k].description[fvar] = A[i].description[fvar];
			C[k].description[fvar] = '\0';
			k++;
			i++;
		}
		else
		{
			C[k].amount = B[j].amount;
			for (fvar = 0; B[j].date[fvar] != '\0'; fvar++)
				C[k].date[fvar] = B[j].date[fvar];
			C[k].date[fvar] = '\0';
			for (fvar = 0; B[j].description[fvar] != '\0'; fvar++)
				C[k].description[fvar] = B[j].description[fvar];
			C[k].description[fvar] = '\0';
			k++;
			j++;
		}
	}
	while (i < ALen)
	{
		C[k].amount = A[i].amount;
		for (fvar = 0; A[i].date[fvar] != '\0'; fvar++)
			C[k].date[fvar] = A[i].date[fvar];
		C[k].date[fvar] = '\0';
		for (fvar = 0; A[i].description[fvar] != '\0'; fvar++)
			C[k].description[fvar] = A[i].description[fvar];
		C[k].description[fvar] = '\0';
		k++;
		i++;
	}
	while (j < BLen)
	{
		C[k].amount = B[j].amount;
		for (fvar = 0; B[j].date[fvar] != '\0'; fvar++)
			C[k].date[fvar] = B[j].date[fvar];
		C[k].date[fvar] = '\0';
		for (fvar = 0; B[j].description[fvar] != '\0'; fvar++)
			C[k].description[fvar] = B[j].description[fvar];
		C[k].description[fvar] = '\0';
		k++;
		j++;
	}
	//	printf("%s", C[1].date);
	return C;
	return NULL;
}

			
//{ { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" }, { 60, "2-04-2006", "Sixth" } };
