#pragma once
#include <queue>
#include <vector>
#include <list>
#include <limits>

constexpr int INFINITE = std::numeric_limits<int>::max();
struct Vertex;
struct wVertex;

using ListNodes = std::vector<Vertex*>;

using VertexAndWeight = std::pair<wVertex*, int>;
using wListNodes = std::vector<VertexAndWeight>;

//unweighted Vertix
struct Vertex
{
	ListNodes adjVertices;
	bool known;	
	int dist;
	int indx;
	Vertex* path;

	Vertex(int idx) : known{ false }, dist{ INFINITE }, indx{ idx }, path{ nullptr } {}
	Vertex(const ListNodes& verts, int idx) :adjVertices{verts}, known{ false }, 
		dist{ INFINITE }, indx{ idx }, path{ nullptr } {}

	~Vertex() { adjVertices.clear(); }

	friend std::ostream& operator<<(std::ostream& out, const Vertex& v)
	{
		out << v.indx;
		return out;
	}

	
};

// weighted Vertex
struct wVertex
{
	wListNodes adjVertices;
	bool known;
	int cost;
	int dist;
	int indx;
	wVertex* path;

	wVertex(int idx) : known(false), cost(0), dist(INFINITE), indx(idx), path(nullptr) {}
	wVertex(const wListNodes& verts, int idx) : adjVertices(verts), 
		known(false), cost(0), dist(INFINITE), indx(idx), path(nullptr) {}

	~wVertex() { adjVertices.clear(); }

	// Add an adjacent vertex with a specified weight
	void addEdge(wVertex* v, int weight) 
	{
		adjVertices.push_back(VertexAndWeight( v, weight ));
	}

	friend std::ostream& operator<<(std::ostream& out, const wVertex& v) {
		out << v.indx;
		return out;
	}
};

void printPath(Vertex* v)
{
	if (v->path != nullptr)
	{
		printPath(v->path);
		std::cout << "-->";
	}

	std::cout << *v;
}

void printPath(wVertex* v)
{
	if (v->path != nullptr)
	{
		printPath(v->path);
		std::cout << "-->";
	}

	std::cout << *v;
}

