CC := g++ -std=c++17
BINARY := dermo
RM := rm -rf 

build:
	$(CC) -o $(BINARY) interval_map.cpp

clean:
	$(RM) $(BINARY)