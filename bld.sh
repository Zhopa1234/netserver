gcc $(python3-config --cflags) -fPIE -ggdb -c sockserver.cpp -o sockserver.o
gcc sockserver.o $(python3-config --embed --ldflags) -ggdb -o sockserver

