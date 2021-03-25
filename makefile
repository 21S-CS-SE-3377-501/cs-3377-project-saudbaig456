testPartOne: clean compile testSimple
testPartTwo: clean compile testMultiProcess
testPartThree: clean compile testThreaded
testPartFour: clean compile testSocket

clean:
	rm -f cmake-build-debug/21S_CS3377_Project

compile: main.cpp
	g++ -I . -pthread -o cmake-build-debug/21S_CS3377_Project main.cpp FileModifierFactory.cpp Part1SimpleFileModifier.cpp Part2MultiProcessModifier.cpp Part3ThreadedModifier.cpp Part4SocketModifier.cpp PipeMaker.cpp Util.cpp FileReader.cpp FileWriter.cpp

testSimple:
	cd cmake-build-debug && ./21S_CS3377_Project 1

testMultiProcess:
	cd cmake-build-debug && ./21S_CS3377_Project 2 2

testThreaded:
	cd cmake-build-debug && ./21S_CS3377_Project 3

testSocket:
	cd cmake-build-debug && ./21S_CS3377_Project 4 2
