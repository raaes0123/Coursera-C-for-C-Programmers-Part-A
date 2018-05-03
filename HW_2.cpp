/*
 * HW_2.cpp -- Implementing Dijkstra's shortest path algorithm.
 */
 
#include <iostream>
#include <vector>
#include <limits>
//#include <ctime>
using namespace std;

vector<int> shortestPath(int start, int end, vector <vector <int>> roads)
{
	int n = roads.size();
	vector<int> path;  //Note: The first element of vector is the shortest distance and the actual path nodes later
	vector<int> open(n, 10000);
	vector<int> closed(n, 10000);
	vector<vector <int>> openSet;
	vector<vector <int>> closedSet;
	closedSet.push_back(vector<int> {start, start});
	closed[start] = 0;
	open[start] = 0;
	int prevOpenSize;
	do {
		prevOpenSize = openSet.size();
		int cityToExplore = closedSet.back()[1];
		for (int i = 0; i < n; i++)
		{
			int distance = open[cityToExplore] + roads[cityToExplore][i];
			if (distance < open[i])
			{
				// Search and erase if this ith city has already been pushed to openSet
				int flag = 0;
				for (int j = 0; j < openSet.size(); j++)
					if (openSet[j][1] == i)
					{
						openSet[j][0] = cityToExplore;
						flag = 1;
					}
				if(flag == 0)
					openSet.push_back(vector<int> {cityToExplore, i});
				open[i] = distance;
			}
		}
		//Select the city from openSet with the least distance and pushback to closedSet
		if (openSet.size() > 0)
		{
			int minIndex = 0;
			for (int i = 1; i < openSet.size(); i++)
				if (open[openSet[i][1]] < open[openSet[minIndex][1]])
					minIndex = i;
			closedSet.push_back(openSet[minIndex]);
			closed[closedSet.back()[1]] = open[closedSet.back()[1]];
			openSet.erase(openSet.begin() + minIndex);
		}
		if (closedSet.back()[1] == end)
		{
			path.push_back(closed[closedSet.back()[1]]);
			int nodeBegin = closedSet.back()[0];
			int nodeEnd = closedSet.back()[1];
			while (nodeBegin != start)
			{
				for (int i = 0; i < closedSet.size(); i++)
				{
					if (nodeBegin == closedSet[i][1])
					{
						nodeEnd = nodeBegin;
						nodeBegin = closedSet[i][0];
						break;
					}
				}
				path.push_back(nodeEnd);
			}
			return path;
		}
	} while (!(openSet.size() == 0 && prevOpenSize == 0));
	return vector<int> {-1};
}

bool isConnected(vector <vector <int>> roads)
{
	int n = roads.size();
	vector <bool> open(n, false);
	vector <bool> closed(n, false);
	vector <int> openSet;
	vector <int> closedSet;
	closedSet.push_back(0);
	closed[0] = true;
	int prevOpenSize;
	do{
		prevOpenSize = openSet.size();
		int cityToExplore = closedSet.back();
		for (int i = 0; i < n; i++)
		{
			if (roads[cityToExplore][i] > 0 && !open[i] && !closed[i])
			{
				openSet.push_back(i);
				open[i] = true;
			}
		}
		if (openSet.size() > 0)
		{
			closedSet.push_back(openSet.back());
			openSet.pop_back();
		}
	} while (!(openSet.size() == 0 && prevOpenSize == 0));
	if (closedSet.size() == n)
		return true;
	else
		return false;
}

int main()
{
	const int connectedness = 50;
	const int cities = 9;
	int a = std::numeric_limits<int>::max();
	a /= 2;
	vector <vector <int>> roads{{a,4,3,a,7,a,a,a,a},
								{a,a,a,1,a,a,a,a,a},
								{3,a,a,a,4,a,a,a,a},
								{a,a,a,a,3,1,a,a,a},
								{a,a,a,a,a,1,5,a,3},
								{a,a,a,a,a,a,a,2,4},
								{a,a,a,a,a,a,a,a,a},
								{a,a,a,a,a,2,a,a,3},
								{a,a,a,a,a,a,5,a,a}};
	//srand(time(NULL));
	//for (int i = 0; i < cities; i++)
	//{
	//	vector <int> row;
	//	for (int j = 0; j < cities; j++)
	//	{
	//		if (i == j)
	//			row.push_back(0);
	//		else if (rand() % 100 > connectedness)
	//			row.push_back(0);
	//		else
	//			row.push_back(1);
	//	}
	//	roads.push_back(row);
	//}
	//cout << "Roads: " << endl;
	//for (int i = 0; i < cities; i++)
	//{
	//	for (int j = 0; j < cities; j++)
	//		cout << roads[i][j] << "	";
	//	cout << endl;
	//}
	//cout << isConnected(roads) << endl;
	int start = 0;
	int end = 8;
	vector <int> path = shortestPath(start, end, roads);
	cout << start << " --> ";
	for (int i = path.size() - 1 ; i > 0 ; i--)
		cout << path[i] << " --> ";
	cout << end << endl;
	cout << "The shortest distance is: " << path[0] << endl;
	return 0;
}