# preparing different actions depending of the OS 
UNAME := $(shell uname)


SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,%.d,$(SOURCES))

ifeq ($(UNAME), Darwin)
CXXFLAGS := -std=c++14 -g 
LIBS = -I/opt/homebrew/Cellar/boost/1.82.0_1/include/ -I/Users/silouane/Documents/code/libs/boost/1.72.0 
LINKS = -I/opt/homebrew/include -L/opt/homebrew/lib -lboost_filesystem
endif
ifeq ($(UNAME), Linux)
CXXFLAGS := -std=c++11 -g
LIBS = 
endif

# ADD MORE WARNINGS!
WARNING := -Wall -Wextra -pedantic

# .PHONY means these rules get executed even if
# files of those names exist.
.PHONY: all clean


all: makeMeFlatAsEarth
ifeq ($(UNAME), Darwin)
	time ./makeMeFlatAsEarth -v ~/Documents/Brouillon/JSV/main.tex	
endif
ifeq ($(UNAME), Linux)
	/usr/bin/time -v ./makeMeFlatAsEarth -v ~/Documents/Brouillon/JSV/main.tex		
endif

clean:
	$(RM) $(OBJECTS) $(DEPENDS) makeMeFlatAsEarth

# Linking the executable from the object files
makeMeFlatAsEarth: $(OBJECTS)
	$(CXX) $(WARNING) $(CXXFLAGS) $(LIBS) $(LINKS) $^ -o $@

-include $(DEPENDS)

%.o: %.cpp Makefile
	$(CXX) $(WARNING) $(CXXFLAGS) $(LIBS) -MMD -MP -c $< -o $@
