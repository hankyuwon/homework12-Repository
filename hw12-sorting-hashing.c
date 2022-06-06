#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
int quickSort(int *a, int n);


int hashCode(int key);

int hashing(int *a, int **ht);

int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); // 기존 배열 print
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array); // quicksort 이후 배열 print

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key); // 입력값 key에 저장
			printArray(hashtable); // hashtable 출력
			index = search(hashtable, key); // key값 hashtable에서 index 찾아서 리턴
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a) // 배열 동적 메모리 할당 및 난수 생성
{
	int *temp = NULL;

	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); //(int)*13 만큼의 메모리 동적 할당
		*a = temp;
	} else
		temp = *a;

	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE; // 배열에 난수 넣기

	return 0;
}

int freeArray(int *a) // 배열 메모리 해제
{
	if(a != NULL) // a 가 NULL이 아닐 경우
		free(a); // a 메모리 해제
	return 0;
}

void printArray(int *a) // 배열 print
{
	if (a == NULL) { // a 가 NULL 인 경우
		printf("nothing to print.\n"); // print 할게 없음
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // a[0] ~ a[12] 출력
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // a[0] ~ a[12] 배열 안에 있는 수 출력
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a) // selectionSort
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 기존 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++) // selectionSort 알고리즘
	{
		minindex = i; // 기준점을 i와 a[i]로 잡음
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) // i+1과 a[i+1]부터 MAX_ARRAY_SIZE까지 반복
		{
			if (min > a[j]) // a[j]가 min 보다 작으면
			{
				min = a[j]; // min 과 minindex를 a[j], j로 설정
				minindex = j;
			}
		}
		a[minindex] = a[i]; // a[i]와 a[j] 자리 바꿈
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // SelectionSort 후 배열 print
	return 0;
}

int insertionSort(int *a) // insertionSort
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 기존 배열 print

	for(i = 1; i < MAX_ARRAY_SIZE; i++) // insertionSort 알고리즘
	{
		t = a[i]; // a[i], i 기준
		j = i;
		while (a[j-1] > t && j > 0) // i>0 && a[i-1]>a[i] 일때 반복
		{
			a[j] = a[j-1]; // a[i]와 a[i-1] 바꿈
			j--;
		}
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // insertionSort 이후 배열 print

	return 0;
}

int bubbleSort(int *a) // bubblesort
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 기존 배열 print

	for(i = 0; i < MAX_ARRAY_SIZE; i++) // bubbleSort 알고리즘
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j]) // a[j-1] > a[j]이면
			{
				t = a[j-1]; // 자리바꿈
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // bubblesort 이후 배열 print

	return 0;
}

int shellSort(int *a) // shellsort
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 기존 배열 print

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) // shellsort 알고리즘
	{
		for (i = 0; i < h; i++) // i는 MAX_ARRAY_SIZE/2, MAX_ARRAY_SIZE까지 i++
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) // j는 i+MAX_ARRAY_SIZE/2, MAX_ARRAY_SIZE까지 h+j
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // shellsort 이후 배열 print

	return 0;
}

int quickSort(int *a, int n) // quicksort
{
	int v, t;
	int i, j;

	if (n > 1) // MAX_ARRAY_SIZE > 1
	{
		v = a[n-1]; // v = a[n-1], 즉 right를 pivot로 잡음
		i = -1; // i를 배열의 left
		j = n - 1; // j 를 배열의 right

		while(1) // 반복
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break; // left 가 right 보다 커지면 while문 종료
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i); // a, i 재귀
		quickSort(a+i+1, n-i-1); // a+i+1, n-i-1 재귀
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; // key 값을 MAX_HASH_TABLE_SIZE 만큼의 크기로 나눠준 나머지 return
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	if(*ht == NULL) { // ht 가 NULL 이면
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // 메모리 할당
		*ht = hashtable;
	} else {
		hashtable = *ht;
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1; // hashtable 배열 -1로 초기화

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key); // key 값 hashCode 함수 return 값을 hashcode에 저장

		if (hashtable[hashcode] == -1) // hashtable[hashcode]에 들어온 값이 없으면
		{
			hashtable[hashcode] = key; // hashtable[hashcode] 에 key 부여
		} else 	{ // 만약 이미 hashtable[hashcode]에 들어온 값 있다면

			index = hashcode;

			while(hashtable[index] != -1) // hashtable[hashcode]가 -1이 아닐때 까지 반복
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; // index = (index+1)%MAX_HASH_TABLE_SIZE
			}
			hashtable[index] = key; // hashtable[index] 값에 key값 부여
		}
	}

	return 0;
}

int search(int *ht, int key) // hashtabale 에서 key 값 이 들어있는 index 찾기
{
	int index = hashCode(key); // index = key % MAX_HASH_TABLE_SIZE 부여

	if(ht[index] == key) // 만약 hashtable[index]에 key 값이 있으면
		return index; // index return

	while(ht[++index] != key) // 만약 그렇지 않다면, index 증가시키며 key값 찾기
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index; // 찾은 index 값 return
}


