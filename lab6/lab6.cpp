#include <iostream>
#include <random>
#include <fstream>
#include <clocale>

using namespace std;
ofstream file;

extern "C" {void first(int* array, int lenArray, int Xmin, int* arrResalt); 
			void second(int* array, int Xmin, int Xmax, int* LGrInt, int* arr_out); }

void print_first(int Xmin, int Xmax, int* arr) {
	std::cout << endl << "��������� 1 ������: " << std::endl;
	std::cout <<"��������:\t" << "��������:\t" << "���-��:" << std::endl;
	for (int i = Xmin, j = 0; i <= Xmax; i++, j++) {
		std::cout << "   "<<j + 1<<"\t           " << i << "\t           " << arr[j] << std::endl;
	}
}

void print_second(int NInt, int NumRanDat, int*& arr, int*& LGrInt, int*& answer) {
	std::cout << "��������� 2 ������:" << std::endl;
	file << std::endl;
	std::cout << "�����\t" << "����� ��������\t" << "���-��" << std::endl;
	file << "�����\t" << "����� ��������\t" << "���-��" << std::endl;
	for (int i = 0; i < NInt; i++) {
		std::cout << "  " << i + 1 << "\t      " << LGrInt[i] << "\t          " << answer[i] << std::endl;
		file << "  " << i + 1 << "\t      " << LGrInt[i] << "\t          " << answer[i] << std::endl;
	}
}

int main()
{
	int NumRanDat, Xmin, Xmax, NInt;
	setlocale(LC_ALL, "Russian");
	cout << "������� ����� �������: ";
	cin >> NumRanDat;
	while (NumRanDat <= 0 || NumRanDat > 1024 * 16)
	{
		cout << "������ ������������� �������. ������� �������� ��� ���:";
		cin >> NumRanDat;
	}

	cout << "������� �������� ��������� ������� ��������������� ����� �����." << endl;
	cout << "�������: ";
	cin >> Xmin;
	cout << "��������: ";
	cin >> Xmax;
	if (Xmax < Xmin)
	{
		swap(Xmin, Xmax);
		cout << "�������� ����. �������� �������� �������. ������ Xmin = "<< Xmin << ", Xmax = " << Xmax;
	}

	int rangeLen = Xmax - Xmin + 1; //����� ���������
	int* arr = new int[NumRanDat]; //������ ��������� �����
	for (int i = 0; i < NumRanDat; i++)
		arr[i] = Xmin + rand() % rangeLen;

	cout << "�������� ������: ";
	for (int i = 0; i < NumRanDat; i++)
		cout << arr[i] << " ";

	int* arrAnswer = new int[rangeLen] {0};
	first(arr, NumRanDat, Xmin, arrAnswer);
	print_first(Xmin, Xmax, arrAnswer);

	cout << endl << "������� ���������� ����������, �� ������� ����������� �������� ��������� ������� ��������������� ����� �����: ";
	cin >> NInt;
	while (NInt <= 0 || NInt > 24 || NInt>rangeLen)
	{
		cout << "�������� ����. �������� ��� ���: ";
		cin >> NInt;
	}

	int* LGrInt = new int[NInt + 1];  //������ ����� ������ ��� ��������� ��������
	LGrInt[0] = Xmin;
	cout << "������� ����� ������� ���������� ���������: " << endl;
	for (int i = 1; i < NInt; i++)
	{
		std::cin >> LGrInt[i];
		while (LGrInt[i] > Xmax || LGrInt[i] < Xmin) {
			std::cout << "������������ ��������, ���������� ��� ���: ";
			std::cin >> LGrInt[i];
		}
	}
	LGrInt[NInt] = Xmax + 1;

	int* resultArr = new int[NInt] {0}; 
	second(arrAnswer, Xmin, Xmax, LGrInt, resultArr);
	file.open("answer.txt", std::ios_base::out);
	print_second(NInt, NumRanDat, arr, LGrInt, resultArr);
	delete[] arr;
	delete[] LGrInt;
	delete[] resultArr;
	delete[] arrAnswer;
	file.close();
}

