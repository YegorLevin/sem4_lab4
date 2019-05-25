#pragma once
#include "ListClass.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>



using namespace std;

class Schedule
{
private:
	const int INF = 1e9;
	size_t size;
	ListClass<string> towns;
	ListClass<vector<int>*> matrix;


	void add_new_town(string name);
	ListClass<string> * split(string input);


public:
	Schedule(string file_name);
	ListClass<string> * best_way(string from, string whereto);
	void print_matrix();
};


Schedule::Schedule(string file_name)
{
	setlocale(LC_CTYPE, "Russian");
	size = 0;
	ifstream in(file_name); // opening file for reading
	string input;
	if (in.is_open())
	{
		//adding missing towns
		while (in >> input)
		{
			ListClass<string>* info = split(input);

			bool already_has1 = false;
			bool already_has2 = false;
			for (size_t i = 0; i < towns.get_size(); i++)
			{

				if (info->at(0) == towns.at(i))
					already_has1 = true;
				if (info->at(1) == towns.at(i))
					already_has2 = true;
			}
			if (!already_has1)
			{
				add_new_town(info->at(0));
			}

			if (!already_has2)
			{
				add_new_town(info->at(1));
			}

			//filling the matrix
			size_t row = 0;
			size_t column = 0;

			while (towns.at(row) != info->at(0))
			{
				row++;
			}
			while (towns.at(column) != info->at(1))
			{
				column++;
			}
			if (info->at(2) != "N/A")
			{
				matrix.at(row)->at(column) = stoi(info->at(2));
			}
			size_t support = row;
			row = column;
			column = support;

			if (info->at(3) != "N/A")
			{
				matrix.at(row)->at(column) = stoi(info->at(3));
			}

		}

	}
	else
		throw logic_error("No input file");
	in.close();     // closing file


}


void Schedule::add_new_town(string name)
{
	towns.push_back(name);
	size++;
	vector<int> * new_row = new vector<int>(size, -1); //matrix expansion
	matrix.push_back(new_row);
	for (size_t i = 0; i < size - 1; i++)
	{
		matrix.at(i)->push_back(-1);
	}
}


void Schedule::print_matrix()
{
	cout << towns << endl;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			cout << matrix.at(i)->at(j) << " ";
		}
		cout << endl;
	}
}

ListClass<string> * Schedule::split(string input)
{
	ListClass<string> * info = new ListClass<string>;
	string buffer = "";      //buffer string
	for (size_t i = 0; i < input.size(); i++) {
		if (input[i] != ';') {      // "—" splitter
			buffer += input[i];
		}
		else {
			info->push_back(buffer);
			buffer = "";
		}
	}
	info->push_back(buffer);
	return info;
}

ListClass<string> * Schedule::best_way(string from, string whereto)
{
	ListClass<int> arrival_from;
	ListClass<int> distances;
	for (size_t i = 0; i < size; i++) 
	{
		distances.push_back(INF);
		arrival_from.push_back(-1);
	}
	size_t index_from = 0;
	size_t index_whereto = 0;

	//searching index of the first town on the way
	while (towns.at(index_from) != from)
	{
		index_from++;
	}
	//searching index of the last town on the way
	while (towns.at(index_whereto) != whereto)
	{
		index_whereto++;
	}

	// Ford-Bellman algorithm
	distances.set(index_from, 0);
	
	for (size_t k = 0; k < size - 1; k++)
		for (size_t i = 0; i < size; i++)
			for (size_t j = 0; j < size; j++)
			{
				if (matrix.at(j)->at(i) == -1)
					continue;
				if (distances.at(j) + matrix.at(j)->at(i) < distances.at(i))
				{
					distances.set(i, distances.at(j) + matrix.at(j)->at(i));
					arrival_from.set(i, j);
				}
			}


	ListClass<string> * path;
	if (distances.at(index_whereto) == INF) // if there is no path
	{
		cout << "No path from " << towns.at(index_from) << " to " << towns.at(index_whereto) << "." << endl;
		return nullptr;
	}

	else { // making path
		path = new ListClass<string>;
		for (size_t current = index_whereto; current != index_from; current = arrival_from.at(current))
		{
			path->push_front(towns.at(current));
		}
		path->push_front(towns.at(index_from));
		// output
		cout << "Path from " << towns.at(index_from) << " to " << towns.at(index_whereto) << ": ";
		for (size_t i = 0; i < path->get_size() - 1; i++)
			cout << path->at(i) << "->";

		cout << path->at(path->get_size() - 1) << endl << "Total sum: " << distances.at(index_whereto) << endl;
	}
	return path;
}
