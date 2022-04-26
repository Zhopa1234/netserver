

all: socclient sockserver

OBJ_CLIENT = socclient.cpp
OBJ_SERV = sockserver.cpp


socclinet: $(OBJ_CLIENT)
	gcc  -ggdb $(OBJ_CLIENT) -o socclient

sockserver: $(OBJ_SERV)
	gcc  -ggdb $(OBJ_SERV) -o sockserver


#sockserver.o: sockserver.cpp
#	gcc $(python3-config --cflags) -fPIE -ggdb -c sockserver.cpp -o sockserver.o

#sockserver: sockserver.o
# 	gcc sockserver.o $(python3-config --embed --ldflags) -ggdb -o sockserver



clean:
	rm  socclient sockserver