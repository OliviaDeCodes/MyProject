CC = gcc
CFLAGS = -I./thirdpart/include -DTEST_FUNC -std=c11 -Wall -g
OBJS = main.o newton.o two_points.o

.PHONY: clean

a.out : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) thirdpart/libs/libtest.a
    
main.o : main.c
	$(CC) -c $(CFLAGS) main.c

newton.o : newton.c newton.h
	$(CC) -c $(CFLAGS) newton.c

two_points.o : two_points.c two_points.h
	$(CC) -c $(CFLAGS) two_points.c

clean:
	rm -rf *.o a.out
