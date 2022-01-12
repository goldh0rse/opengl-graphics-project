#
#  Linux Makefile for Computer Graphics project
#  Computer Graphics course
#  Dept Computing Science, Umea University
#  Stefan Johansson, stefanj@cs.umu.se
#  Modified by Filip Henningsson, floop@cs.umu.se
#  Modified by Klas Holmberg, hed16khg@cs.umu.se
#
SRC = ./src
INCLUDES = ./include
TARGET =  3DStudio.app
IMGUI_DIR = $(SRC)/ImGui

OBJS = 	\
	$(SRC)/main.o \
	$(SRC)/openglwindow.o \
	$(SRC)/shader.o \
	$(SRC)/texture.o \
	$(SRC)/material.o \
	$(SRC)/mesh.o \
	$(SRC)/primitive.o \
	$(SRC)/mymodel.o \
	$(SRC)/camera.o \
	$(SRC)/light.o \
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
WFLAGS  = -Wall -std=c++11 #-Wextra

# Uncomment if you have local libraries or headers in subfolders lib and include
IFLAGS = -I$(INCLUDES) -I$(IMGUI_DIR) -I$(IMGUI_DIR)/ImGuiFileDialog
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
	make -t

.SUFFIXES: .o .c .cpp .cxx .cc
.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -MMD -MP -o "$@" "$<"
.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -MMD -MP -o "$@" "$<"
.cc.o:
	$(CXX) -c $(CXXFLAGS) -MMD -MP $<
.c.o:
	$(CXX) -c $(CXXFLAGS) -MMD -MP $<
$(TARGET): $(OBJS)
	$(CXX) $(LFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)
