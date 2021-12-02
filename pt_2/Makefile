#
#  Linux and MS Windows Makefile for the test gui for Part 2
#  Computer Graphics course
#  Dept Computing Science, Umea University
#  Stefan Johansson, stefanj@cs.umu.se
#  Modified by Filip Henningsson, floop@cs.umu.se
#

# CHANGES FOR ImGui
# The following flags are changed or added:
# IMGUI_DIR, OBJS, IFLAGS, IMGUIFLAGS, and IMGUIFLAGS is added to CXXFLAGS

SRC = ./src
INCLUDES = ./include
IMGUI_DIR = ./src/ImGui
TARGET = 3DStudio

OBJS = $(SRC)/openglwindow.o \
	$(SRC)/geometryrender.o \
	$(SRC)/main.o \
	$(IMGUI_DIR)/imgui.o \
	$(IMGUI_DIR)/imgui_demo.o \
	$(IMGUI_DIR)/imgui_draw.o \
	$(IMGUI_DIR)/imgui_tables.o \
	$(IMGUI_DIR)/imgui_widgets.o \
	$(IMGUI_DIR)/imgui_impl_glfw.o \
	$(IMGUI_DIR)/imgui_impl_opengl3.o \
	$(IMGUI_DIR)/ImGuiFileDialog/ImGuiFileDialog.o

CXX = g++

DBFLAGS = -O0 -g3 -ggdb3 -fno-inline
#DBFLAGS = -O2
WFLAGS  = -Wall -std=c++11

# Uncomment if you have local libraries or headers in subfolders lib and include
IFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/ImGuiFileDialog -I$(INCLUDES)
LFLAGS = #-Llib

IMGUIFLAGS = -DIMGUI_IMPL_OPENGL_LOADER_GLEW

ifeq ($(OS), Windows_NT)
# -DWINDOWS_BUILD needed to deal with Windows use 0f \ instead of / in path
# Unless it's completely unnecessary and handled by the compiler.
DEFS      = -DWINDOWS_BUILD
GLFLAGS   = -DGLEW_STATIC
OSLDFLAGS = -static -lglew32 -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32
else
DEFS    = -DIMGUI_IMPL_OPENGL_LOADER_GL3W
GLFLAGS = `pkg-config --cflags glfw3`
# gl3w seemingly needs libdl
LGLFLAGS = `pkg-config --libs glfw3` -lm -ldl -lGL -lGLEW -lglfw
ELDFLAGS = -export-dynamic -lXext -lX11
endif

CXXFLAGS = $(DBFLAGS) $(DEFS) $(WFLAGS) $(IFLAGS) $(DFLAGS) $(GLFLAGS) $(IMGUIFLAGS)
LDFLAGS  = $(ELDFLAGS) $(LGLFLAGS) $(OSLDFLAGS)


all: $(TARGET)
clean:
ifeq ($(OS), Windows_NT)
	del /Q /S *.o
else
	rm -f $(OBJS) $(TARGET)
endif

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
