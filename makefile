# # Makefile

CXX = g++
CXXFLAGS = -std=c++11 -g

all: passwordManager

passwordManager: main.o entryMenu.o recordPassword.o decrypt.o
	$(CXX) $(CXXFLAGS) -o passwordManager main.o entryMenu.o recordPassword.o decrypt.o `wx-config --cxxflags --libs`

main.o: main.cpp entryMenu.hpp
	$(CXX) $(CXXFLAGS) -c -o main.o main.cpp `wx-config --cxxflags`

entryMenu.o: entryMenu.cpp entryMenu.hpp
	$(CXX) $(CXXFLAGS) -c -o entryMenu.o entryMenu.cpp `wx-config --cxxflags`

recordPassword.o: recordPassword.cpp recordPassword.hpp
	$(CXX) $(CXXFLAGS) -c -o recordPassword.o recordPassword.cpp `wx-config --cxxflags`

decrypt.o: decrypt.cpp decrypt.hpp
	$(CXX) $(CXXFLAGS) -c -o decrypt.o decrypt.cpp `wx-config --cxxflags`

clean:
	rm -f passwordManager *.o
