/*Not in Use
bool graphMatrix::addVertex() {
	bool inProgress = true;
	vertex tempLabel;
	vertex tempConnected;
	std::map<vertex, edgeWeight> tempEdge; //edgeInfo tempEdge;

	std::cout << "Please enter label of a vertex" << std::endl;
	std::cin >> tempLabel;

	std::cout << "Please enter connected vertexes." << std::endl;
	std::cout << "To skip or to end the process, please enter 0." << std::endl;

	while (inProgress) {

		std::cin >> tempConnected;

		if (tempConnected == '1') {
			inProgress = false;
		}

		tempEdge.insert(std::make_pair(tempConnected, 1));

	}

	vertexList.insert(std::make_pair(tempLabel, tempEdge));

	return true;
}

bool graphMatrix::removeVertex(const vertex targetVertex) {
	auto iter = vertexList.find(targetVertex);

	if (iter == vertexList.end()) {
		std::cout << "Cannot find the vertex from the list." << std::endl;
		return false;
	}
	else {
		std::cout << "Remove Vertex - " << iter->first << std::endl;
		std::cout << "Edges to following Vertexs are removed" << std::endl;
		for (auto iterEdge : iter->second) {
			std::cout << iterEdge.first << std::endl;
		}
		vertexList.erase(iter);
		return true;
	}
}

bool graphMatrix::getVertex(const vertex& targetVertex) {
	auto iter = vertexList.find(targetVertex);

	if (iter == vertexList.end()) {
		std::cout << "Cannot find the vertex from the list." << std::endl;
		return false;
	}
	else {
		std::cout << "Vertex Info of " << iter->first << std::endl;
		std::cout << "Vertex is connected with following Vertexes" << std::endl;
		for (auto iterEdge : iter->second) {
			std::cout << iterEdge.first << std::endl;
		}
		return true;
	}
}

bool graphMatrix::addEdge(const vertex& vStart, const vertex& vEnd) {
	auto iterList = vertexList.find(vStart);

	if (iterList == vertexList.end()) {
		std::cout << "Starting Vertex does not exist." << std::endl;
		return false;
	}
	else {
		auto insertState = iterList->second.insert(std::make_pair(vEnd, 1));
		if (insertState.second) {
			std::cout << "Edge between " << vStart << " and " << vEnd << "is succeeded." << std::endl;
			return true;
		}
		else {
			std::cout << "Edge between " << vStart << " and " << vEnd << "is already exist." << std::endl;
			return false;
		}
	}
}

bool graphMatrix::removeEdge(const vertex& vStart, const vertex& vEnd) {
	auto iterStart = vertexList.find(vStart);

	if (iterStart == vertexList.end()) {
		std::cout << "Starting Vertex does not exist." << std::endl;
		return false;
	}
	else {
		auto iterEnd = iterStart->second.find(vEnd);
		if (iterEnd == iterStart->second.end()) {
			std::cout << "There no connection between Vertex" << vStart << " and " << "Vertex " << vEnd << std::endl;
			return false;
		}
		else {
			iterStart->second.erase(iterEnd);
			std::cout << "Edge between " << vStart << " and " << vEnd << "is now removed." << std::endl;
			return true;
		}
	}
}

bool graphMatrix::getEdge(const vertex& vStart, const vertex& vEnd) {
	auto iterStart = vertexList.find(vStart);

	if (iterStart == vertexList.end()) {
		std::cout << "Starting Vertex does not exist." << std::endl;
		return false;
	}
	else {
		auto iterEnd = iterStart->second.find(vEnd);
		if (iterEnd == iterStart->second.end()) {
			std::cout << "There no connection between Vertex" << vStart << " and " << "Vertex " << vEnd << std::endl;
			return false;
		}
		else {
			std::cout << "There is edge between Vertex " << vStart << " and " << "Vertex " << vEnd << std::endl;
			return false;
		}
	}
}

bool graphMatrix::setEdge(const vertex& vStart, const vertex& vEnd) {
	auto iterStart = vertexList.find(vStart);

	if (iterStart == vertexList.end()) {
		std::cout << "Starting Vertex does not exist." << std::endl;
		return false;
	}
	else {
		auto iterEnd = iterStart->second.find(vEnd);
		if (iterEnd == iterStart->second.end()) {
			std::cout << "There no connection between Vertex" << vStart << " and " << "Vertex " << vEnd << std::endl;
			return false;
		}
		else {
			iterEnd->second = 1;
			std::cout << "Edge between " << vStart << " and " << vEnd << "is now set." << std::endl;
			return true;
		}
	}
}
*/