#include "fordF.h"

void fordF::runfordFBFS(graph& g)
{
	int size = g.getSize(); //num of v
	int t = g.getT(); // t
	int* path = new int[size]; //A simple path contains at most n vertices
	int cf = 0; //Cf 
	
	//Initializing the path
	initPath(path, size);

	//Finding an improving path
	this->gf.bfs(p,d);

	
	while (d[t - 1] != INF)//t is accessible from s
	{
		gf.findPath(p,t, path, size); // Finds the path from the parent array

		cf = gf.findMin(path); //Finds the min capacity in the path

		g.increaseFlow(path, cf); //Increase the flow of the edges along the path in G

		gf.CapacityUpdate(path, g);// Updates the capacity of the edges along the path in Gf

		initPath(path, size);
	
		this->gf.bfs(p, d);
	}

	this->findMinCut();

	maxflow = g.findMaxFlow();

	delete[] path;
}

void fordF::runfordG(graph& g)
{
	int size = g.getSize(); //num of v
	int t = g.getT();  // t
	int* path = new int[size]; //A simple path contains at most n vertices
	int cf = 0; //Cf

	//Initializing the path
	initPath(path, size);

	//Finding an improving path
	this->gf.dijksta(p, d);

	while (d[t - 1] != MINUS_INF)//t is accessible from s
	{

		gf.findPath(p, t, path, size); // Finds the path from the parent array

		cf = gf.findMin(path); //Finds the min capacity in the path

		g.increaseFlow(path, cf); //Increase the flow of the edges along the path in G

		gf.CapacityUpdate(path, g);// Updates the capacity of the edges along the path in Gf

		initPath(path, size);

		this->gf.dijksta(p, d);
	}

	this->findMinCut();

	maxflow = g.findMaxFlow();

	delete[] path;
}

void fordF::findMinCut()
{
	for (int i = 0; i < gf.getSize() ; i++)
	{
		if (d[i] != INF && d[i] != MINUS_INF)
			s.push_back(i + 1);

		else
			t.push_back(i + 1);
	}
}

void fordF::printMaxflowMinCut()
{
	cout << "Max flow = " << maxflow << endl;
	cout << "Min cut: S =";
	for (std::vector<int>::const_iterator i = s.begin(); i != s.end(); ++i)
		cout << " " << *i;
	cout << ".";
	cout << "T =";
	for (std::vector<int>::const_iterator i = t.begin(); i != t.end(); ++i)
		cout << " " << *i;
	cout << endl;
}

void fordF::initPath(int* path,int size)
{
	for (int i = 0; i < size; i++)
		path[i] = 0;
}

