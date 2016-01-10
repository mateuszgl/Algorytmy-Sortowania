#include<iostream>
#include <time.h>
#include <chrono>
#include <algorithm>
#include <functional>

typedef std::chrono::high_resolution_clock Clock;


using namespace std;
//-----------------------------------------------------------------------
//								Quick Lomuto
int Partition(int A[], int p, int r)
{
	int x = A[r];
	int i = p - 1;
	for (int j = p; j <= r; j++)
		{
			if (A[j] <= x)
			{
				i = i + 1;
				swap(A[i], A[j]);
			}
		}
	if (i < r)
		return i;
	else return i - 1;
}
void quickSort(int A[],int p,int r)
{
	int q;
	if (p < r)
	{
		q = Partition(A, p, r);
		quickSort(A, p, q);
		quickSort(A, q + 1, r);
	}
}
//--------------Hoare-------------
int HoarePartition(int B[], int p, int r) {
	int x = B[p], i = p - 1, j = r + 1;
	while (true) {
		do  j--; while (B[j] > x);
		do  i++; while (B[i] < x);

		if (i < j)
			swap(B[i], B[j]);
		else
			return j;
	}
}
void quickSortHoare(int B[], int p, int r) {

	int q;
	if (p < r)
	{
		q = HoarePartition(B, p, r);
		quickSortHoare(B, p, q);
		quickSortHoare(B, q + 1, r);
	}
}
//-----------------------------------------------------------------------
//								Selection(min)

void SelectionSort(int T[], int size) {
	
	int min;
	
	for (int i = 0; i < size; i++) {
		min = i;
		for (int j = i+1; j <= size; j++) {
			if (T[min] > T[j]) {
				min = j;
			}
		}
		swap(T[i], T[min]);
	}

}

//-----------------------------------------------------------------------
//								Bubble

void BubbleSort(int T[], int size) {
	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - i; j++) {
			if (T[j] > T[j + 1])
				swap(T[j], T[j + 1]);
		}
	}
}
//-----------------------------------------------------------------------
//							Bubble 2
void BubbleSort2(int T[], int size) {
	int pmin = 0, pmax = size - 1, p;

	do
	{
		p = -1;
		for (int i = pmin; i < pmax; i++)
			if (T[i] > T[i + 1])
			{
				swap(T[i], T[i + 1]);
				if (p < 0) pmin = i;
				p = i;
			}
		if (pmin) pmin--;
		pmax = p;
	} while (p >= 0);
}

//-----------------------------------------------------------------------
//								Insertion
void InsertionSort(int T[], int size) {
	
	int key = 0, i;

	for (int j = 1; j <= size; j++) {
		key = T[j];
		i = j-1;
		while ((i >= 0) && (T[i] > key)) {
			T[i + 1] = T[i];
			i--;
			T[i + 1] = key;
			}
		
	}
}

//-----------------------------------------------------------------------
//								Heap
void maxHeapify(int T[], int i, int size) {

	int largest;
	int l = 2 * i, r = (2 * i) + 1;
	if ((l <= size) && (T[l]>T[i]))
		largest = l;
	else largest = i;
	if ((r <= size) && (T[r]>T[largest]))
		largest = r;
	if (largest != i)
	{
		swap(T[i], T[largest]);
		maxHeapify(T, largest, size);
	}
}

void buildMaxHeap(int T[], int size) {
	
	for (int i = (size / 2); i>=0; i--)
		maxHeapify(T, i, size);
}

void Heapsort(int T[],int size) {
	
	buildMaxHeap(T, size);
	for (int i = size; i>0; i--)
	{
		swap(T[i], T[0]);
		size--;
		maxHeapify(T, 0, size);
	}
}

//-----------------------------------------------------------------------
void print(int T[], int size)
{
	for (int i = 0; i <= size; i++)
		cout << T[i] << " ";
	cout << endl;
}

void buildTmp(int T[], int size, int Tmp[]) {
	
	for (int i = 0; i <= size; i++)
		Tmp[i] = T[i];
}

//-----------------------------------------------------------------------

