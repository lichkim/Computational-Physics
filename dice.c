#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define diceNum 2
#define tryNum 10000

int main(void) {
	int i, j;
	int sum;
	int result[5 * diceNum + 1] = { 0, };

	printf("~~~~~ R E S U L T ~~~~~\n\n");
	for (i = 0; i < tryNum; i++) {
		sum = 0;
		for (j = 0; j < diceNum; j++) {
			sum += rand() % 6 + 1;
		}
		result[sum - diceNum]++;
	}
	for (i = 0; i < 5 * diceNum + 1; i++) {
		printf("%2d : %2d\n", diceNum + i, result[i]);
	}
	printf("\n");
	return 0;
}
