#ifndef LOADER_H
#define LOADER_H


#include "GL/glut.h"

class Bad
{
  public:
      Bad(char *argv, unsigned long color,float offsetX, float offsetY,float offsetZ);
      ~Bad();

  int j;
 struct  header
{
    unsigned char header[80];
    unsigned long number_of_triangles;
} __attribute__((__packed__));

struct  triangle
{
  float Normal[3];
  float Vertex1[3];
  float Vertex2[3];
  float Vertex3[3];
  unsigned short Attr;
} __attribute__((__packed__));

   triangle *solid;

   float x,y,z;
   header head;
   char line[50];
   char name1[20];
   char name2[20];
   float x1,y1,z1;
   float x2,y2,z2;
   float x3,y3,z3;
   float R,G,B;
   bool select=false;
   int degree;
   int degreeZ;
   float offX, offY, offZ;
   float posX,posY,posZ;
   float deltaX,deltaY,deltaZ;
   float deltaX1,deltaY1,deltaZ1;

  int load(char *argv);
  void load_ascii();
  void draw();
  void rotatem();

};

#endif // LOADER_H
