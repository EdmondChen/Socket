server: server.o serverMain.o
	xlC -o server server.o serverMain.o
server.o: server.cpp server.h
	xlC -c server.cpp -o server.o
serverMain.o: serverMain.cpp server.h
	xlC -c serverMain.cpp -o serverMain.o
clean:
	rm -rf *.o server