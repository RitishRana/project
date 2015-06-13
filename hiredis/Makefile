CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix src/,$(notdir $(CPP_FILES:.cpp=.o)))
main.exe: $(OBJ_FILES)
	g++ -o $@ $^ include/libhiredis.a -lcurl

%.o: src/%.cpp
	g++ -c -o $@ $< 

clean:
	rm src/*.o *.exe
