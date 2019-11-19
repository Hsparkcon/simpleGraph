#include "graphMatrix.h"


graphMatrix::graphMatrix(const bool& directed) {
	numVertex = 0;
	numEdge = 0;
	isDirected = directed;
	isIndexExist = false;
	isMatrixExist = false;
	
	labelToindex;
	indexTolabel;
	matrixGraph = nullptr;
}

graphMatrix::~graphMatrix() {
	if (isMatrixExist == true) {
		destoryMatrix();
	}
}

bool graphMatrix::getIndex(const vertex& targetVertex, index& getIndex) {

	auto iter = labelToindex.find(targetVertex);

	if (iter == labelToindex.end()) {
		std::cout << "Vertex - " << targetVertex << "is not in the list" << std::endl;
		getIndex = NULL;
		return false;
	}
	else if (iter->second >= numVertex) {
		std::cout << "Error in index of " << targetVertex << ", it exceeds size of matrix." << std::endl;
		return false;
	}
	else {
		getIndex = iter->second;
		return true;
	}

}



bool graphMatrix::addVertex(const vertex input) {
	auto insertState = labelToindex.insert(std::make_pair(input, 0));
	
	if (insertState.second) {
		std::cout << "Adding Vertex - " << input << std::endl;
		return true;
	}
	else {
		std::cout << "Vertex - " << input << " - Already Exist" << std::endl;
		std::cout << "Adding Vertex failed." << std::endl;
		return false;
	}
}

bool graphMatrix::removeVertex(const vertex targetVertex) {
	auto iter = labelToindex.find(targetVertex);

	if (iter == labelToindex.end()) {
		std::cout << "Cannot find the vertex from the list." << std::endl;
		return false;
	}
	else {
		std::cout << "Remove Vertex - " << targetVertex << std::endl;
		labelToindex.erase(iter);
		return true;
	}
}

void graphMatrix::listVertex() {
	std::cout << std::endl;
	for (auto iter : labelToindex) {
		std::cout << iter.first << std::endl;
	}
	std::cout << std::endl;
}

void graphMatrix::infoVertex_new(const vertex inputVertex) {
	auto iter = labelToindex.find(inputVertex);

	if (iter == labelToindex.end()) {
		std::cout << "There is no vertex with the given label" << std::endl;
	}
	else {
		std::cout << "Vertex " << inputVertex << " - ";
		for (int indexCol = 0; indexCol < numVertex; indexCol++) {
			if (matrixGraph[iter->second][indexCol] != 0) {
				std::cout << std::setw(3) << indexTolabel[indexCol];
			}
		}
		std::cout << '\n' << std::endl;
	}
	

}



bool graphMatrix::addEdge(const vertex& vStart, const vertex& vEnd, const edgeWeight& inputWeight) {

	index indexS, indexE;

	if (!getIndex(vStart, indexS) || !getIndex(vEnd, indexE)) {
		return false;
	} 

	matrixGraph[indexS][indexE] = inputWeight;
	numEdge = numEdge + 1;
	std::cout << "Declared Edge ( " << vStart << " & " << vEnd << " ) : " << inputWeight << std::endl;

	if (isDirected == false) {
		matrixGraph[indexE][indexS] = inputWeight;
	}

	return true;
}

bool graphMatrix::getEdge(const vertex& vStart, const vertex& vEnd) {
	index indexS, indexE;

	if (!getIndex(vStart, indexS) || !getIndex(vEnd, indexE)) {
		return false;
	}

	if (matrixGraph[indexS][indexE] != 0) {
		std::cout << "Edge between " << vStart << " & " << vEnd << " is exist." << std::endl;
		std::cout << "Weight of the Edge is " << matrixGraph[indexS][indexE] << '.' << std::endl;
	}
	else {
		std::cout << "Edge between " << vStart << " & " << vEnd << " is not exist." << std::endl;
	}
	return true;
}

bool graphMatrix::setEdge(const vertex& vStart, const vertex& vEnd, const edgeWeight& inputWeight) 
{
	index indexS, indexE;

	if (!getIndex(vStart, indexS) || !getIndex(vEnd, indexE)) 
	{
		return false;
	}

	if (matrixGraph[indexS][indexE] == 0) 
	{
		std::cout << "Edge between " << vStart << " & " << vEnd << " is not exist." << std::endl;
	}
	else {
		matrixGraph[indexS][indexE] = inputWeight;
		std::cout << "Edge between " << vStart << " & " << vEnd << " is set to " << inputWeight << '.' << std::endl;

		if (isDirected == false) 
		{
			matrixGraph[indexE][indexS] = inputWeight;
		}

	}

	return true;

}

