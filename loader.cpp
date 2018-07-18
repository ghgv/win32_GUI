#include "loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrix.h"
#include <unistd.h>
#define PATH_MAX 80
extern int pos2;
extern float degreeZ;

void Bad::load_ascii()
{

};

Bad::Bad(char *argv,unsigned long color, float offsetX,float offsetY,float offsetZ)
{
FILE *fp;
int i,j;
R=(color>>16);
G=(color>>8) & (0x0000FF);
B=(color&0x0000FF);
offX=offsetX;
offY=offsetY;
offZ=offsetZ;

deltaX=0;
deltaY=0;
deltaZ=0;

deltaX1=0;
deltaY1=0;
deltaZ1=0;

char init[]="solid";
char* cwd;
char buff[PATH_MAX + 1];
cwd = getcwd( buff, PATH_MAX + 1 );
    if( cwd != NULL ) {
        printf( "Current directory is %s.\n", cwd );
    }

   fp=fopen(argv,"rb");
   if(fp==NULL)
   {
       printf("file %s not found\n",argv);
       exit(0);
   }

   fread(&head, 1,sizeof(head), fp);
   for(i=0;i<80;i++)
   {
       printf("%c",head.header[i]);
   }
   memcpy(init,&head.header[0],sizeof("solid")-1);
   printf("\nInit word %s\n",init);

   if(strcmp(init,"solid")!=0)
	{
    	printf("\nNumber of Triangles: %i, size of tri %i bytes, payload= %i \n",head.number_of_triangles, sizeof(triangle),sizeof(triangle)*head.number_of_triangles );
    	solid=(  triangle *)malloc(head.number_of_triangles*sizeof(triangle));
    	i=fread(solid, sizeof(triangle),head.number_of_triangles, fp);
    	printf("Read objects %i\n",i);
	}
    else
	{
        printf("Ascii file\n");
        load_ascii();
		fseek(fp,0,SEEK_SET);
        fgets(line,sizeof line,fp);
        sscanf(line,"%s %s",name1,name2);
        printf("%s %s\n",name1,name2);
        i=0;
        memcpy(name1,"endsolid",sizeof("solid")-1);
        do
        {
                fgets(line,sizeof line,fp);//Normal
                sscanf(line,"%s %s %f %f %f",name1,name2,&x,&y,&z);

                if(strcmp(name1,"endsolid")==0)
                    break;
                //printf("%s %s %f %f %f\n",name1,name2,x,y,z);
                fgets(line,sizeof line,fp);//outer loop
                fgets(line,sizeof line,fp);//vertex
                sscanf(line,"%s %f %f %f",name1,&x1,&y1,&z1);
                //printf("%s %f %f %f\n",name1,x1,y1,z1);
                fgets(line,sizeof line,fp);//vertex
                sscanf(line,"%s %f %f %f",name1,&x2,&y2,&z2);
                //printf("%s %f %f %f\n",name1,x2,y2,z2);
                fgets(line,sizeof line,fp);//vertex
                sscanf(line,"%s %f %f %f",name1,&x3,&y3,&z3);
                //printf("%s %f %f %f\n",name1,x3,y3,z3);
                fgets(line,sizeof line,fp);//outer loop
                fgets(line,sizeof line,fp);//endfacet
                sscanf(line,"%s %f %f %f",name1,&x,&y,&z);
                //printf("%s\n",name1);
                //V=(-x3*y2*z1+x2*y3*z1+x3*y1*z2-x1*y3*z2-x2*y1*z3+x1*y2*z3)/6;
                //    Vt=Vt+V;
                //printf("Vol2: %f\n",Vt);
                i++;
        }
        while(strcmp(name1,"endsolid")!=0);
        //printf("Volumen: %f\n",Vt);
        //exit(0);
	}
printf("Eolecture");
}


void Bad::draw()
{
    triangle *old_solid;
    old_solid=solid;

    glColor3f(R/255, G/255, B/255);
    GLfloat qaBlack[]= {0,0,0,1};
    GLfloat qaGreen[]= {0,1,0,1};
    GLfloat qaWhite[]= {1,1,1,1};

    glMaterialfv(GL_FRONT,GL_AMBIENT,qaGreen);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,qaGreen);
    glMaterialfv(GL_FRONT,GL_SPECULAR,qaWhite);
    glMaterialf(GL_FRONT,GL_SHININESS,60.0);

       /* //if(select==true)
        {
            glMatrixMode(GL_MODELVIEW);
            // posX=posX+offX*cos(3.1416*degree/180);
            //posY=posY+offY*sin(3.1416*degree/180);printf("D=%i\n",degree);
            //glTranslatef(0,posX,posY);
            glPushMatrix();
            glTranslatef(offX, offY, offZ); // move back to focus of gluLookAt
            glRotatef(degree,1,0,0); //  rotate around center
            glTranslatef(-offX, -offY, -offZ); //move object to center
        }
        */
        //if(select==true)
        {
            glMatrixMode(GL_MODELVIEW);

            glPushMatrix();
            glRotatef(degreeZ,0,0,1);
            glTranslatef(deltaX+deltaX1, deltaY+deltaY1, deltaZ+deltaZ1);

            glTranslatef(offX, offY, offZ);
            glRotatef(degree,1,0,0);
            glTranslatef(-offX, -offY, -offZ); //move object to center

        }

    glBegin(GL_TRIANGLES);
    for(j=0;j<head.number_of_triangles;j++)
   		{
       glNormal3f(solid->Normal[0],solid->Normal[1],solid->Normal[2]);
		glVertex3f(solid->Vertex1[0]+posX,solid->Vertex1[1]+posY,solid->Vertex1[2]);
		glVertex3f(solid->Vertex2[0]+posX,solid->Vertex2[1]+posY,solid->Vertex2[2]);
		glVertex3f(solid->Vertex3[0]+posX,solid->Vertex3[1]+posY,solid->Vertex3[2]);
        solid++;
   		}

        glEnd();
       // if(select==true)
        {

               glPopMatrix();
        }
        solid=old_solid;

}

Bad::~Bad()
{

};

void Bad::rotatem()
{

}
