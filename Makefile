LIBS  = 
CFLAGS = -Wall

# Should be equivalent to your list of C files, if you don't build selectively
SRC=$(wildcard *.cc)

singleton: $(SRC)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)


