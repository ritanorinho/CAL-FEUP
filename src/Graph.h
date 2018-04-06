/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
private:
	T info;                // contents
    // outgoing edges
	bool visited;          // auxiliary field
    Vertex<T> *path = NULL;
    // required by MutablePriorityQueue

	bool processing = false;
    Edge<T> * addEdge(Vertex<T> *dest, double w, long id);

public:
	Vertex(T in);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T &getInfo();
	double getDist() const;
	Vertex *getPath() const;
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
    vector<Edge<T>> &getAdj();
    void setAdj(const vector<Edge<T>> &adj);

    double dist = 0;
    int queueIndex = 0;
    vector<Edge<T>> adj;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
Edge<T> *Vertex<T>::addEdge(Vertex<T> *d, double w, long id) {
    for(auto edge:adj){
        if((edge.dest == d) && (edge.getId() == id)) {
            return nullptr;
        }
    }

    Edge<T> *newEdge = new Edge<T>(d, w);
    newEdge->setId(id);
	adj.push_back(*newEdge);
    return newEdge;
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T &Vertex<T>::getInfo() {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;
public:
    Vertex<T> *getDest() const;

    void setDest(Vertex<T> *dest);

private:
    // destination vertex
	double weight;         // edge weight
	long id;
    string nome_rua;
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
    long getId() const;
    void setId(long id);
    const string &getNome_rua() const;
    void setNome_rua(const string &nome_rua);
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	Edge<T> *addEdge(const T &sourc, const T &dest, double w, long id);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void dijkstraShortestPath(const T &s);
	void dijkstraShortestPathOld(const T &s);
	void unweightedShortestPath(const T &s);
	void bellmanFordShortestPath(const T &s);
	vector<T> getPath(const T &origin, const T &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;

    vector<T> findNearestSharepoint(const T &origin);
    vector<vector<T>> findNearestSharepoints(const T &origin);

    void isStronglyConnected(Vertex<T> *vertex, vector<Vertex<T>*> *visited);

    bool isStronglyConnected();
};

template<class T>
vector<Edge<T>> &Vertex<T>::getAdj() {
    return adj;
}

template<class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) {
    Vertex::adj = adj;
}

template<class T>
long Edge<T>::getId() const {
    return id;
}

template<class T>
void Edge<T>::setId(long id) {
    Edge::id = id;
}

template<class T>
const string &Edge<T>::getNome_rua() const {
    return nome_rua;
}

template<class T>
void Edge<T>::setNome_rua(const string &nome_rua) {
    Edge::nome_rua = nome_rua;
}

template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

template<class T>
void Edge<T>::setDest(Vertex<T> *dest) {
    Edge::dest = dest;
}

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
Edge<T> *Graph<T>::addEdge(const T &sourc, const T &dest, double w,long id) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return nullptr;
	return v1->addEdge(v2,w,id);
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    MutablePriorityQueue<Vertex<T> > q;

    for(auto v : this->vertexSet){
        v->dist = INF;
        v->path = nullptr;
        v->queueIndex = -1;
    }

    Vertex<T> *originVertex = findVertex(origin);

    originVertex->dist = 0;
    originVertex->queueIndex = 0;
    q.insert(originVertex);

    while(!q.empty()){
        Vertex<T> *v = q.extractMin();
        for(auto edge : v->adj){
            Vertex<T> *w = edge.dest;
            if(w->dist > (v->dist + edge.weight)){
                double oldDist = w->dist;
                w->dist = v->dist + edge.weight;
                w->path = v;
                if(oldDist == INF){
                    q.insert(w);
                }else{
                    q.decreaseKey(w);
                }
            }
        }
    }
}

template<class T>
vector<T> Graph<T>::findNearestSharepoint(const T &origin) {
    MutablePriorityQueue<Vertex<T>> q;

    for(auto v : this->vertexSet){
        v->dist = INF;
        v->path = nullptr;
        v->queueIndex = -1;
    }

    Vertex<T> *originVertex = findVertex(origin);

    originVertex->dist = 0;
    originVertex->queueIndex = 0;
    q.insert(originVertex);

    Vertex<T> *v;

    while(!q.empty()){
        v = q.extractMin();
        if(v->getInfo().getSharePoint().getBicycles() != -1 && v->getInfo().getSharePoint().getCurrentPrice() != -1){
            return getPath(origin,v->getInfo());
        }
        for(auto edge : v->adj){
            Vertex<T> *w = edge.dest;
            if(w->dist > (v->dist + edge.weight)){
                double oldDist = w->dist;
                w->dist = v->dist + edge.weight;
                w->path = v;
                if(oldDist == INF){
                    q.insert(w);
                }else{
                    q.decreaseKey(w);
                }
            }
        }
    }

    return vector<T>();
}