int main()
{
	int T[250000];
	int Tmp[250000];
	int size = 250000-1;

	srand((unsigned int)time(NULL));
	for (int i = 0; i <= size; i++)
		T[i] = (rand() % 250000) + 1;
	
	//-----------------------------------------------------
	//					nieposortowane

	cout << "250 000 liczb" << endl;

	cout << endl << "Nieposortowane:" << endl;

	buildTmp(T, size, Tmp);
	auto qs1 = Clock::now();
	quickSort(Tmp, 0, size);
	auto qs2 = Clock::now();
	cout << "quickSortLomuto :" << chrono::duration_cast<std::chrono::milliseconds>(qs2 - qs1).count() << "ms" << endl;

	buildTmp(T, size, Tmp);
	auto qsh1 = Clock::now();
	quickSortHoare(Tmp, 0, size);
	auto qsh2 = Clock::now();
	cout << "quickSortHoare : " << chrono::duration_cast<std::chrono::milliseconds>(qsh2 - qsh1).count() << "ms" << endl;

	buildTmp(T, size, Tmp);
	auto s1 = Clock::now();
	SelectionSort(Tmp, size);
	auto s2 = Clock::now();
	cout << "selectionSort :  " << chrono::duration_cast<std::chrono::milliseconds>(s2 - s1).count() << "ms" << endl;

	buildTmp(T, size, Tmp);
	auto b1 = Clock::now();
	BubbleSort(Tmp, size);
	auto b2 = Clock::now();
	cout << "bubbleSort :     " << chrono::duration_cast<std::chrono::milliseconds>(b2 - b1).count() << "ms" << endl;

	buildTmp(T, size, Tmp);
	auto b3 = Clock::now();
	BubbleSort2(Tmp, size);
	auto b4 = Clock::now();
	cout << "bubbleSort2 :     " << chrono::duration_cast<std::chrono::milliseconds>(b4 - b3).count() << "ms" << endl;

	buildTmp(T, size, Tmp);
	auto i1 = Clock::now();
	InsertionSort(Tmp, size);
	auto i2 = Clock::now();
	cout << "insertionSort :  " << chrono::duration_cast<std::chrono::milliseconds>(i2 - i1).count() << "ms" << endl;

	buildTmp(T, size, Tmp);
	auto h1 = Clock::now();
	Heapsort(Tmp, size);
	auto h2 = Clock::now();
	cout << "heapSort :       " << chrono::duration_cast<std::chrono::milliseconds>(h2 - h1).count() << "ms" << endl;


	//-----------------------------------------------------
	//					posortowane

	buildTmp(T, size, Tmp);
	sort(Tmp, Tmp + 250000);
	cout <<endl<< "Posortowane:" << endl;
	
	auto qs1p = Clock::now();
	quickSort(Tmp, 0, size);
	auto qs2p = Clock::now();
	cout << "quickSortLomuto :" << chrono::duration_cast<std::chrono::milliseconds>(qs2p - qs1p).count() << "ms" << endl;

	auto qsh1p = Clock::now();
	quickSortHoare(Tmp, 0, size);
	auto qsh2p = Clock::now();
	cout << "quickSortHoare : " << chrono::duration_cast<std::chrono::milliseconds>(qsh2p - qsh1p).count() << "ms" << endl;

	auto s1p = Clock::now();
	SelectionSort(Tmp, size);
	auto s2p = Clock::now();
	cout << "selectionSort :  " << chrono::duration_cast<std::chrono::milliseconds>(s2p - s1p).count() << "ms" << endl;

	auto b1p = Clock::now();
	BubbleSort(Tmp, size);
	auto b2p = Clock::now();
	cout << "bubbleSort :     " << chrono::duration_cast<std::chrono::milliseconds>(b2p - b1p).count() << "ms" << endl;

	auto i1p = Clock::now();
	InsertionSort(Tmp,size);
	auto i2p = Clock::now();
	cout << "insertionSort :  " << chrono::duration_cast<std::chrono::nanoseconds>(i2p - i1p).count() << "ms" << endl;

	auto h1p = Clock::now();
	Heapsort(Tmp, size);
	auto h2p = Clock::now();
	cout << "heapSort :       " << chrono::duration_cast<std::chrono::milliseconds>(h2p - h1p).count() << "ms" << endl;

	//--------------------------------------------------------
	//					Odwrotnie posortowane
	
	sort(T, T + 250000, greater < int >());
	cout << endl << "Odwrotnie posortowane:" << endl;

	buildTmp(T, size, Tmp);
	auto qs1o = Clock::now();
	quickSort(Tmp, 0, size);
	auto qs2o = Clock::now();
	cout << "quickSortLomuto :" << chrono::duration_cast<std::chrono::milliseconds>(qs2o - qs1o).count() << "ms" << endl;

	buildTmp(T, size, Tmp);
	auto qsh1o = Clock::now();
	quickSortHoare(Tmp, 0, size);
	auto qsh2o = Clock::now();
	cout << "quickSortHoare : " << chrono::duration_cast<std::chrono::milliseconds>(qsh2o - qsh1o).count() << "ms" << endl;

	buildTmp(T, size, Tmp);
	auto s1o = Clock::now();
	SelectionSort(Tmp, size);
	auto s2o = Clock::now();
	cout << "selectionSort :  " << chrono::duration_cast<std::chrono::milliseconds>(s2o - s1o).count() << "ms" << endl;

	buildTmp(T, size, Tmp);
	auto b1o = Clock::now();
	BubbleSort(Tmp, size);
	auto b2o = Clock::now();
	cout << "bubbleSort :     " << chrono::duration_cast<std::chrono::milliseconds>(b2o - b1o).count() << "ms" << endl;

	buildTmp(T, size, Tmp);
	auto i1o = Clock::now();
	InsertionSort(Tmp, size);
	auto i2o = Clock::now();
	cout << "insertionSort :  " << chrono::duration_cast<std::chrono::milliseconds>(i2o - i1o).count() << "ms" << endl;

	buildTmp(T, size, Tmp);
	auto h1o = Clock::now();
	Heapsort(Tmp, size);
	auto h2o = Clock::now();
	cout << "heapSort :       " << chrono::duration_cast<std::chrono::milliseconds>(h2o - h1o).count() << "ms" << endl;
	
	cout << endl;

	system("pause");
	return 0;
	
	
}