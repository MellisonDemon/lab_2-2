#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>
#include <chrono>
using namespace std;
using namespace chrono;

struct list
{
	int data;
	list *next; // указатель на следующий элемент
	list *prev; // указатель на предыдущий элемент
};

int printList(list*& first)
{
	list* curr = first;
	while (curr) {
		cout << curr->data << " ";
		curr = curr->next;
	}
	cout << "\n\n";
	return 0;
}

list* listElemIndex(list* curr, int index, bool err_msg = true)
{
	while (curr && (index--))
		curr = curr->next;
	if (err_msg && !curr)
		cout << "ОШИБКА";
	return curr;
}

list* listElemValue(list* curr, int &value, bool err_msg = true)
{
	while (curr && curr->data != value)
		curr = curr->next;
	if (err_msg && !curr)
		cout << "ОШИБКА";
	return curr;
}

list* takeElem(list*& first, int &idx, bool print = false)
{
	list* curr = 0;
	cout << "\n1. По значению\n2. По индексу\n";
	int value;
	string answer;
	cin >> answer;
	value = stoi(answer);
	if (value == 1) {
		cout << "Введите значение: ";
		cin >> answer;
		value = stoi(answer);
		curr = listElemValue(first, value);
		list* idx_search = first;
		idx = 0;
		while (idx_search && idx_search != curr) {
			idx++;
			idx_search = idx_search->next;
		}
	}
	else if (value == 2) {
		cout << "Введите индекс: ";
		cin >> answer;
		idx = stoi(answer);
		curr = listElemIndex(first, idx);
	}
	else  cout << "ОШИБКА";
	if (print && curr)
		cout << "Ваш элемент: " << curr->data << "\n";
	return curr;
}

int deleteList(list* &first)
{
	list* next;
	while (first)
	{
		next = first->next;
		delete first;
		first = next;;
	}
	return 0;
}

int createList(list* &first, list*& last, unsigned n)
{
	list* curr = 0, *next = 0;
	deleteList(first);
	for (unsigned i = 0; i < n; i++) {
		curr = new list;
		curr->data = rand() % 100;
		curr->next = next;
		if (next) {
			next->prev = curr;
		}
		else
			last = curr;
		next = curr;
	}
	curr->prev = nullptr;
	first = curr;
	return 0;
}

int createMain(list*& first, list*& last, int& n, int* &arr)
{
	system_clock::time_point begin = system_clock::now();
	createList(first, last, n);
	system_clock::time_point end = system_clock::now();
	duration<double> time = end - begin;
	begin = system_clock::now();
	int* array = new int[n];
	list* curr = first;
	for (int i = 0; i < n; ++i, curr = curr->next) {
		array[i] = curr->data;
	}
	delete[]arr;
	arr = array;
	end = system_clock::now();
	cout << "\nУшло времени на создание списка: " << time.count() << " мс\n";
	cout << "Array: " << (end - begin).count() << " мс\n";
	return 0;
}

int pushFirst(list* &curr, list* &first, list* &last)
{
	curr->prev = nullptr;
	curr->next = nullptr;
	first = curr;
	last = curr;
	return 0;
}

int pushLast(list* &curr, list* & last)
{
	curr->prev = last;
	last->next = curr;
	last = curr;
	last->next = nullptr;
	return 0;
}

int enterList(list*& first, list*& last, int& n)
{
	n = 0;
	list* p;
	deleteList(first);
	string theDatas, number;
	cin.ignore();
	cout << "Введите элементы: ";
	getline(cin, theDatas);
	for (int i = 0; i <= theDatas.length(); i++) {
		if (theDatas[i] != ' ' && theDatas[i] != '\0') {
			number += theDatas[i];
		}
		else {
			list* p = new list;
			n++;
			p->data = stoi(number);
			if (first == nullptr) {
				pushFirst(p, first, last);
			}
			else {
				pushLast(p, last);
			}
			number.erase(0, number.length());

		}
	}
	return 0;
}

void insertToArray(int* &arr, int &n, const int &idx, const int &value)
{
	if (idx > n || idx < -1) return;
	int* arr_new = new int[++n];
	int i = 0;
	for (i; i <= idx; ++i) {
		arr_new[i] = arr[i];
	}
	if (idx == -1) arr_new[i] = value;
	else arr_new[i] = value;
	for (++i; i < n; ++i) {
		arr_new[i] = arr[i - 1];
	}
	delete[]arr;
	arr = arr_new;
}

