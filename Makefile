UNAME := $(shell uname)

COMPILERFLAGS = -Wall

ifeq ($(UNAME), Linux)
INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/X11R6/lib 
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm 
endif

ifeq ($(UNAME), Darwin)
FRAMEWORK = -framework GLUT
FRAMEWORK += -framework OpenGL
LIBDIR = -L"/System/Library/Frameworks/OpenGL.framework/Libraries"
LIBRARIES = -lGL -lGLU
endif

CC = gcc
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)

game_NAME := game
game_SRCS := $(wildcard *.c)
game_OBJS := ${game_SRCS:.c=.o}

all: $(game_NAME)
$(game_NAME): $(game_OBJS)
	$(CC) $(FRAMEWORK) $(CFLAGS) -o $(game_NAME) $(LIBDIR) $(game_OBJS) $(LIBRARIES)  
clean:
	rm -f $(game_NAME) $(game_OBJS)