bool graphMatrix::removeEdge(const vertex& vStart, const vertex& vEnd) {
	if (setEdge(vStart, vEnd, 0)) {
		std::cout << "Remove Edge between " << vStart << " & " << vEnd << std::endl;
		return true;
	}
	else {
		std::cout << "Failed to Remove Edge between " << vStart << " & " << vEnd << std::endl;
		return false;
	}
}



bool graphMatrix::buildIndex() {
	std::cout << "List of Vertexes" << std::endl;
	for (auto iter : labelToindex) {
		std::cout << iter.first << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Ready to build a graph? (Y/N)" << std::endl;
	char checkState;
	bool correctInput = false;

	while (!correctInput) {
		std::cin >> checkState;
		if (checkState == 'y' || checkState == 'Y' || checkState == 'n' || checkState == 'N') {
			correctInput = true;
		}
		else {
			std::cout << "Wrong Input, please use one of the followings - y, n, Y, N" << std::endl;
		}
	}

	if (checkState == 'y' || checkState == 'Y') {
		for (auto iter : labelToindex) {
			labelToindex[iter.first] = numVertex;
			indexTolabel.push_back(iter.first);
			numVertex = numVertex + 1;
		}

		isIndexExist = true;

		std::cout << "Indexing process complete." << std::endl;
		std::cout << std::endl;

		return true;
	}
	else{
		std::cout << "Indexing process stopped." << std::endl;

		return false;
	}
}

void graphMatrix::buildMatrix() {

	 matrixGraph = new edgeWeight * [numVertex];
	 for (int i = 0; i < numVertex; i++) {
		 matrixGraph[i] = new edgeWeight[numVertex];
	 }

	 for (int indexRow = 0; indexRow < numVertex; indexRow++) {
		 for (int indexCol = 0; indexCol < numVertex; indexCol++) {
			 matrixGraph[indexRow][indexCol] = 0;
		 }
	 }

	 isMatrixExist = true;
}

void graphMatrix::destoryMatrix() {

	for (int index = 0; index < numVertex; index++) {
		delete matrixGraph[index];
	}

	delete[] matrixGraph;

	matrixGraph = nullptr;
	isMatrixExist = false;

}

void graphMatrix::printMatrix() {

	std::cout << "Print Graph Matrix" << std::endl;

	std::cout << std::setw(3) << ' ';
	for (auto i : indexTolabel) { std::cout << std::setw(3) << i; }
	std::cout << std::endl;

	for (int indexRow = 0; indexRow < numVertex; indexRow++) {
		std::cout << std::setw(3) << indexTolabel[indexRow];
		for (int indexCol = 0; indexCol < numVertex; indexCol++) {
			std::cout << std::setw(3) << matrixGraph[indexRow][indexCol];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}



void graphMatrix::graphDFS(const vertex& sVertex) 
{
	index sIndex;

	if (getIndex(sVertex, sIndex)) 
	{
		std::vector<visitState> visitedVertex(numVertex, visitState::Unvisited);

		rootPrinter.clear();

		graphVisited(visitedVertex, sIndex);
		rootPrinter.push_back(sVertex);

		for (int indexCol = 0; indexCol < numVertex; indexCol++)
		{
			if (matrixGraph[sIndex][indexCol] > 0) 
			{
				graphDFS(visitedVertex, indexCol);
			}
		}
		std::cout << std::endl;
	}
}

void graphMatrix::graphDFS(std::vector<visitState>& stateTable, const int& index)
{
	bool isRouteEnd;
	bool isRouteIntersection;

	if (graphVisited(stateTable, index))
	{
		rootPrinter.push_back(indexTolabel[index]);

		isRouteEnd = true;
		isRouteIntersection = false;

		for (int indexCol = 0; indexCol < numVertex; indexCol++)
		{
			if (matrixGraph[index][indexCol] > 0 && stateTable[indexCol] == visitState::Unvisited)
			{
				graphDFS(stateTable, indexCol);
				isRouteEnd = false;
				isRouteIntersection = true;
			}
		}

		if (isRouteEnd) 
		{
			std::cout << "End of Route" << std::endl;
			for (auto iter : rootPrinter) 
			{
				std::cout << iter;
			}
			rootPrinter.pop_back();
			std::cout << std::endl;
		}

		if (isRouteIntersection) 
		{
			rootPrinter.pop_back();
		}
	}
}

void graphMatrix::graphBFS(const vertex& sVertex) 
{
	index sIndex;

	if (getIndex(sVertex, sIndex)) 
	{
		std::vector<visitState> visitedVertex(numVertex, visitState::Unvisited);
		std::queue<vertex> vertexQueue;
		int currentVisitIndex;

		vertexQueue.push(sVertex);
		graphVisited(visitedVertex, sIndex);

		while (!vertexQueue.empty()) 
		{
			currentVisitIndex = labelToindex[vertexQueue.front()];

			std::cout << vertexQueue.front() << ' ';

			for (int indexRow = 0; indexRow < numVertex; indexRow++)
			{
				if (matrixGraph[currentVisitIndex][indexRow] > 0 && graphVisited(visitedVertex, indexRow))
				{
					vertexQueue.push(indexTolabel[indexRow]);
				}
			}
			vertexQueue.pop();
		}
		std::cout << std::endl;
	}
}

bool graphMatrix::graphVisited(std::vector<visitState>& stateTable, const int& index) 
{
	if (stateTable[index] == visitState::Unvisited) 
	{
		stateTable[index] = visitState::Visited;
		return true;
	}
	else 
	{
		return false;		
	}
}



void graphMatrix::MST() {
	if (isDirected) {
		std::cout << "MST is not applicable with DIRECTED GRAPH." << std::endl;
	}
	else if (!isMatrixExist) {
		std::cout << "There is a no graph to find MST." << std::endl;
	}
	else 
	{		
		graph matrixMST = matrixGraph;
		MST_KrusKal(matrixMST);
		MST_Print(matrixMST);
	}
}

void graphMatrix::MST_KrusKal(graph& inputMatrix) {

	std::multimap<edgeWeight, std::pair<vertex, vertex>, std::greater <edgeWeight>> edgeInfo;
	std::multimap<edgeWeight, std::pair<vertex, vertex>, std::greater <edgeWeight>>::iterator iterEdgeList;;
	int currentNumEdge = NULL;
	edgeInfoCollector(edgeInfo, currentNumEdge, inputMatrix);

	std::cout << std::endl;
	std::cout << "Current Edge Info" << std::endl;
	for (auto iterEdgeInfo : edgeInfo) {
		std::cout << "Edge ( " << iterEdgeInfo.second.first << " & " << iterEdgeInfo.second.second << " ) : " << iterEdgeInfo.first << std::endl;
	}
	std::cout << std::endl;



	iterEdgeList = edgeInfo.begin();
	edgeWeight eWeight = iterEdgeList->first;
	vertex vStart = iterEdgeList->second.first;
	vertex vEnd = iterEdgeList->second.second;
	index indexRow = labelToindex[vStart];
	index indexCol = labelToindex[vEnd];	

	while (currentNumEdge + 1 > numVertex) {
		
		inputMatrix[indexRow][indexCol] = 0;
		inputMatrix[indexCol][indexRow] = 0;

		if (isConnected(vStart, vEnd, inputMatrix))
		{
			currentNumEdge = currentNumEdge - 1;
		}
		else {
			inputMatrix[indexRow][indexCol] = eWeight;
			inputMatrix[indexCol][indexRow] = eWeight;
		}

		iterEdgeList++;

		if (iterEdgeList != edgeInfo.end()) {
			eWeight = iterEdgeList->first;
			vStart = iterEdgeList->second.first;
			vEnd = iterEdgeList->second.second;
			indexRow = labelToindex[vStart];
			indexCol = labelToindex[vEnd];
		}
		else {
			iterEdgeList = edgeInfo.begin();
			eWeight = iterEdgeList->first;
			vStart = iterEdgeList->second.first;
			vEnd = iterEdgeList->second.second;
			indexRow = labelToindex[vStart];
			indexCol = labelToindex[vEnd];
		}
	}

	edgeInfoCollector(edgeInfo, currentNumEdge, inputMatrix);

	std::cout << "MST edges info" << std::endl;
	for (auto iterEdgeInfo : edgeInfo) {
		std::cout << "Edge ( " << iterEdgeInfo.second.first << " & " << iterEdgeInfo.second.second << " ) : " << iterEdgeInfo.first << std::endl;
	}
	std::cout << std::endl;

}

void graphMatrix::MST_Print(const graph& inputMatrix) {
	std::cout << "Print MST of the Graph" << std::endl;

	std::cout << std::setw(3) << ' ';
	for (auto i : indexTolabel) { std::cout << std::setw(3) << i; }
	std::cout << std::endl;

	for (int indexRow = 0; indexRow < numVertex; indexRow++) {
		std::cout << std::setw(3) << indexTolabel[indexRow];
		for (int indexCol = 0; indexCol < numVertex; indexCol++) {
			std::cout << std::setw(3) << inputMatrix[indexRow][indexCol];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void graphMatrix::edgeInfoCollector(std::multimap<edgeWeight, std::pair<vertex, vertex>, std::greater <edgeWeight>>& edgeInfo, int& numCollectedEdge, const graph& inputMatrix) {
	edgeInfo.clear();
	numCollectedEdge = 0;

	std::set<std::pair<index, index>> edgeDuplicated;
	
	for (int indexRow = 0; indexRow < numVertex; indexRow++) {
		for (int indexCol = 0; indexCol < numVertex; indexCol++) {
			if (inputMatrix[indexRow][indexCol] > 0 && edgeDuplicated.insert(std::make_pair(indexRow, indexCol)).second) {
				edgeInfo.insert(std::make_pair(inputMatrix[indexRow][indexCol], std::make_pair(indexTolabel[indexRow], indexTolabel[indexCol])));
				edgeDuplicated.insert(std::make_pair(indexCol, indexRow));
				numCollectedEdge = numCollectedEdge + 1;
			}
		}
	}
}

bool graphMatrix::isConnected(const vertex& vStart, const vertex& vEnd, const graph& inputMatrix) {
	index sIndex;
	index eIndex;

	if (getIndex(vStart, sIndex) && getIndex(vEnd, eIndex))
	{
		std::vector<visitState> visitedVertex(numVertex, visitState::Unvisited);

		graphVisited(visitedVertex, sIndex);

		for (int indexCol = 0; indexCol < numVertex; indexCol++)
		{
			if (inputMatrix[sIndex][indexCol] > 0) {
				isConnected(visitedVertex, indexCol, inputMatrix);
			}
		}

		if (visitedVertex[eIndex] == visitState::Unvisited) {
			return false;
		}
		else {
			return true;
		}
	}	
}

void graphMatrix::isConnected(std::vector<visitState>& stateTable, const int& index, const graph& inputMatrix)
{
	if (graphVisited(stateTable, index))
	{
		for (int indexCol = 0; indexCol < numVertex; indexCol++)
		{
			if (inputMatrix[index][indexCol] > 0 && stateTable[indexCol] == visitState::Unvisited)
			{
				isConnected(stateTable, indexCol, inputMatrix);
			}
		}
	}
}


/*
void graphMatrix::methodSelection() {
	int currSelection = NULL;

	while (1) {
		std::cout << "Please choose one of Following" << std::endl;
		std::cout
			<< "1 - Modify Vertex\n"
			<< "2 - Modify Edge\n"
			<< "3 - Print Current Matrix Info"
			<< "4 - Terminate the Program"
			<< std::endl;

		std::cin >> currSelection;

		switch (currSelection)
		{
		case 1:
			std::cout << "Modifying Vertex" << std::endl;
			modifyVertex();
			break;
		case 2:
			std::cout << "Modifying Edges" << std::endl;
			break;
		case 3:
			std::cout << "Print Current Matrix Info" << std::endl;
			break;
		case 4:
			std::cout << "Exit the Program" << std::endl;
		default:
			std::cout << "Please select from the list" << std::endl;
			break;
		}

	}
}

void graphMatrix::modifyVertex() {

	int currSelection = NULL;
	bool inProgress = true;
	vertex inputVertex;

	while (inProgress) {
		std::cout << "Please select work from the following" << std::endl;
		std::cout
			<< "1 - Add Vertex\n"
			<< "2 - Remove Vertex\n"
			<< "3 - Show list of Vertexes\n"
			<< "4 - Finishing the operation\n"
			<< std::endl;
	
		currSelection = NULL;
		std::cin >> currSelection;
		inputVertex = NULL;

		switch (currSelection)
		{
			case 1:
				std::cout << "Please enter all labels of vertexes to be add." << std::endl;
				std::cin >> inputVertex;
				addVertex(inputVertex);
				break;
			case 2:
				std::cout << "Please enter label of the vertex be removed" << std::endl;
				std::cin >> inputVertex;
				removeVertex(inputVertex);
				break;
			case 3:
				std::cout << "List of Vertexes" << std::endl;
				listVertex();
				break;
			case 4:
				std::cout << "End vertex modification" << std::endl;
				inProgress = false;
				break;
			default:
				std::cout << "Please Select from the list" << std::endl;
				break;
		}
	}
}

void graphMatrix::modifyEdge() {

}

void graphMatrix::graphInfo() {

}
*/