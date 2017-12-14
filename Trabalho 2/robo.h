//AUTORES: Felipe Chabatura e Leonardo Tironi;
#ifndef ROBO_H
#define ROBO_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#define MAXLAB 30
#define SPEED 0.10;
#define INF 112345
#define CAMTURN 0.111111111 * 2
#define ROBOTURN 10

typedef struct{
  int x, y;
  double speedx, speedy;
  char nextdir;
}point_t;

void Inicializa(void);
GLUquadricObj *quadric(void);
void getViewPos(unsigned char key, int x, int y);
void desenhaCubo(int posi, int posj);
void desenhaCuboRobo();
void desenhaRobo();
void desenhaParede(void);
void desenhaObjetos(void);
void desenha(void);
void Redesenha(int);
void AlteraTamanhoJanela(GLsizei w, GLsizei h);
///////////////////////////////////////////////////////////////////
void loadTexture(const char * imagepath, int i);
///////////////////////////////////////////////////////////////////
#endif
