#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

class graph
{
	int ** mtrx;
	int vertices;
	int * visiting;

public:
	graph() {
		mtrx = nullptr;
		vertices = 0;
		visiting = nullptr;
	}

	graph(int n) {
		vertices = n;
		mtrx = new int *[vertices];
		visiting = new int[vertices];
		for (int i = 0; i < vertices; i++) {
			mtrx[i] = new int[vertices];
			visiting[i] = 0;
		}
	}

	bool read_mtrx(std::istream & stream)
	{
		bool success = true;
		if (success) {
			int ** elements = new int *[vertices];
			for (int i = 0; success && i < vertices; i++) {
				elements[i] = new int[vertices];
				for (int j = 0; j < vertices; ++j) {
					if (!(stream >> elements[i][j])) {
						success = false;
						break;
					}
				}
			}
			if (success) {
				if (mtrx != nullptr) {
					for (int i = 0; i < vertices; i++) {
						delete[] mtrx[i];
					}
					delete[] mtrx;
				}
				mtrx = new int *[vertices];
				for (int i = 0; i < vertices; i++)
				{
					mtrx[i] = new int[vertices];
					for (int j = 0; j < vertices; j++)
					{
						mtrx[i][j] = elements[i][j];
					}
				}
				for (int i = 0; i < vertices; i++) {
					delete[] elements[i];
				}
				delete[] elements;
			}
			else {
				success = false;
			}

		}
		else {
			success = false;
		}
		return success;
	}

	void graph_dfs(std::ostream & stream, int vertex) {
		if (vertex < vertices) {
			visiting[vertex]++;
			stream << vertex << " ";
			for (int i = 0; i < vertices; i++) {
				if (mtrx[vertex][i] == 1 && visiting[i] == 0) {
					graph_dfs(stream, i);
				}
			}
		}
		else {
			throw out_of_range("there is no such vertex");
		}
	}

	void clearvisiting() {
		for (int i = 0; i < vertices; i++) {
			visiting[i] = 0;
		}
	}

	int * distance(int vertex) {
		int * dist = new int[vertices];
		int minindex, min;
		clearvisiting();
		for (int i = 0; i < vertices; i++) {
			dist[i] = 10000;
		}
		dist[vertex] = 0;
		do {
			minindex = 10000;
			min = 10000;
			for (int i = 0; i < vertices; i++) {
				if (dist[i] < min && visiting[i] == 0 ) {
					min = dist[i];
					minindex = i;
				}
			}
			if (minindex != 10000) {
				for (int i = 0; i < vertices; i++) {
					if (mtrx[minindex][i] > 0) {
						if (min + mtrx[minindex][i] < dist[i]) {
							dist[i] = min + mtrx[minindex][i];
						}
					}
				}
				visiting[minindex] = 1;
			}
		} while (minindex < 10000);
		return dist;
	}

	void shortway(std::ostream & stream, int vertex) {
		int * d = distance(vertex);
		int j, dist, tmp;
		for (int dest = 0; dest < vertices; dest++){
			int * way = new int[vertices];
			way[0] = dest;
			tmp = dest;
			j = 1;
			dist = d[dest];
			while (tmp != vertex) {
				for (int i = 0; i < vertices; i++) {
					if (mtrx[tmp][i] != 0) {
						if (dist - mtrx[tmp][i] == d[i]) {
							dist = dist - mtrx[tmp][i];
							tmp = i;
							way[j] = i;
							j++;
						}
					}
				}
			}
			for (int i = j - 1; i >= 0; i--) {
				stream << way[i] << ' ';
			}
			stream << endl;
			delete[] way;
		}
		delete[] d;
		
	}

	~graph() {
		if (mtrx != nullptr) {
			for (int i = 0; i < vertices; i++) {
				delete[] mtrx[i];
			}
			delete[] mtrx;
			delete[] visiting;
		}
	}
