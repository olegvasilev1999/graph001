#include <iostream>
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
		visiting = new int [vertices];
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
				mtrx = elements;
			}
			for (int i = 0; i < vertices; i++) {
				delete[] elements[i];
			}
			delete[] elements;
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
