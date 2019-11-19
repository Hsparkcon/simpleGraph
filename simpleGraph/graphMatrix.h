#pragma once
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <functional>

using vertex = char;
using index = int;
using edgeWeight = long;
using graph = edgeWeight**;
//using edgeInfo = std::map<vertex, edgeWeight>;
//using vertexInfo = std::map<vertex, edgeInfo>;

class graphMatrix
{
	private:
		enum class visitState { Unvisited, Visited };

		int numVertex;
		int numEdge;
		bool isDirected;
		bool isIndexExist;
		bool isMatrixExist;

		std::map<vertex, index> labelToindex;
		std::vector<vertex> indexTolabel;
		std::vector<vertex> rootPrinter;
		edgeWeight** matrixGraph;
		
		bool getIndex(const vertex& targetVertex, index& getIndex);

		void graphDFS(std::vector<visitState>& stateTable, const int& index);
		bool graphVisited(std::vector<visitState>& stateTable, const int& index);

		void MST_Print(const graph& inputMatrix);
		void MST_KrusKal(graph& inputMatrix);
		void isConnected(std::vector<visitState>& stateTable, const int& index, const graph& inputMatrix);
		void edgeInfoCollector(std::multimap<edgeWeight, std::pair<vertex, vertex>, std::greater <edgeWeight>>& edgeInfo, int& numCollectedEdge, const graph& inputMatrix);


	public:
		graphMatrix(const bool& directed = false);
		~graphMatrix();

		bool addVertex(const vertex inputVertex);
		bool removeVertex(const vertex targetVertex);
		void listVertex();
		void infoVertex_new(const vertex inputVertex);

		bool addEdge(const vertex& vStart, const vertex& vEnd, const edgeWeight& inputWeight = 1);
		bool getEdge(const vertex& vStart, const vertex& vEnd);
		bool setEdge(const vertex& vStart, const vertex& vEnd, const edgeWeight& inputWeight);
		bool removeEdge(const vertex& vStart, const vertex& vEnd);

		bool buildIndex();
		void buildMatrix();
		void destoryMatrix();
		void printMatrix();

		void graphDFS(const vertex& sVertex);
		void graphBFS(const vertex& sVertex);

		void MST();
		bool isConnected(const vertex& vStart, const vertex& vEnd, const graph& inputMatrix);

		/*
		void methodSelection();
		void modifyVertex();
		void modifyEdge();
		void graphInfo();
		*/
};