template<class T>
vector<vector<T>> Graph<T>::findNearestSharepoints(const T &origin) {

    vector<vector<T>> ret;

    MutablePriorityQueue<Vertex<T>> q;

    for(auto v : this->vertexSet){
        v->dist = INF;
        v->path = nullptr;
        v->queueIndex = -1;
    }

    Vertex<T> *originVertex = findVertex(origin);

    originVertex->dist = 0;
    originVertex->queueIndex = 0;
    q.insert(originVertex);

    Vertex<T> *v;

    while(!q.empty()){
        v = q.extractMin();
        if(v->getInfo().getSharePoint().getBicycles() != -1 && v->getInfo().getSharePoint().getCurrentPrice() != -1){
            ret.push_back(getPath(origin,v->getInfo()));
        }
        for(auto edge : v->adj){
            Vertex<T> *w = edge.dest;
            if(w->dist > (v->dist + edge.weight)){
                double oldDist = w->dist;
                w->dist = v->dist + edge.weight;
                w->path = v;
                if(oldDist == INF){
                    q.insert(w);
                }else{
                    q.decreaseKey(w);
                }
            }
        }
    }

    return ret;
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    vector<T> res;

    Vertex<T> *curr_vertex = findVertex(dest);
    Vertex<T> *dest_vertex = findVertex(origin);

    if(curr_vertex == dest_vertex){
        cout << "Warning: Origin is the same as Dest" << endl;
    }

    res.push_back(curr_vertex->info);

    while(curr_vertex != dest_vertex) {
        curr_vertex = curr_vertex->path;

        if(curr_vertex == 0x0){
            cout << "Could not find path" << endl;
            return res;
        }

        res.push_back(curr_vertex->info);
    }

    reverse(res.begin(),res.end());

    return res;
}

template<class T>
bool Graph<T>::isStronglyConnected() { //DFS
    vector<Vertex<T>*> visited;
    Vertex<T> *startSharePoint;

    for(auto ver: getVertexSet()){
        for(auto edge: ver->getAdj()){
            if(edge.dest->getInfo().getSharePoint().getBicycles() > 0){
                startSharePoint = edge.dest;
            }
        }
    }

    if (startSharePoint == nullptr){
        cout << "Could not find any accessible sharepoints" << endl;
        return false;
    }

    isStronglyConnected(startSharePoint,&visited);

    if(visited.size() == getVertexSet().size()){
        cout << "Graph is fully connected" << endl;
        return true;
    }

    int sharePointNum = 0;

    for(auto ver: getVertexSet()){
        if(ver->getInfo().getSharePoint().getBicycles() > 0){
            sharePointNum++;
        }
    }

    for(auto ver: visited){
        if(ver->getInfo().getSharePoint().getBicycles() > 0){
            sharePointNum--;
        }
    }

    if(sharePointNum == 0){
        cout << "Graph is not fully connected but all sharepoints are accessible" << endl;
        return true;
    }else if(sharePointNum < 0){
        cout << "Error: Visited set is larger than graph vertex list" << endl;
        return false;
    }else{
        cout << "Graph is not fully connected and not every sharepoint is accessible" << endl;
    }

}


template<class T>
void Graph<T>::isStronglyConnected(Vertex<T> *vertex,vector<Vertex<T> *> *visited){ //DFS

    visited->push_back(vertex);

    for(Edge next: vertex->getAdj()){
        if(std::find(visited->begin(),visited->end(),next.getDest()) == visited->end()){
            isStronglyConnected(next.getDest(),visited);
        }
    }
}

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
	// TODO
}

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	// TODO
}


/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
	// TODO
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
	// TODO
	return res;
}


#endif /* GRAPH_H_ */
