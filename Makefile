EXEC = exec
OBJS = test.o

CC = gcc 
CXX = g++ 

CFLAGS = 

CXXFLAGS = 

VPATH = src  

INCPATH = -I${FREEGLUT300_HOME}/include
LIBPATH = -L${$FREEGLUT300_HOME}/lib

LIBS = -lpthread  -lglut  -lGL  -lGLU

$(EXEC):$(OBJS)
    $(CXX) $(INCPATH) $(LIBPATH) -o $(EXEC)  $(OBJS) $(LIBS)

%.o:%.cpp
    $(CXX) $(INCPATH) $(LIBPATH) -o $@ -c $< $(LIBS) 

clean:
    $(RM) $(OBJS)
