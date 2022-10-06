#include "graph.h"

using namespace std;

void graph::addEdge(int u, int v, int c)
{
	this->verticas[u - 1].push_back(adjacent(v, c));
}

void graph::makeEmptyGraph(int n)
{	
	for (int i = 0; i < n; i++)
		verticas.push_back(list<adjacent>());
}

void graph::getGraph()
{
	vector<tuple<int,int>> vec;
	bool flag;
	int n, m;
	int u, v, c;

	cin >> n;
	size = n;

	if (n <= 0) //There are no vertices in the graph
	{
		cout << "invalid input" << endl;
		exit(0);
	}

	this->makeEmptyGraph(n);

	cin >> m;

	cin >> s;

	cin >> t;

	if ((m < 0) || (s < 1) || (t < 1) || (s > n) || (t > n))
	{
		cout << "invalid input" << endl;
		exit(0);
	}

	for (int i = 0; i < m; i++)
	{
		flag = false;
		cin >> u;
		cin >> v;
		cin >> c;

		if ((c < 0) || (v < 1) || (u < 1) || (v > n) || (u > n))
		{
			cout << "invalid input" << endl;
			exit(0);
		}

		for (int i = 0 ; i < vec.size() ; i++)
		{
			if (vec[i] == tuple<int, int>(u, v))
			{
				flag = true;

				for (auto it = verticas[u - 1].begin(); it != verticas[u - 1].end(); ++it)
				{
					if ((*it).vertex == v)
							(*it).capacity = c;
				}
			}
		}

		if(flag == false)
		{
			vec.push_back(tuple<int, int>(v, u));
			this->addEdge(u, v, c);
			this->addEdge(v, u, 0);
		}	
	}
}

void graph::CapacityUpdate(int* path,graph& g)
{
	int u = s;

	for (int i = 0; i < size; i++)
	{
		if (path[i] != 0)
		{

			auto it1 = verticas[u - 1].begin();
			auto it2 = g.verticas[u - 1].begin();

			for (; it1 != verticas[u - 1].end() || it2 != g.verticas[u - 1].end(); ++it1, ++it2)
			{
				if ((*it1).vertex == path[i])
					(*it1).capacity = (*it2).capacity - (*it2).flow;
			}

			it1 = verticas[path[i] - 1].begin();
			it2 = g.verticas[path[i] - 1].begin();

			for (; it1 != verticas[path[i] - 1].end() || it2 != g.verticas[path[i] - 1].end(); ++it1, ++it2)
			{
				if ((*it1).vertex == u)
					(*it1).capacity = (*it2).capacity - (*it2).flow;
			}

			u = path[i];
		}

	}

}

void graph::increaseFlow(int* path, int cf)
{
	int u = s;
	int f;


	for (int i = 0; i < size; i++)
	{
		if (path[i] != 0)
		{
			for (auto it = verticas[u - 1].begin(); it != verticas[u - 1].end(); ++it)
			{
				if ((*it).vertex == path[i])
				{
					(*it).flow += cf;
					f = (*it).flow;
				}
			}


			for (auto it = verticas[path[i] - 1].begin(); it != verticas[path[i] - 1].end(); ++it)
			{
				if ((*it).vertex == u)
				{
					(*it).flow = -f;
				}
			}

			u = path[i];
		}
	}
}

void graph::findPath(int* p,int v,int* arr,int size)
{
	if (p[v - 1] != NULL_PTR)
		findPath(p,p[v-1],arr,size-1);

	arr[size-1] = v;
}

int graph::findMin(int* path)
{
	int u = s;
	int min = 0;
    
	for (int i = 0 ; i < size; i++)
	{
		if (path[i] != 0)
		{
			for (auto it = verticas[u - 1].begin(); it != verticas[u - 1].end(); ++it)
			{
				int v = (*it).vertex;
				int curr_capacity = (*it).capacity;

				if (v == path[i])
				{
					if (min == 0)
						min = curr_capacity;

					if (curr_capacity < min)
						min = curr_capacity;
				}

			}

			u = path[i];
		}
	}

	return min;
}

void graph::removeEdge(int u, int v)
{
	for (auto it = verticas[u - 1].begin(); it != verticas[u - 1].end(); ++it)
	{
		if ((*it).vertex == v)
		{
			verticas[u - 1].erase(it);
			return;
		}
		
	}
}

list<adjacent> graph::getAdjList(int u)
{
	list<adjacent> res;

	for (auto it = verticas[u - 1].begin(); it != verticas[u - 1].end(); ++it)
		res.push_back(adjacent((*it).vertex, (*it).capacity));

	res.sort(adjacent::compareAdj);

	return res;
}

graph::graph(graph& g)
{
	size = g.size;
	s = g.s;
	t = g.t;

	this->makeEmptyGraph(size);

	for (int i = 1 ; i <= size; i++)
	{
		for (auto it = g.verticas[i - 1].begin(); it != g.verticas[i - 1].end(); ++it)
			this->addEdge(i, (*it).vertex, (*it).capacity);
	}
}

void graph::bfs(int* p,int* d)
{
	int u;
	std::queue<int> Q;

	//Init d
	for (int i = 0; i < size; i++)
	{
		d[i] = INF;
		p[i] = NULL_PTR;
	}

	//S level 0
	d[s - 1] = 0;
	
	Q.push(s);

	while (!Q.empty())
	{
		u = Q.front();
		Q.pop();

		for (auto it = verticas[u - 1].begin(); it != verticas[u - 1].end(); ++it)
		{
			int v = (*it).vertex;

			if (d[v - 1] == INF && (*it).capacity != 0)
			{
				d[v - 1] = d[u - 1] + 1;
				p[v - 1] = u;
				Q.push(v);
			}
		}
	}
}


void graph::dijksta(int* p, int* d)
{
	int u , v;
	int curr_capacity;
	//Since SQL priority queue does not allow updating the value of an element in the queue,
    //I implemented a priority queue with a maximum stack which allows finding an key and updating is value at a minimal cost
	max_heap Q;

	for (int i = 0; i < size; i++)
	{
		d[i] = MINUS_INF;
		p[i] = NULL_PTR;
	}

	d[s - 1] = 0;

	//Build Q
	Q.build(size, d);

	//Search
	while (Q.getHeapSize() != 0)
	{
		u = Q.deleteMax().getV();

		for (auto it = verticas[u - 1].begin(); it != verticas[u - 1].end(); ++it)
		{
			v = (*it).vertex;
			curr_capacity = (*it).capacity;

			if (d[v - 1] < d[u-1] + curr_capacity &&  d[u-1] != MINUS_INF && curr_capacity != 0 && d[v - 1] == MINUS_INF)
			{
				d[v - 1] = d[u - 1] + curr_capacity;
				p[v - 1] = u;
				Q.increaseKey(v, d[v - 1]);
			}
		}
	}
}

int graph::findMaxFlow()
{
	int maxflow = 0;

	for (auto it = verticas[s - 1].begin(); it != verticas[s - 1].end(); ++it)
		maxflow += (*it).getFlow();

	return maxflow;
}