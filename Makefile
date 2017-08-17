CPPFLAGS=-DDEBUG=3
All: MoveBall.exe 
	
MoveBall.exe :MoveBall.o VideoBoard.o raspivid.o VideoBuffer.o Ppm.o Ball.o
	g++ -o MoveBall.exe MoveBall.o VideoBoard.o raspivid.o VideoBuffer.o Ppm.o Ball.o


clean:
	rm *.o

cleanshort:
	rm Ball.o MoveBall.o















