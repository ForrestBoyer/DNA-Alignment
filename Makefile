CC = g++
CFLAGS = -g --std=c++14 -Wall -Werror -pedantic
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

all: EDistance lint

EDistance: EDistance.o
	$(CC) $(CFLAGS) EDistance.o -o EDistance $(LIB)

EDistance.o: EDistance.cpp
	$(CC) $(CFLAGS) -c EDistance.cpp

#lint:
#	cpplint --filter=-whitespace/line_length,-runtime/references,-build/c++11 --root=. *

clean:
	rm *.o EDistance