#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int diceNum, tryNum;
	int i, j;
	int* result;
	int sum;

	srand((unsigned)time(NULL));
	while (1) {
		printf("How many dice are you going to use? : ");
		scanf("%d", &diceNum);
		if (diceNum > 0)
			break;
		else
			printf("Wrong input! Please Try again...\n\n");
	}
	while (1) {
		printf("How many times are you going to throw your dice? : ");
		scanf("%d", &tryNum);
		if (tryNum > 0)
			break;
		else
			printf("Wrong input! Please Try again...\n\n");
	}
	result = (int*)malloc(sizeof(int)*(5 * diceNum + 1));
	for (i = 0; i < 5 * diceNum + 1; i++) {
		*(result + i) = 0;
	}

	for (i = 0; i < tryNum; i++) {
		sum = 0;
		for (j = 0; j < diceNum; j++) {
			sum += rand() % 6 + 1;
		}
		result[sum - diceNum]++;
	}

	printf("~~~~~ R E S U L T ~~~~~\n\n");

	for (i = 0; i < 5 * diceNum + 1; i++) {
		printf("%2d : %d\t%f\n", diceNum + i, result[i],result[i]/((float)tryNum));
	}

	free(result);

	return 0;
}
