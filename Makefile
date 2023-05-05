FLAGS = -pedantic-errors -std=c++11
Target = black_jack
OBJ = black_jack.o banker.o player.o AllocationSystem.o

$(Target) : $(OBJ)
	g++ $(FLAGS) $^ -o $@

%.o: %.cpp
	g+++ $(FLAGS) -c $<

.PHONY:clean

clean:
	rm -f $(Target) $(OBJ)
