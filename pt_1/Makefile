#
#  Linux Makefile for Computer Graphics project
#  Computer Graphics course
#  Dept Computing Science, Umea University
#  Stefan Johansson, stefanj@cs.umu.se
#  Modified by Filip Henningsson, floop@cs.umu.se
#  Modified by Klas Holmberg, hed16khg@cs.umu.se
#
SRC = ./src
OUT = ./out
TARGET = project

#OBJS = $(OUT)/main.o $(OUT)/shader.o $(OUT)/texture.o \
    $(OUT)/material.o $(OUT)/mesh.o $(OUT)/primitive.o \
    $(OUT)/openglwindow.o $(OUT)/mymodel.o

OBJS = $(SRC)/main.o $(SRC)/shader.o $(SRC)/texture.o \
	$(SRC)/material.o $(SRC)/mesh.o $(SRC)/primitive.o \
	$(SRC)/openglwindow.o $(SRC)/mymodel.o

CXX = g++

DBFLAGS = -O0 -g3 -ggdb3 -fno-inline
#DBFLAGS = -O2
WFLAGS  = -Wall -std=c++11 #-Wextra

# Uncomment if you have local libraries or headers in subfolders lib and include
IFLAGS = -Iinclude
LFLAGS = -Llibs

DEFS    = -DIMGUI_IMPL_OPENGL_LOADER_GL3W
GLFLAGS = `pkg-config --cflags glfw3`
# gl3w seemingly needs libdl
LGLFLAGS = `pkg-config --libs glfw3` -lm -ldl -lGL -lGLEW -lglfw
ELDFLAGS = -export-dynamic -lXext -lX11 -lsoil2

#GLM & SOIL
GLMFLAGS = `pkg-config --cflags-only-I glm`

CXXFLAGS = $(WFLAGS) $(DFLAGS) $(GLFLAGS)

CXXFLAGS = $(DBFLAGS) $(DEFS) $(WFLAGS) $(IFLAGS) $(DFLAGS) $(GLFLAGS) $(GLMFLAGS)
LDFLAGS  = $(ELDFLAGS) $(LGLFLAGS) $(OSLDFLAGS)


all: $(TARGET)
clean:
	rm -f $(OBJS) $(TARGET)
build:
	rm -f $(OBJS) $(TARGET)
	make

.SUFFIXES: .o .c .cpp .cxx .cc
.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"
.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"
.cc.o:
	$(CXX) -c $(CXXFLAGS) $<
.c.o:
	$(CXX) -c $(CXXFLAGS) $<
$(TARGET): $(OBJS)
	$(CXX) $(LFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)
