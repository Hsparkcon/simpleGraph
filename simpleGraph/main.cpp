#include <iostream>
#include "graphMatrix.h"

int main() {
	graphMatrix userMatrix(false);

	std::vector<char> myVector;

	char hell;

	while (std::cin >> hell) {
		myVector.push_back(hell);
		//컨트롤 z 사용, 후 cin을 청소
	}

	for (auto i : myVector) {
		std::cout << i << std::endl;
	}

	std::cin.clear();

	system("PAUSE");

	userMatrix.addVertex('a');
	userMatrix.addVertex('b');
	userMatrix.addVertex('c');
	userMatrix.addVertex('d');
	userMatrix.addVertex('e');
	std::cout << std::endl;

	userMatrix.buildIndex();
	userMatrix.buildMatrix();
	userMatrix.printMatrix();
	std::cout << std::endl;

	userMatrix.addEdge('a', 'b', 1);
	userMatrix.addEdge('a', 'c', 2);
	userMatrix.addEdge('a', 'd', 6);
	userMatrix.addEdge('a', 'e', 7);

	userMatrix.addEdge('b', 'c', 5);
	userMatrix.addEdge('b', 'd', 3);

	userMatrix.addEdge('c', 'd', 4);

	std::cout << std::endl;

	userMatrix.printMatrix();

	//userMatrix.infoVertex_new('a');
	//userMatrix.infoVertex_new('e');

	userMatrix.graphDFS('a');
	userMatrix.graphBFS('a');
/*
	
	std::cout << std::endl;

	userMatrix.removeEdge('c', 'g');
	std::cout << std::endl;

	userMatrix.printMatrix();

	userMatrix.graphBFS('a');
	std::cout << std::endl;
*/

	userMatrix.MST();

	userMatrix.destoryMatrix();


	return 0;
}