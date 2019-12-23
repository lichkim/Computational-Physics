#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define dataSize 1000

typedef struct _Node {	//linked list의 Node 구조체
	struct _Node* next;	//다음 노드를 가리키는 포인터
	int data;			//데이터를 담을 변수
} Node;

void addNode(Node* target, int data);	//기준노드 뒤에 노드를 추가하는 함수
void printArr(int* arr);				//배열의 값을 출력하는 함수
void printData(Node* head);				//데이터의 모든 값을 출력하는 함수
int popNextNode(Node* target);			//기준 노드 뒤의 노드를 제거하는 함수. 제거된 노드의 data를 반환한다.
Node* returnBeforeTargetNode(Node* head, int index);		//index 전의 타겟 노드를 반환.
int* shuffleList(Node* head);			//list를 섞은 후, 섞은 결과를 담은 array를 반환하는 함수

int main(void) {
	clock_t start, end;					//프로그램 시간 측정을 위해 사용할 변수
	Node* head = malloc(sizeof(Node));	//머리 노드
	Node* temp;							//리스트를 순회하기 위한 노드
	int i;								//반복문용 변수
	int* result;						//결과값을 담을 배열

	srand((unsigned)time(NULL));		//시드값을 시간에 따라 바꿈
	head->next = NULL;					//머리노드의 next를 null로 지정해줌
	temp = head;						//머리노드 뒤에 노드를 추가하기 위해 temp를 사용

	for (i = 0; i < dataSize; i++) {
		addNode(temp, i + 1);			//head 뒤에 1~dataSize까지의 값을 추가함
		temp = temp->next;				//다음 노드로 넘어감 : temp는 추가한 노드가 됨
	}

	printf("Before Shuffle : \n");
	printData(head);

	start = clock();					//측정 시작
	result = shuffleList(head);
	end = clock();						//측정 종료

	printf("After Shuffle : \n");
	printArr(result);
	printf("Spent Time : %f sec\n", (double)((end - start)/(double)(1000)));	//clock함수는 ms를 기준으로 측정하기 때문에 1000으로 나눠줘야 실제 걸린 시간이 나옴
	free(result);						//shuffleList에서 동적할당한 array를 해제
	free(head);							//필요 없으니 head 역시 해제

	return 0;
}

void printArr(int* arr) {
	int i;					//반복문용 변수
	const int row = 25;		//한 줄에 표시할 숫자의 갯수

	for (i = 0; i < dataSize; i++) {
		if (i%row == 0)		//row만큼의 숫자를 출력함
			printf("\n");
		printf("%4d ", arr[i]);
	}
	printf("\n\n");
}

void printData(Node* head) {
	Node* curr = head->next;	//curr를 head의 다음 노드로 지정함
	const int row = 20;			//한 줄에 표시할 숫자의 갯수
	int i = 0;					//반복문용 변수

	while (curr != NULL) {
		if (i%row == 0)			//row만큼의 숫자를 출력함
			printf("\n");
		i++;
		printf("%4d ", curr->data);
		curr = curr->next;		//curr 노드를 다음 노드로 설정
	}
	printf("\n\n");
	free(curr);					//curr은 이제 필요없으니 해제한다.
}

void addNode(Node* target, int data) {
	Node* newNode = malloc(sizeof(Node));	//새 노드 생성

	newNode->next = target->next;			//새 노드의 next를 기존의 이전 노드의 next로 설정
	newNode->data = data;					//새 노드에 데이터를 할당함

	target->next = newNode;					//이전 노드의 다음 노드를 새 노드로 변경
}

int popNextNode(Node* target) {
	Node* toRemove = target->next;	//target 노드의 다음 노드를 저장. 지울 노드임.
	int out = toRemove->data;		//반환할 결과

	target->next = toRemove->next;	//target 노드의 다음 노드를 지울 노드의 다음 노드로 지정.
	free(toRemove);					//노드 삭제
	return out;						//제거한 노드의 데이터를 반환
}

Node* returnBeforeTargetNode(Node* head, int index) {
	Node* curr = head;			//curr 노드를 head 노드로 지정.
	int i;						//반복문용 변수

	for (i = 0; i < index; i++) {
		curr = curr->next;		//index 직전까지 다음노드로 이동
	}
	return curr;
}

int* shuffleList(Node* head) {
	int* result;		//결과를 담을 배열
	int i;				//반복문용 변수
	int randNum;		//랜덤 숫자

	result = (int*)malloc(sizeof(int)*dataSize);						//result를 dataSize만큼 할당. result[dataSize]로 생각해도 무방.

	for (i = 0; i < dataSize; i++) {
		randNum = rand() % (dataSize - i);								//0~dataSize-i-1까지의 숫자가 생성됨.
		result[i] = popNextNode(returnBeforeTargetNode(head, randNum));	//리스트에선 randNum의 인덱스에 해당하는 노드가 제거되고, 제거된 노드의 데이터는 result[i]에 저장됨.
	}

	return result;
}
