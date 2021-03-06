// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <queue>
#include <memory>
using namespace std;

pair<short**, int*> ReadGraph(size_t size)
{
	cout << "Write verticies values" << endl;
	auto poolValue = new int[size];
	for (size_t i = 0; i < size; i++)
	{
		cin >> poolValue[i];
	}
	cout << "Write transition matrix"<< endl;
	auto poolGraph = new short*[size];
	for (size_t i = 0; i < size; i++)
	{
		poolGraph[i] = new short[size];
		for (size_t j = 0; j < size; j++)
		{
			cin >> poolGraph[i][j];
		}
	}
	return make_pair(poolGraph, poolValue);
}

//Класс для работы с графом
class Graph
{
public:
	Graph(short** matrix, int* values, int size);
	~Graph();
	//Метод поиска в глубину
	bool DeepSearch(int value, int startNode);
	//Метод поиска по ширине
	bool WidthSearch(int value, int startNode);
private:
	short** matrix;
	int* values;
	int size1;
	bool MainDeepSearch(int value, int node, vector<bool> &isChecked);
};

Graph::Graph(short** matrix, int* values, int size)
{
	this->matrix = matrix;
	this->values = values;
	size1 = size;
}

Graph::~Graph()
{
	delete[] values;
	for (size_t i = 0; i < size1; i++)
		delete[] matrix[i];
}

bool Graph::DeepSearch(int value, int startNode)
{
	vector<bool> isChecked(size1, false);

	return MainDeepSearch(value, startNode, isChecked);
}

bool Graph::MainDeepSearch(int value, int node, vector<bool> &isChecked)
{
	if (isChecked[node]) return false;
	isChecked[node] = true;

	if (values[node] == value) return true;

	for (size_t i = 0; i < size1; i++)
		if (matrix[node][i] == 1)
			if (MainDeepSearch(value, i, isChecked))
				return true;
	return false;
}

bool Graph::WidthSearch(int value, int startNode)
{
	queue<int> nodesQueue;
	vector<bool> isChecked(size1, false);

	nodesQueue.push(startNode);
	for (int cur = nodesQueue.front(); nodesQueue.empty()==false; cur = nodesQueue.front())
	{
		isChecked[cur] = true;
		nodesQueue.pop();

		if (values[cur] == value) return true;

		for (size_t j = 0; j < size1; j++)
			if (matrix[cur][j] == 1 && !isChecked[j])
				nodesQueue.push(j);
	}
	return false;
}

int main()
{
	size_t size;
	cout << "Write matrix size" << endl;
	cin >> size;

	auto myPair = ReadGraph(size);

	cout << "Write target digit" << endl;
	int target;
	cin >> target;

	cout << "Write start node number" << endl;
	int startNumber;
	cin >> startNumber;

	Graph gr(myPair.first, myPair.second, size);
	cout << "Deep search result " << gr.DeepSearch(target, startNumber) << endl;
	cout << "Width search result " << gr.WidthSearch(target, startNumber) << endl;
	system("pause");
	return 0;
}
