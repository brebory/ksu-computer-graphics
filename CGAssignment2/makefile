#============================================================================
#  CGAssignment2 makefile
#
#  Notes:
#
#===========================================================================

EXECUTABLE = CGAssigment2
CPPFLAGS = -ggdb3 -Wall -O -Wall -W -Wunused -Wuninitialized -Wshadow 
LIBS =  -lGL -lGLU -lglut
#################################################
CC = g++
SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,src/%.o,$(SRCS))
DEPS := $(patsubst src/%.cpp,src/%.d,$(SRCS))
#################################################
all:	$(EXECUTABLE)
 
$(EXECUTABLE): $(DEPS) $(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS) $(LIBS)
 
%.d: %.cpp
	$(CC) -M $(CPPFLAGS) $< > $@
	$(CC) -M $(CPPFLAGS) $< | sed s/\\.o/.d/ > $@
 
%.d: %.h
	$(CC) -M $(CPPFLAGS) $< > $@
	$(CC) -M $(CPPFLAGS) $< | sed s/\\.o/.d/ > $@
clean:
	-rm $(OBJS) $(EXECUTABLE) $(DEPS) *~
 
explain:
	@echo "--------Some Info--------"
	@echo "Executable name: $(EXECUTABLE)"
	@echo "Source files: $(SRCS)"
	@echo "Object files: $(OBJS)"
	@echo "Dependency files: $(DEPS)"
 
depends: $(DEPS)
	@echo "Dependencies updated"
 
-include $(DEPS)
 
run:	all
	./$(EXECUTABLE)
 
debug:	all
	gdb $(EXECUTABLE)