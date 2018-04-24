all: cache-sim

cache-sim: cache-sim.cpp
	g++ -g cache-sim.cpp -o cache-sim

print: output.txt
	cat output.txt
clean:
	rm -rf cache-sim
	rm -rf output.txt
