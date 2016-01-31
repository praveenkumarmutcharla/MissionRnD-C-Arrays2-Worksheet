/*
OVERVIEW: You are given a bank statement where transactions are ordered by date. Write a function that finds the number of transactions in that statement after a given date.
-- find the count of numbers greater than a given number in a sorted array.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
date = "19-10-2004"
Output: 1 (as there is only one transaction { 30, "03-03-2005", "Third" })

INPUTS: One bank statement (array of transactions) and date.

OUTPUT: Return the number of transactions in that statement after a given date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/
#include<stdio.h>
#include<string.h>
#include<conio.h>
struct transaction {
	int amount;
	char date[11];
	char description[20];
};
char * reverse(char *str)
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
int strtoint(char *str)
{
	int len, i, inte = 0, counter = 1;
	len = strlen(str);
	reverse(str);
	for (i = 0; i<len; i++)
	{
		inte = inte + ((str[i] - '0')*counter);
		counter = counter * 10;
	}
	return inte;
}
int yearcheck(char *date1, char date2[])
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
	reverse(year1);								//as it storing from left to right
	j = 0;
	intYear1 = strtoint(year1);
	for (i = (int)strlen(date2) - 1; date2[i] != '-'; i--)
	{
		year2[j] = date2[i];
		j++;
	}
	year2[j] = '\0';
	reverse(year2);
	intYear2 = strtoint(year2);
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
int monthcheck(char date1[], char date2[])
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
	Mm1 = strtoint(mm1);
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

	Mm2 = strtoint(mm2);
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
int daycheck(char date1[], char date2[])
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
	Dd1 = strtoint(dd1);
	j = 0;
	for (i = 0; date2[i] != '-'; i++)
	{
		dd2[j] = date2[i];
		j++;
	}
	dd2[j] = '\0';
	j = 0;

	Dd2 = strtoint(dd2);
	if (Dd1 < Dd2)
	{
		return 1;
	}
	return 0;
}
int checkdates(char date1[], char date2[])
{
	int yearflag, monthflag, dayflag;
	yearflag = yearcheck(date1, date2);
	if (yearflag == 2)
		monthflag = monthcheck(date1, date2);
	else if (yearflag == 1)
		monthflag = 1;
	else
		monthflag = 0;
	if (monthflag == 2)
		dayflag = daycheck(date1, date2);
	else if (monthflag == 1)
		dayflag = 1;
	else
		dayflag = 0;

	if (yearflag&&monthflag&&dayflag)
		return 1;
	else
		return 0;
}
int countGreaterNumbers(struct transaction *Arr, int len, char *date) {
	int count = 0, inc = 0, i;
	for (i = 0; i < len; i++)
	{

		if (checkdates(date, Arr[i].date))
			return len - inc;
		else
			inc++;
	}
	return 0;
}

