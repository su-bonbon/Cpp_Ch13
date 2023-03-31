pa13: Container.o pa13.o
	$(CXX) $(CXXFLAGS) Container.o pa13.o -o pa13

Container.o: Container.h Container.cpp
	$(CXX) $(CXXFLAGS) Container.cpp -c

pa13.o: pa13.cpp Container.h
	$(CXX) $(CXXFLAGS) pa13.cpp -c

clean:
	rm -f Container.o pa13.o pa13

turnin:
	turnin -c cs202 -p pa13 -v \
		Container.h Container.cpp pa13.cpp Makefile

