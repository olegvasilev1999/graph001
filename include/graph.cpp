#include <iostream>
#include <sstream>
#include <fstream>

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
		visiting = new int [vertices];
		for (int i = 0; i < vertices; i++) {
			mtrx[i] = new int[vertices];
			visiting[i] = 0;
		}
	}

	bool read(std::istream & stream)
	{
		int n;
		bool success = true;
		if (stream >> n) {
			int ** elements = new int *[n];
			for (int i = 0; success && i < n; i++) {
				elements[i] = new int[n];
				for (int j = 0; j < n; ++j) {
					if (!(stream >> elements[i][j])) {
						success = false;
						break;
					}
				}
			}
			if (success) {
				mtrx = elements;	
			}
			else {
				for (int i = 0; i < n; i++) {
					delete[] elements[i];
				}
				delete[] elements;
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


	~graph(){
		if (mtrx != nullptr) {
			for (int i = 0; i < vertices; i++)
			{
				delete[] mtrx[i];
			}
			delete[] mtrx;
			delete[] visiting;
		}
	}
};
