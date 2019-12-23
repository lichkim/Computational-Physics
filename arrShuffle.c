#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define arrSize 1000

int* shuffleArr(int *arr);	//배열을 셔플하는 함수
void printArr(int *arr);	//배열의 모든 원소를 출력하는 함수

int main(void) {
	time_t start, end;	//프로그램이 소요한 시간을 측정하기 위해 사용되는 변수.
	int arr[arrSize];	//1~arrSize까지의 숫자를 담을 배열
	int i;				//반복문용 변수
	int *result;		//결과를 담을 배열

	srand((unsigned)time(NULL));	//시드값을 시간에 따라 변경

	for (i = 0; i < arrSize; i++)	
		arr[i] = i + 1;				//1~arrSize까지의 숫자가 arr에 담김

	printf("Before Shuffle : \n");
	printArr(arr);

	start = clock();		//측정 시작
	result = shuffleArr(arr);
	end = clock();			//측정 종료

	printArr(result);
	printf("\n");
	printf("Spent time : %f sec\n", (double)((end - start)/(double)1000));	//clock함수는 ms단위를 기준으로 측정하기 때문에 실제 걸린 시간은 1000으로 나눠줘야 구할 수 있음
	free(result);			//shuffleArr 밖에서도 shuffleArr 함수 내부에서 동적할당한 포인터가 해제가 된다. result나 shuffeArr에서 할당한 result나 같은 곳을 가리키는 포인터이므로.

	return 0;
}

int* shuffleArr(int* arr) {
	int* result;	//결과를 담을 배열.
	int i,j;		//반복문용 변수
	int randnum;	//랜덤한 숫자를 담을 변수

	result = (int*)malloc(sizeof(int)*arrSize);			//result에 arrSize만큼의 크기를 할당. result[arrSize]처럼 생각해도 됨

	for (i = 0; i < arrSize; i++) {
		randnum = rand() % (arrSize - i);				//처음엔 0~(arrSize-1), 1개가 빠지면 0~(arrSize-2) 까지의 랜덤 숫자를 생성... 이런식으로 계속
		result[i] = arr[randnum];						//랜덤으로 선택되서 배열에서 빠질 원소를 결과에 추가한다.
		for (j = randnum; j < arrSize - i - 1; j++) {	//끝까지 할 필요 없이 i-1 번째 전 까지만 당겨오면 된다.
			arr[j] = arr[j + 1];						//빠진 부분을 비우고 빠진부분 다음의 모든 원소를 한 칸 씩 당겨서 빈자리를 채운다.
		}
	}

	return result;
}

void printArr(int* arr) {
	int i;					//반복문용 변수
	const int row =25;		//한 줄에 표시할 숫자의 갯수

	for(i = 0; i < arrSize; i++) {
		if (i%row == 0)		//row만큼의 숫자를 출력함
			printf("\n");
		printf("%4d ", arr[i]);
	}
	printf("\n");
}
