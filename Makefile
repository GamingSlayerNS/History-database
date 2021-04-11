myBrowsingHistory : myBrowsingHistory.o
	g++ -o myBrowsingHistory myBrowsingHistory.o -l sqlite3
myBrowsingHistory.o :
	g++ -c myBrowsingHistory.cpp
clean :
	rm -f core myBrowsingHistory myBrowsingHistory.o
