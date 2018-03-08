all: predictors

predictors: predictors.cpp
	g++ -g predictors.cpp -o predictors

print: output.txt
	cat output.txt
clean:
	rm -rf predictors
	rm -rf output.txt
