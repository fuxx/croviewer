TARGET := ./CroViewer 
#CXXFLAGS := -D LINUX -g -Wextra -Wall -Wno-long-long -pedantic-errors -std=c++98 -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -I/usr/local/include/fmodex -I./
CXXFLAGS := -D LINUX -g -Wno-long-long -pedantic-errors -std=c++98 -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -I/usr/local/include/fmodex -I./
CXX := g++ 
LIBS := -L/usr/lib -lSDL -lpthread -lm -ldl -lpthread -L/usr/lib -ldirectfb -ldirect -L/usr/lib -lpthread -lboost_filesystem -lSDL_image -L/usr/local/lib -lfmodex
EXT := cpp 
BUILDDIR := build 

sources:=$(wildcard *.cpp) 
objects:=$(patsubst %.cpp,%.o,$(sources)) 
deps:=$(patsubst %.cpp,%.dep,$(sources)) 

$(TARGET):  $(objects) $(deps) 
	$(CXX) $(CXXFLAGS) $(OPTS) -o $(TARGET) $(objects) $(LIBS) 

include $(sources:.cpp=.dep) 

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $(OPTS) -c $< 

%.dep: %.cpp  
	$(CXX) $(CXXFLAGS) -MM $< > $@ 

.PHONY: clean 
clean: 
	rm *.o 
	rm *.dep
	rm $(TARGET)

