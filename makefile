CXX = g++
CXXFLAGS = -std=c++17 -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
COMMONOBJS = 

testColoredTextBox.exe: testColoredTextBox.o $(COMMONOBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	./$@

testStreetTile.exe: testStreetTile.o $(COMMONOBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	./$@

%.o : %.cpp %.hpp %.h
	$(CXX) $(CXXFLAGS) $< -o $@

testColoredTextBox.o: coloredTextBox.hpp streetTile.hpp
testStreetTile.o: streetTile.hpp coloredTextBox.hpp

clean:
	rm *.o *.exe