int enterArray(int* &arr, list* first, int &n) {
	int* array = new int[n];
	list* curr = first;
	string imitation;
	cout << "Введите любое число: ";
	getline(cin, imitation);
	for (int i = 0; i < n && curr; ++i, curr = curr->next) {
		array[i] = curr->data;
	}
	delete[]arr;
	arr = array;
	return 0;
}

int enterMain(list* &first, list* &last, int* &arr, int &n)
{
	system_clock::time_point begin = system_clock::now();
	enterList(first, last, n);
	system_clock::time_point end = system_clock::now();
	duration<double> time = end - begin;
	begin = system_clock::now();
	enterArray(arr, first, n);
	end = system_clock::now();
	cout << "\nУшло времени на создание списка: " << time.count() << " мс\n";
	cout << "Array: " << (end - begin).count() << " мс\n";
	return 0;
}

void insertToList(list*& first, list*& last, const int &idx, const int &val)
{
	list* curr_1 = 0, *curr_2 = new list;
	curr_2->data = val;
	if (idx == -1) {
		if (!first)
			pushFirst(curr_2, first, last);
		else {
			first->prev = curr_2;
			curr_2->next = first;
			curr_2->prev = nullptr;
			first = curr_2;
		}
		return;
	}
	curr_1 = listElemIndex(first, idx);
	if (!curr_1) return;;
	if (curr_1 == last) {
		pushLast(curr_2, last);
	}
	else {
		curr_1->next->prev = curr_2;
		curr_2->next = curr_1->next;
		curr_1->next = curr_2;
		curr_2->prev = curr_1;

	}
}

int insertMain(list* &first, list* &last, int* &arr, int &n)
{
	int idx, val;
	string answer;
	cout << "\nПосле какого элемента вставить данный элемент (0, если нужно вставить первым)?: ";
	cin >> answer;
	idx = stoi(answer);
	idx = idx - 1;
	cout << "\nВведите значение данного элемента: ";
	cin >> answer;
	val = stoi(answer);
	system_clock::time_point begin = system_clock::now();
	insertToList(first, last, idx, val);
	system_clock::time_point end = system_clock::now();
	duration<double> time = end - begin;
	begin = system_clock::now();
	insertToArray(arr, n, idx, val);
	end = system_clock::now();
	cout << "\nВремя, потраченное на вставку: " << time.count() << " мс\n";
	cout << "\nArray: " << (end - begin).count() << " мс\n";
	return 0;
}

void deleteArray(int* &arr, int &n, const int &idx)
{
	if (idx >= n || idx < 0) return;
	if (n == 0)return;
	int* arr_new = new int[--n];
	int i;
	for (i = 0; i < idx; ++i) {
		arr_new[i] = arr[i];
	}
	for (i = idx; i < n; ++i) {
		arr_new[i] = arr[i + 1];
	}
	delete[]arr;
	arr = arr_new;
}

void deleteCurr(list*& first, list* &last, int &idx)
{
	list* curr = 0;
	curr = takeElem(first, idx);
	if (!curr) {
		cout << "List item not found\n";
		idx = -1;
		return;
	}
	if (curr == first) {
		if (!first->next) {
			first = nullptr;
			cout << "List item deleted\nThe list is empty\n";
			return;
		}
		curr = first->next;
		delete first;
		curr->prev = nullptr;
		first = curr;
		return;
	}
	if (curr == last) {
		curr = last->prev;
		delete last;
		curr->next = nullptr;
		last = curr;
		return;
	}
	if (curr) {
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		delete curr;
		return;
	}
}

int deleteMain(int* &arr, int &n, list*& first, list*& last)
{
	system_clock::time_point begin = system_clock::now();
	int idx = -2;
	deleteCurr(first, last, idx);
	system_clock::time_point end = system_clock::now();
	duration<double> time = end - begin;
	begin = system_clock::now();
	deleteArray(arr, n, idx);
	end = system_clock::now();
	cout << "Время, ушедшее на удаление элемента: " << time.count() << " мс\n";
	cout << "Array: " << (end - begin).count() << " мс\n";
	return 0;
}

