CPP = g++ -std=c++11
INC = -I../cryphutil -I../fontutil -I../glslutil -I../ImageReader -I../mvcutil -I/usr/local/include -I.

# >>> FOR LINUX, uncomment next few lines; comment out the MAC ones.
C_FLAGS = -fPIC -g -c $(INC) -DGL_GLEXT_PROTOTYPES
GL_LIB_LOC = -L/usr/lib/nvidia-375
GL_LIBRARIES = $(GL_LIB_LOC) -lglfw -lGLU -lGL
MAKE = make
# >>> FOR MAC, uncomment next few lines; comment out previous linux ones.
# C_FLAGS = -fPIC -g -c $(INC) -DGLFW_INCLUDE_GLEXT -DGLFW_INCLUDE_GLCOREARB -DGL_SILENCE_DEPRECATION
# GL_LIBRARIES = -L/usr/local/lib -lglfw -framework OpenGL
# MAKE = make -f MakefileMac
# >>> END: FOR LINUX - FOR MAC

LINK = g++ -fPIC -g
LOCAL_UTIL_LIBRARIES = ../lib/libcryph.so ../lib/libfont.so ../lib/libglsl.so ../lib/libImageReader.so ../lib/libmvc.so

OBJS = main.o ExtendedController.o Cylinder.o Block.o Tree.o Flower.o Bench.o Bridge.o

main: $(OBJS) $(LOCAL_UTIL_LIBRARIES)
	$(LINK) -o main $(OBJS) $(LOCAL_UTIL_LIBRARIES) $(GL_LIBRARIES)

../lib/libcryph.so: ../cryphutil/AffVector.h ../cryphutil/AffVector.c++ ../cryphutil/AffPoint.h ../cryphutil/AffPoint.c++
	(cd ../cryphutil; make)

../lib/libfont.so: ../fontutil/CFont.h ../fontutil/CFont.c++ ../fontutil/CGLString.h ../fontutil/CGLString.c++
	(cd ../fontutil; $(MAKE))

../lib/libglsl.so: ../glslutil/ShaderIF.h ../glslutil/ShaderIF.c++
	(cd ../glslutil; $(MAKE))

../lib/libImageReader.so: ../ImageReader/ImageReader.h ../ImageReader/ImageReader.c++
	(cd ../ImageReader; $(MAKE))

../lib/libmvc.so: ../mvcutil/Controller.h ../mvcutil/Controller.c++ ../mvcutil/ModelView.h ../mvcutil/ModelView.c++
	(cd ../mvcutil; $(MAKE))

main.o: main.cpp
	$(CPP) $(C_FLAGS) main.cpp
ExtendedController.o: ExtendedController.cpp
	$(CPP) $(C_FLAGS) ExtendedController.cpp
Cylinder.o: Cylinder.h Cylinder.cpp
	$(CPP) $(C_FLAGS) Cylinder.cpp
Block.o: Block.h Block.cpp
	$(CPP) $(C_FLAGS) Block.cpp
Tree.o: Tree.h Tree.cpp
	$(CPP) $(C_FLAGS) Tree.cpp
Flower.o: Flower.h Flower.cpp
	$(CPP) $(C_FLAGS) Flower.cpp
Bench.o: Bench.h Bench.cpp
	$(CPP) $(C_FLAGS) Bench.cpp
Bridge.o: Bridge.h Bridge.cpp
	$(CPP) $(C_FLAGS) Bridge.cpp