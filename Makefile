CXXFLAGS += `pkg-config --cflags SDL_gfx`
LDFLAGS += `pkg-config --libs SDL_gfx`

all: alakzat
alakzat: kor.o main.o poligon.o teglalap.o
	$(CXX) $(LDFLAGS) $+ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -f alakzat *.o