void exchangeCurr(list* &first, list* &last, const int& index_1, const int& index_2)
{
	list* p_1, *p_2;
	list* p_mem = new list;
	p_1 = listElemIndex(first, index_1);
	p_2 = listElemIndex(first, index_2);
	if (!p_1 || !p_2) return;
	if (p_1->next == p_2) {
		p_mem->next = p_2->next;
		p_2->next = p_1;
		p_2->prev = p_1->prev;
		p_1->next = p_mem->next;
		p_1->prev = p_2;
		if (p_1->next != nullptr) {
			p_1->next->prev = p_1;
		}
		if (p_2->prev != nullptr) {
			p_2->prev->next = p_2;
		}
	}
	else if (p_2->next == p_1) {
		p_mem->next = p_1->next;
		p_1->next = p_2;
		p_1->prev = p_2->prev;
		p_2->next = p_mem->next;
		p_2->prev = p_1;
		if (p_2->next != nullptr) {
			p_2->next->prev = p_2;
		}
		if (p_1->prev != nullptr) {
			p_1->prev->next = p_1;
		}
	}
	else {
		if (p_1 != first)
			p_1->prev->next = p_2;
		p_mem->next = p_2->next;
		p_2->next = p_1->next;
		if (p_2 != first)
			p_2->prev->next = p_1;
		p_1->next = p_mem->next;
		p_mem->prev = p_2->prev;
		p_2->prev = p_1->prev;
		p_1->prev = p_mem->prev;
		if (p_1->next != nullptr)
			p_1->next->prev = p_1;
		if (p_2->next != nullptr)
			p_2->next->prev = p_2;
	}
	if (p_1->prev == nullptr)
		first = p_1;
	if (p_2->prev == nullptr)
		first = p_2;
}

int exchangeMain(int*& arr, const int& n, list*& first, list*& last)
{
	int index_1, index_2;
	string answer;
	system_clock::time_point begin = system_clock::now();
	cout << "Введите индексы элементов, которые требуется обменять: ";
	cin >> answer;
	index_1 = stoi(answer);
	cin >> answer;
	index_2 = stoi(answer);
	exchangeCurr(first, last, index_1, index_2);
	system_clock::time_point end = system_clock::now();
	duration<double> time = end - begin;
	begin = system_clock::now();
	if (index_1 < n && index_2 < n)
		swap(arr[index_1], arr[index_2]);
	end = system_clock::now();
	cout << "Время, ушедшее на перестановку: " << time.count() << " мс\n";
	cout << "Array: " << (end - begin).count() << " мс\n";
	return 0;
}

int takeElemMain(int*& arr, const int& n, list*& first)
{
	system_clock::time_point begin = system_clock::now();
	int found, idx = -1;
	takeElem(first, idx, 1);
	system_clock::time_point end = system_clock::now();
	duration<double> time = end - begin;
	begin = system_clock::now();
	if (idx >= 0 && idx < n) {
		found = arr[idx];
		cout << found << "\n";
	}
	end = system_clock::now();
	cout << "Затрачено времени на поиск: " << time.count() << " мс\n";
	cout << "Array: " << (end - begin).count() << " мс\n";
	return 0;
}

int menu(list*& first, list*& last, int* &arr, int &n)
{
	int countOfDatas = 0, switcher, switcher2, okay = 0;

	while (true)
	{
		cout << "\nВыберите действие:\n1.Создать двусвязный список\n2.Вставка элемента\n3.Удалить элемент\n4.Обмен элементов\n5.Получить элемент\n";
		cin >> switcher;
		switch (switcher)
		{
		case 1:
			cout << "\n1.Создать рандомный список заданной длинны.\n2.Ввести список с клвиатуры\n";
			cin >> switcher2;
			switch (switcher2)
			{
			case 1:
				cout << "\nКакой длинны Вы желаете создать массив?" << endl;
				cin >> countOfDatas;
				n = countOfDatas;
				createMain(first, last, n, arr);
				printList(first);
				okay = 1;
				break;
			case 2:
				enterMain(first, last, arr, n);
				printList(first);
				okay = 1;
				break;
			default:
				cout << "ОШИБКА";
				break;
			}
			break;
		case 2:
			if (okay != 1)
			{
				cout << "СОЗДАЙТЕ МАССИВ";
				break;
			}
			insertMain(first, last, arr, n);
			printList(first);
			break;
		case 3:
			if (okay != 1)
			{
				cout << "СОЗДАЙТЕ МАССИВ";
				break;
			}
			deleteMain(arr, n, first, last);
			printList(first);
			break;
		case 4:
			if (okay != 1)
			{
				cout << "СОЗДАЙТЕ МАССИВ";
				break;
			}
			exchangeMain(arr, n, first, last);
			printList(first);
			break;
		case 5:
			if (okay != 1)
			{
				cout << "СОЗДАЙТЕ МАССИВ";
				break;
			}
			takeElemMain(arr, n, first);
			break;
		default:
			cout << "ОШИБКА";
			break;
		}
	}
	return 0;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	int n = 0;
	list* first = nullptr;
	list* last = nullptr;
	int* arr = new int[1];
	menu(first, last, arr, n);
	return 0;
}
