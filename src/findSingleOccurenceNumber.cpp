/*
OVERVIEW: Given an array where every element occurs three times, except one element which occurs only
once. Find the element that occurs once.
E.g.: Input: arr = 12, 1, 12, 3, 12, 1, 1, 2, 3, 3
ouput: 2

INPUTS: Integer array and length of the array.

OUTPUT: Element that occurs only once.

ERROR CASES: Return -1 for invalid inputs.

NOTES:
*/
#include<conio.h>
#include<stdio.h>
int findSingleOccurenceNumber(int *A, int len) {
	int cmpnumptr = 0, i = 0, j = len - 1, count = 0;
	if (A == NULL)
		return -1;
	while (cmpnumptr<len)
	{
		while (i <= j)
		{

			if (A[cmpnumptr] == A[i])
				count++;
			if (A[cmpnumptr] == A[j])
				count++;
			i++;
			j--;
		}
		if (count == 1)
			return A[cmpnumptr];
		i = 0;
		j = len - 1;
		count = 0;
		cmpnumptr++;
	}
	return -1;
}