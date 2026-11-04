bin/testListArray: testListArray.cpp ListArray.h List.h
	mkdir -p bin
	g++ -o bin/testListArray testListArray.cpp

clean:
	rm -r *.o *.gch *.pch bin

bin/testNode: testNode.cpp Node.h
	mkdir -p bin
	g++ -o bin/testNode testNode.cpp

bin/testListLinked: testListLinked.cpp ListLinked.h Node.h List.h
	mkdir -p bin
	g++ -std=c++11 -g testListLinked.cpp -o bin/testListLinked
