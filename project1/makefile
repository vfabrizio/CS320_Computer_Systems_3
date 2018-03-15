all: predictors

predictors: LinkedList.cpp predictors.cpp
	g++ -g LinkedList.cpp predictors.cpp -o predictors

print: output.txt
	cat output.txt
clean:
	rm -rf predictors
	rm -rf output.txt
