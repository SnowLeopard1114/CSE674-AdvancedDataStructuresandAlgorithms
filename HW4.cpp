
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
#include <math.h>
using namespace std;

class cell {
public:
	int id;
	int wall;
	bool visited;
	bool in_structure;
	int from;
	//design your constructor
	cell() {}
	cell(int n1, int n2) { id = n1; wall = n2; visited = false; in_structure = false; from = n1; }
};
void DFS(vector<cell>& maze, int n, int start, int end);//end is target cell
void BFS(vector<cell>& maze, int n, int start, int end);
int main() {
	vector<cell> p1;
	ifstream in("maze.txt");
	int i, j, k;
	in >> i >> j >> k;//Get the number of cells,starting cell,target cell.
	int start = j;	//Store the starting cell;
	int end = k;	//Store the target cell;
	for (int num = 0; num < i; num++) {
		int wall;
		in >> wall;
		cell tmp = cell(num, wall);
		p1.push_back(tmp);
	}
	DFS(p1, i, start, end);
	for (int num = 0; num < i; num++) {	//To reset the whole vector in order to execute the BFS function.
		p1[num].from = num;
		p1[num].in_structure = false;
		p1[num].visited = false;
	}
	BFS(p1, i, start, end);


	getchar();
	getchar();
	return 0;
}
void plotTheMaze(vector<cell>& maze, int n, int start, int end) {	//This function is designed for plotting the maze and the path."#" means wall,"!"means path.
	int sq = sqrt(n);
	char** matrix = new char* [2 * sq + 1];
	for (int i = 0; i < (2 * sq + 1); i++)
		matrix[i] = new char[2 * sq + 1];
	for (int num = 0; num < n; num++) {
		int construct = maze[num].wall;
		if (construct == 0) {
			int tmp = maze[num].id;
			int len = tmp / sq;
			int wid = tmp % sq;
			matrix[len * 2][wid * 2] = ' ';
			matrix[len * 2 + 1][wid * 2] = ' ';
			matrix[len * 2 + 2][wid * 2] = ' ';
			matrix[len * 2][wid * 2 + 1] = ' ';
			matrix[len * 2][wid * 2 + 2] = ' ';
			matrix[len * 2 + 1][wid * 2 + 1] = ' ';
			matrix[len * 2 + 1][wid * 2 + 2] = ' ';
			matrix[len * 2 + 2][wid * 2 + 2] = ' ';
			matrix[len * 2 + 2][wid * 2 + 1] = ' ';
			continue;
		}
		if (construct == 1) {
			int tmp = maze[num].id;
			int len = tmp / sq;
			int wid = tmp % sq;
			matrix[len * 2 + 2][wid * 2] = '#';
			matrix[len * 2 + 2][wid * 2 + 1] = '#';
			matrix[len * 2 + 2][wid * 2 + 2] = '#';

			matrix[len * 2 + 1][wid * 2 + 1] = ' ';
			matrix[len * 2 + 1][wid * 2] = ' ';
			matrix[len * 2][wid * 2] = ' ';
			matrix[len * 2][wid * 2 + 1] = ' ';
			matrix[len * 2][wid * 2 + 2] = ' ';
			matrix[len * 2 + 1][wid * 2 + 2] = ' ';
			continue;
		}
		if (construct == 2) {
			int tmp = maze[num].id;
			int len = tmp / sq;
			int wid = tmp % sq;
			matrix[len * 2][wid * 2 + 2] = '#';
			matrix[len * 2 + 1][wid * 2 + 2] = '#';
			matrix[len * 2 + 2][wid * 2 + 2] = '#';

			matrix[len * 2][wid * 2] = ' ';
			matrix[len * 2 + 1][wid * 2] = ' ';
			matrix[len * 2 + 2][wid * 2] = ' ';
			matrix[len * 2 + 1][wid * 2 + 1] = ' ';
			matrix[len * 2][wid * 2 + 1] = ' ';
			matrix[len * 2 + 2][wid * 2] = ' ';
			matrix[len * 2 + 2][wid * 2 + 1] = ' ';
			continue;
		}
		if (construct == 3) {
			int tmp = maze[num].id;
			int len = tmp / sq;
			int wid = tmp % sq;
			matrix[len * 2 + 2][wid * 2] = '#';
			matrix[len * 2 + 2][wid * 2 + 1] = '#';
			matrix[len * 2 + 2][wid * 2 + 2] = '#';
			matrix[len * 2][wid * 2 + 2] = '#';
			matrix[len * 2 + 1][wid * 2 + 2] = '#';

			matrix[len * 2][wid * 2] = ' ';
			matrix[len * 2 + 1][wid * 2] = ' ';
			matrix[len * 2 + 1][wid * 2 + 1] = ' ';
			matrix[len * 2][wid * 2 + 1] = ' ';
			continue;

		}
		if (construct == 4) {
			int tmp = maze[num].id;
			int len = tmp / sq;
			int wid = tmp % sq;
			matrix[len * 2][wid * 2] = '#';
			matrix[len * 2][wid * 2 + 1] = '#';
			matrix[len * 2][wid * 2 + 2] = '#';

			matrix[len * 2 + 1][wid * 2] = ' ';
			matrix[len * 2 + 2][wid * 2] = ' ';
			matrix[len * 2 + 1][wid * 2 + 2] = ' ';
			matrix[len * 2 + 2][wid * 2 + 2] = ' ';
			matrix[len * 2 + 1][wid * 2 + 1] = ' ';
			matrix[len * 2 + 2][wid * 2 + 1] = ' ';
			continue;
		}
		if (construct == 5) {
			int tmp = maze[num].id;
			int len = tmp / sq;
			int wid = tmp % sq;
			matrix[len * 2 + 2][wid * 2] = '#';
			matrix[len * 2 + 2][wid * 2 + 1] = '#';
			matrix[len * 2 + 2][wid * 2 + 2] = '#';
			matrix[len * 2][wid * 2] = '#';
			matrix[len * 2][wid * 2 + 1] = '#';
			matrix[len * 2][wid * 2 + 2] = '#';

			matrix[len * 2 + 1][wid * 2] = ' ';
			matrix[len * 2 + 1][wid * 2 + 1] = ' ';
			matrix[len * 2 + 1][wid * 2 + 2] = ' ';
			continue;
		}
		if (construct == 6) {
			int tmp = maze[num].id;
			int len = tmp / sq;
			int wid = tmp % sq;
			matrix[len * 2][wid * 2] = '#';
			matrix[len * 2][wid * 2 + 1] = '#';
			matrix[len * 2][wid * 2 + 2] = '#';
			matrix[len * 2 + 1][wid * 2 + 2] = '#';
			matrix[len * 2 + 2][wid * 2 + 2] = '#';

			matrix[len * 2 + 1][wid * 2 + 1] = ' ';
			matrix[len * 2 + 1][wid * 2] = ' ';
			matrix[len * 2 + 2][wid * 2] = ' ';
			matrix[len * 2 + 2][wid * 2 + 1] = ' ';
			continue;
		}
		if (construct == 7) {
			int tmp = maze[num].id;
			int len = tmp / sq;
			int wid = tmp % sq;
			matrix[len * 2][wid * 2] = '#';
			matrix[len * 2][wid * 2 + 1] = '#';
			matrix[len * 2][wid * 2 + 2] = '#';
			matrix[len * 2 + 1][wid * 2 + 2] = '#';
			matrix[len * 2 + 2][wid * 2 + 2] = '#';
			matrix[len * 2 + 2][wid * 2] = '#';
			matrix[len * 2 + 2][wid * 2 + 1] = '#';

			matrix[len * 2 + 1][wid * 2] = ' ';
			matrix[len * 2 + 1][wid * 2 + 1] = ' ';
			continue;
		}
		if (construct == 8) {
			int tmp = maze[num].id;
			int len = tmp / sq;
			int wid = tmp % sq;
			matrix[len * 2][wid * 2] = '#';
			matrix[len * 2 + 1][wid * 2] = '#';
			matrix[len * 2 + 2][wid * 2] = '#';

			matrix[len * 2][wid * 2 + 1] = ' ';
			matrix[len * 2][wid * 2 + 2] = ' ';
			matrix[len * 2 + 1][wid * 2 + 1] = ' ';
			matrix[len * 2 + 1][wid * 2 + 2] = ' ';
			matrix[len * 2 + 2][wid * 2 + 2] = ' ';
			matrix[len * 2 + 2][wid * 2 + 1] = ' ';
			continue;
		}
		if (construct == 9) {
			int tmp = maze[num].id;
			int len = tmp / sq;
			int wid = tmp % sq;
			matrix[len * 2][wid * 2] = '#';
			matrix[len * 2 + 1][wid * 2] = '#';
			matrix[len * 2 + 2][wid * 2] = '#';
			matrix[len * 2 + 2][wid * 2 + 1] = '#';
			matrix[len * 2 + 2][wid * 2 + 2] = '#';

			matrix[len * 2][wid * 2 + 1] = ' ';
			matrix[len * 2][wid * 2 + 2] = ' ';
			matrix[len * 2 + 1][wid * 2 + 1] = ' ';
			matrix[len * 2 + 1][wid * 2 + 2] = ' ';
			continue;
		}
		if (construct == 10) {
			int tmp = maze[num].id;
			int len = tmp / sq;
			int wid = tmp % sq;
			matrix[len * 2][wid * 2] = '#';
			matrix[len * 2 + 1][wid * 2] = '#';
			matrix[len * 2 + 2][wid * 2] = '#';
			matrix[len * 2][wid * 2 + 2] = '#';
			matrix[len * 2 + 1][wid * 2 + 2] = '#';
			matrix[len * 2 + 2][wid * 2 + 2] = '#';

			matrix[len * 2][wid * 2 + 1] = ' ';
			matrix[len * 2 + 1][wid * 2 + 1] = ' ';
			matrix[len * 2 + 2][wid * 2 + 1] = ' ';
			continue;
		}
		if (construct == 11) {
			int tmp = maze[num].id;
			int len = tmp / sq;
			int wid = tmp % sq;
			matrix[len * 2][wid * 2] = '#';
			matrix[len * 2 + 1][wid * 2] = '#';
			matrix[len * 2 + 2][wid * 2] = '#';
			matrix[len * 2][wid * 2 + 2] = '#';
			matrix[len * 2 + 1][wid * 2 + 2] = '#';
			matrix[len * 2 + 2][wid * 2 + 2] = '#';
			matrix[len * 2 + 2][wid * 2 + 1] = '#';

			matrix[len * 2 + 1][wid * 2 + 1] = ' ';
			matrix[len * 2][wid * 2 + 1] = ' ';
			continue;
		}
		if (construct == 12) {
			int tmp = maze[num].id;
			int len = tmp / sq;
			int wid = tmp % sq;
			matrix[len * 2][wid * 2] = '#';
			matrix[len * 2 + 1][wid * 2] = '#';
			matrix[len * 2 + 2][wid * 2] = '#';
			matrix[len * 2][wid * 2 + 1] = '#';
			matrix[len * 2][wid * 2 + 2] = '#';

			matrix[len * 2 + 2][wid * 2 + 1] = ' ';
			matrix[len * 2 + 2][wid * 2 + 2] = ' ';
			matrix[len * 2 + 1][wid * 2 + 1] = ' ';
			matrix[len * 2 + 1][wid * 2 + 2] = ' ';
			continue;
		}
		if (construct == 13) {
			int tmp = maze[num].id;
			int len = tmp / sq;
			int wid = tmp % sq;
			matrix[len * 2][wid * 2] = '#';
			matrix[len * 2 + 1][wid * 2] = '#';
			matrix[len * 2 + 2][wid * 2] = '#';
			matrix[len * 2][wid * 2 + 1] = '#';
			matrix[len * 2][wid * 2 + 2] = '#';
			matrix[len * 2 + 2][wid * 2 + 1] = '#';
			matrix[len * 2 + 2][wid * 2 + 2] = '#';

			matrix[len * 2 + 1][wid * 2 + 1] = ' ';
			matrix[len * 2 + 1][wid * 2 + 2] = ' ';
			continue;
		}
		if (construct == 14) {
			int tmp = maze[num].id;
			int len = tmp / sq;
			int wid = tmp % sq;
			matrix[len * 2][wid * 2] = '#';
			matrix[len * 2 + 1][wid * 2] = '#';
			matrix[len * 2 + 2][wid * 2] = '#';
			matrix[len * 2][wid * 2 + 1] = '#';
			matrix[len * 2][wid * 2 + 2] = '#';
			matrix[len * 2][wid * 2 + 2] = '#';
			matrix[len * 2 + 1][wid * 2 + 2] = '#';
			matrix[len * 2 + 2][wid * 2 + 2] = '#';

			matrix[len * 2 + 1][wid * 2 + 1] = ' ';
			matrix[len * 2 + 2][wid * 2 + 1] = ' ';
			continue;
		}
		if (construct == 15) {
			int tmp = maze[num].id;
			int len = tmp / sq;
			int wid = tmp % sq;
			matrix[len * 2][wid * 2] = '#';
			matrix[len * 2 + 1][wid * 2] = '#';
			matrix[len * 2 + 2][wid * 2] = '#';
			matrix[len * 2][wid * 2 + 1] = '#';
			matrix[len * 2][wid * 2 + 2] = '#';
			matrix[len * 2 + 1][wid * 2 + 1] = '#';
			matrix[len * 2 + 1][wid * 2 + 2] = '#';
			matrix[len * 2 + 2][wid * 2 + 2] = '#';
			matrix[len * 2 + 2][wid * 2 + 1] = '#';
			continue;
		}
	}

	stack<int> print;
	int num = end;
	while (num != start) {
		print.push(num);
		num = maze[num].from;
	}
	print.push(num);
	while (!print.empty()) {
		int result = maze[print.top()].id;
		print.pop();
		int len = result / sq;
		int wid = result % sq;
		matrix[len * 2 + 1][wid * 2 + 1] = '!';
	}

	for (int i = 0; i < (2 * sq + 1); i++) {
		for (int j = 0; j < (2 * sq + 1); j++) {
			printf("%c", matrix[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < (2 * sq + 1); i++)
		delete[] matrix[i];				//Prevent Memory Leak.
	delete[] matrix;	//Prevent memory Leak;
	return;
}
void DFS(vector<cell>& maze, int n, int start, int end) {
	if (maze.empty() == true) {	//If the maze is empty,we do nothing
		cout << "Using DFS:" << endl;
		cout << "No solution." << endl;
		return;
	}
	if (n <= 0) {	//if the num of cell is 0 or less,We do nothing just return.
		cout << "Using DFS:" << endl;
		cout << "No solution." << endl;
		return;
	}
	if (start >= n || end < 0 || start < 0 || end >= n) {
		cout << "Using DFS:" << endl;
		cout << "No solution." << endl;
		return;
	}
	stack<cell*> p1;
	int sq = sqrt(n);
	int num = start;
	maze[num].in_structure = true;
	p1.push(&maze[num]);
	while (!p1.empty()) {
		cell* tmp = p1.top();
		num = tmp->id;
		tmp->visited = true;
		tmp->in_structure = false;
		p1.pop();
		if (tmp->wall != 1 && tmp->wall != 3 && tmp->wall != 5 && tmp->wall != 7 && tmp->wall != 9 && tmp->wall != 11 && tmp->wall != 13 && tmp->wall != 15) {
			if (num + sq < n)
				if (maze[num + sq].in_structure == false && maze[num + sq].visited == false) {
					maze[num + sq].in_structure = true;
					maze[num + sq].from = (num);
					p1.push(&maze[num + sq]);
					if (end == (num + sq)) {
						cout << "Using DFS:" << endl;
						num = num + sq;
						stack<int> print;
						while (num != start) {
							print.push(num);
							num = maze[num].from;
						}
						print.push(num);
						while (!print.empty()) {
							cout << maze[print.top()].id << " ";
							print.pop();
							if (!print.empty())
								cout << "-> ";
						}
						cout << endl;
						plotTheMaze(maze, n, start, end);
						return;
					}
				}
		}
		if (tmp->wall != 2 && tmp->wall != 3 && tmp->wall != 6 && tmp->wall != 7 && tmp->wall != 10 && tmp->wall != 11 && tmp->wall != 14 && tmp->wall != 15) {
			if (num + 1 < n)
				if (maze[num + 1].in_structure == false && maze[num + 1].visited == false) {
					maze[num + 1].in_structure = true;
					maze[num + 1].from = (num);
					p1.push(&maze[num + 1]);
					if (end == (num + 1)) {
						cout << "Using DFS:" << endl;
						stack<int> print;
						num = num + 1;
						while (num != start) {
							print.push(num);
							num = maze[num].from;
						}
						print.push(num);
						while (!print.empty()) {
							cout << maze[print.top()].id << " ";
							print.pop();
							if (!print.empty())
								cout << "-> ";
						}
						cout << endl;
						plotTheMaze(maze, n, start, end);
						return;
					}
				}
		}
		if (tmp->wall != 4 && tmp->wall != 5 && tmp->wall != 6 && tmp->wall != 7 && tmp->wall != 12 && tmp->wall != 13 && tmp->wall != 14 && tmp->wall != 15) {
			if (num - sq >= 0)
				if (maze[num - sq].in_structure == false && maze[num - sq].visited == false) {
					maze[num - sq].in_structure = true;
					maze[num - sq].from = (num);
					p1.push(&maze[num - sq]);
					if (end == (num - sq)) {
						cout << "Using DFS:" << endl;
						num = num - sq;
						stack<int> print;
						while (num != start) {
							print.push(num);
							num = maze[num].from;
						}
						print.push(num);
						while (!print.empty()) {
							cout << maze[print.top()].id << " ";
							print.pop();
							if (!print.empty())
								cout << "-> ";
						}
						cout << endl;
						plotTheMaze(maze, n, start, end);
						return;
					}
				}
		}
		if (tmp->wall != 8 && tmp->wall != 9 && tmp->wall != 10 && tmp->wall != 11 && tmp->wall != 12 && tmp->wall != 13 && tmp->wall != 14 && tmp->wall != 15) {
			if (num - 1 >= 0)
				if (maze[num - 1].in_structure == false && maze[num - 1].visited == false) {
					maze[num - 1].in_structure = true;
					maze[num - 1].from = (num);
					p1.push(&maze[num - 1]);
					if (end == (num - 1)) {
						cout << "Using DFS:" << endl;
						num = num - 1;
						stack<int> print;
						while (num != start) {
							print.push(num);
							num = maze[num].from;
						}
						print.push(num);
						while (!print.empty()) {
							cout << maze[print.top()].id << " ";
							print.pop();
							if (!print.empty())
								cout << "-> ";
						}
						cout << endl;
						plotTheMaze(maze, n, start, end);
						return;
					}
				}
		}
	}
	if (p1.empty()) {
		cout << "Using DFS:" << endl;
		cout << "No solution." << endl;
	}
	return;
}
void BFS(vector<cell>& maze, int n, int start, int end) {
	if (maze.empty() == true) {		//If the maze is empty,we do nothing.
		cout << "Using BFS:" << endl;
		cout << "No solution." << endl;
		return;
	}
	if (n <= 0) {	//if the num of cell is 0 or less,We do nothing just return.
		cout << "Using BFS:" << endl;
		cout << "No solution." << endl;
		return;
	}
	if (start >= n || end < 0 || start < 0 || end >= n) {
		cout << "Using BFS:" << endl;
		cout << "No solution." << endl;
		return;
	}
	queue<cell*> p1;
	int sq = sqrt(n);
	int num = start;
	maze[num].in_structure = true;
	p1.push(&maze[num]);
	while (!p1.empty()) {
		cell* tmp = p1.front();
		num = tmp->id;
		tmp->visited = true;
		tmp->in_structure = false;
		p1.pop();
		if (tmp->wall != 1 && tmp->wall != 3 && tmp->wall != 5 && tmp->wall != 7 && tmp->wall != 9 && tmp->wall != 11 && tmp->wall != 13 && tmp->wall != 15) {
			if (num + sq < n)
				if (maze[num + sq].in_structure == false && maze[num + sq].visited == false) {
					maze[num + sq].in_structure = true;
					maze[num + sq].from = (num);
					p1.push(&maze[num + sq]);
					if (end == (num + sq)) {
						cout << "Using BFS:" << endl;
						num = num + sq;
						stack<int> print;
						while (num != start) {
							print.push(num);
							num = maze[num].from;
						}
						print.push(num);
						while (!print.empty()) {
							cout << maze[print.top()].id << " ";
							print.pop();
							if (!print.empty())
								cout << "-> ";
						}
						cout << endl;
						plotTheMaze(maze, n, start, end);
						return;
					}
				}
		}
		if (tmp->wall != 2 && tmp->wall != 3 && tmp->wall != 6 && tmp->wall != 7 && tmp->wall != 10 && tmp->wall != 11 && tmp->wall != 14 && tmp->wall != 15) {
			if (num + 1 < n)
				if (maze[num + 1].in_structure == false && maze[num + 1].visited == false) {
					maze[num + 1].in_structure = true;
					maze[num + 1].from = (num);
					p1.push(&maze[num + 1]);
					if (end == (num + 1)) {
						cout << "Using BFS:" << endl;
						stack<int> print;
						num = num + 1;
						while (num != start) {
							print.push(num);
							num = maze[num].from;
						}
						print.push(num);
						while (!print.empty()) {
							cout << maze[print.top()].id << " ";
							print.pop();
							if (!print.empty())
								cout << "-> ";
						}
						cout << endl;
						plotTheMaze(maze, n, start, end);
						return;
					}
				}
		}
		if (tmp->wall != 4 && tmp->wall != 5 && tmp->wall != 6 && tmp->wall != 7 && tmp->wall != 12 && tmp->wall != 13 && tmp->wall != 14 && tmp->wall != 15) {
			if (num - sq >= 0)
				if (maze[num - sq].in_structure == false && maze[num - sq].visited == false) {
					maze[num - sq].in_structure = true;
					maze[num - sq].from = (num);
					p1.push(&maze[num - sq]);
					if (end == (num - sq)) {
						cout << "Using BFS:" << endl;
						num = num - sq;
						stack<int> print;
						while (num != start) {
							print.push(num);
							num = maze[num].from;
						}
						print.push(num);
						while (!print.empty()) {
							cout << maze[print.top()].id << " ";
							print.pop();
							if (!print.empty())
								cout << "-> ";
						}
						cout << endl;
						plotTheMaze(maze, n, start, end);
						return;
					}
				}
		}
		if (tmp->wall != 8 && tmp->wall != 9 && tmp->wall != 10 && tmp->wall != 11 && tmp->wall != 12 && tmp->wall != 13 && tmp->wall != 14 && tmp->wall != 15) {
			if (num - 1 >= 0)
				if (maze[num - 1].in_structure == false && maze[num - 1].visited == false) {
					maze[num - 1].in_structure = true;
					maze[num - 1].from = (num);
					p1.push(&maze[num - 1]);
					if (end == (num - 1)) {
						cout << "Using BFS:" << endl;
						num = num - 1;
						stack<int> print;
						while (num != start) {
							print.push(num);
							num = maze[num].from;
						}
						print.push(num);
						while (!print.empty()) {
							cout << maze[print.top()].id << " ";
							print.pop();
							if (!print.empty())
								cout << "-> ";
						}
						cout << endl;
						plotTheMaze(maze, n, start, end);
						return;
					}
				}
		}
	}
	if (p1.empty()) {
		cout << "Using BFS:" << endl;
		cout << "No solution." << endl;
	}
	return;
}
//The 20 * 20 Maze.
//400
//0
//399
//8 6 15 13 6 12 5 6 12 5 4 4 4 4 4 5 5 4 5 7 11 8 4 6 8 0 4 0 0 4 3 9 0 0 1 4 4 2 12 7 12 0 1 2 8 0 0 0 0 0 4 4 0 0 5 0 0 1 0 7 9 0 6 10 10 8 0 0 3 8 0 3 10 9 6 8 1 6 8 7 12 1 3 8 2 8 0 3 12 0 0 4 2 12 1 1 5 0 1 6 10 15 15 10 8 2 11 12 0 0 2 8 0 1 5 5 4 1 4 2 10 14 13 0 1 3 13 0 3 9 0 2 8 6 12 6 9 4 0 2 10 11 12 1 5 4 6 11 15 12 0 3 8 0 0 0 4 2 8 2 8 6 9 5 6 8 0 4 6 10 8 5 0 1 3 8 2 8 1 2 9 2 12 6 8 0 1 1 0 0 3 14 8 7 15 8 0 0 4 2 14 8 0 1 0 0 6 12 2 10 12 3 9 7 12 2 10 10 9 3 9 0 3 12 3 9 0 0 3 10 10 13 4 4 0 0 2 8 4 7 12 0 4 2 13 4 1 1 5 0 0 5 0 2 10 9 2 9 2 15 11 9 2 10 12 1 6 15 13 0 0 5 3 9 2 15 9 6 8 6 12 4 0 0 0 4 3 13 4 1 0 5 4 6 9 4 4 1 1 2 8 0 2 8 2 9 5 4 2 12 2 12 3 10 12 0 0 4 4 2 9 1 1 2 8 4 6 8 0 0 0 2 12 3 8 0 1 2 8 3 12 4 5 0 2 9 0 1 2 8 1 1 1 6 10 8 6 9 0 6 9 0 4 0 0 4 0 6 8 0 4 5 4 0 2 8 0 5 3 10 15 9 3 11 11 9 1 3 9 1 3 15 9 3 11 9 1 5 7 10