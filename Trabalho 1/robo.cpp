//AUTORES: Felipe Chabatura e Leonardo Tironi;
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>

#define MAXLAB 30
#define SPEED 0.10;
#define INF 112345

typedef struct{
  int x, y;
  double speedx, speedy;
  char nextdir;
}point_t;

point_t points[30];
int looktop = 0, iPoint = 0, grau = 0, count = 0, rotation = 0;
double robox = 5, roboy = -2;
GLdouble rotatextop = 0;
GLdouble rotateytop = 0;
GLdouble rotateztop = 46;

GLdouble centerxthird = 0;
GLdouble centerythird = 1;
GLdouble centerzthird = 0;

GLdouble rotatexthird = 0;
GLdouble rotateythird = 0;
GLdouble rotatezthird = 46;

GLfloat PI = 3.141592; // Valor de PI.
GLfloat x, y, z, alpha, beta; // Variáveis para coordenadas e ângulos.
GLfloat radius = 0.3;
GLfloat hRotate = 0;
int gradation = 50; // Quantidade de fatias.
GLfloat move = PI/gradation;
GLfloat speedx = 0;
GLfloat speedy = SPEED;
GLdouble xAdjust = 0;
GLdouble yAdjust = -2;


//Matriz do Labirinto
int labirinto[MAXLAB][MAXLAB] = {
// 0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //0
  {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1}, //1
  {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1}, //2
  {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1}, //3
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1}, //4
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1}, //5
  {1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1}, //6
  {1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1}, //7
  {1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1}, //8
  {1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1}, //9
  {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1}, //0
  {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1}, //1
  {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1}, //2
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1}, //3
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1}, //4
  {1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}, //5
  {1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}, //6
  {1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1}, //7
  {1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1}, //8
  {1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1}, //9
  {1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1}, //0
  {1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1}, //1
  {1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1}, //2
  {1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1}, //3
  {1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1}, //4
  {1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1}, //5
  {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1}, //6
  {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, //7
  {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, //8
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}  //9
};

// Inicializa par?metros de rendering
void Inicializa(void) {
	// Define a cor de fundo da janela de visualização como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
  points[0].x = INF; points[0].y = 14; points[0].speedx = SPEED; points[0].speedy = 0; points[0].nextdir = 'D';
  points[1].x = 10; points[1].y = INF; points[1].speedx = -SPEED; points[1].speedy = 0; points[1].nextdir = 'A';
  points[2].x = 4; points[1].y = INF; points[2].speedx = 0; points[2].speedy = -SPEED; points[2].nextdir = 'E';
  points[3].x = INF; points[3].y = 8; points[3].speedx = SPEED; points[3].speedy = 0; points[3].nextdir = 'E';
  points[4].x = 14; points[4].y = INF; points[4].speedx = 0; points[4].speedy = -SPEED; points[4].nextdir = 'D';
  points[6].x = INF; points[6].y = 4; points[6].speedx = SPEED; points[6].speedy = 0; points[6].nextdir = 'E';
  points[7].x = 28; points[7].y = INF; points[7].speedx = 0; points[7].speedy = SPEED; points[7].nextdir = 'E';
  points[8].x = INF; points[8].y = 13; points[8].speedx = -SPEED; points[8].speedy = 0; points[8].nextdir = 'E'; //
  points[9].x = 20; points[9].y = INF; points[9].speedx = 0; points[9].speedy = SPEED; points[9].nextdir = 'D';
  points[10].x = INF; points[10].y = 22; points[10].speedx = SPEED; points[10].speedy = 0; points[10].nextdir = 'D';
  points[11].x = 26; points[11].y = INF; points[11].speedx = -SPEED; points[11].speedy = 0;  points[11].nextdir = 'A';
  points[12].x = 17; points[12].y = INF; points[12].speedx = SPEED; points[12].speedy = 0;  points[12].nextdir = 'A';
  points[13].x = 21; points[13].y = INF; points[13].speedx = 0; points[13].speedy = -SPEED;  points[13].nextdir = 'D';
  points[14].x = INF; points[14].y = 17; points[14].speedx = -SPEED; points[14].speedy = 0;  points[14].nextdir = 'D';
  points[15].x = 13; points[15].y = INF; points[15].speedx = 0; points[15].speedy = SPEED;  points[15].nextdir = 'D';
  points[16].x = INF; points[16].y = 22; points[16].speedx = -SPEED; points[16].speedy = 0;  points[16].nextdir = 'E';
  points[17].x = 3; points[17].y = INF; points[17].speedx = 0; points[17].speedy = SPEED;  points[17].nextdir = 'D';
  points[18].x = INF; points[18].y = 25; points[18].speedx = -SPEED; points[18].speedy = 0; points[18].nextdir = 'E';
  points[19].x = 1; points[19].y = INF; points[19].speedx = 0; points[19].speedy = SPEED;  points[19].nextdir = 'D';
  points[20].x = INF; points[20].y = 28; points[20].speedx = SPEED; points[20].speedy = 0; points[20].nextdir = 'D';
  points[21].x = 8; points[21].y = INF; points[21].speedx = 0; points[21].speedy = -SPEED; points[21].nextdir = 'D';
  points[22].x = INF; points[22].y = 24; points[22].speedx = SPEED; points[22].speedy = 0; points[22].nextdir = 'E';
  points[23].x = 20; points[23].y = INF; points[23].speedx = 0; points[23].speedy = SPEED; points[23].nextdir = 'E';
  points[24].x = INF; points[24].y = 28; points[24].speedx = -SPEED; points[24].speedy = 0;points[24].nextdir = 'E';
  points[25].x = 17; points[25].y = INF; points[25].speedx = SPEED; points[25].speedy = 0; points[25].nextdir = 'A';
  points[26].x = 20; points[26].y = INF; points[26].speedx = 0; points[26].speedy = -SPEED;points[26].nextdir = 'D';
  points[27].x = INF; points[27].y = 24; points[27].speedx = SPEED; points[27].speedy = 0; points[27].nextdir = 'E';
  points[28].x = 28; points[28].y = INF; points[28].speedx = 0; points[28].speedy = SPEED; points[28].nextdir = 'E';
  points[29].x = INF; points[29].y = 31; points[29].speedx = 0; points[27].speedy = 0; points[29].nextdir = 'E';

}

GLUquadricObj *quadric(void){
  GLUquadricObj *obj = gluNewQuadric();
  gluQuadricDrawStyle(obj, GLU_FILL);
  gluQuadricOrientation(obj, GLU_OUTSIDE);
  gluQuadricNormals(obj, GLU_SMOOTH);
  return obj;
}

void getViewPos(unsigned char key, int x, int y){
  if(looktop){
    if(key == '+') rotateztop -= 1;
    if(key == '-') rotateztop += 1;
    if(key == '8') rotateytop += 1;
    if(key == '2') rotateytop -= 1;
    if(key == '4') rotatextop -= 1;
    if(key == '6') rotatextop += 1;
  }
  else{
    if(key == '+') rotatezthird -= 1;
    if(key == '-') rotatezthird += 1;
    if(key == '8') rotateythird += 1;
    if(key == '2') rotateythird -= 1;
    if(key == '4') rotatexthird -= 1;
    if(key == '6') rotatexthird += 1;
  }
  if(key == '0') looktop = looktop ? 0 : 1;
}

//Função para desenhar o cubo.
void desenhaCubo(int posi, int posj) {
  int i, j, pos = 0;
  GLfloat cords[8][3] = {
    {0, 0, 0}, //0
    {1, 0, 0}, //1
    {0, 0, 1}, //2
    {1, 0, 1}, //3
    {0, 1, 0}, //4
    {1, 1, 0}, //5
    {0, 1, 1}, //6
    {1, 1, 1} //7
  };
  GLfloat cores[7][3] = {
    {0.2, 0.8, 0.2},   //"Cima"
    {0.13, 0.55, 0.13},      //"esquerda"
    {0.13, 0.55, 0.13},   //"Embaixo"
    {0.13, 0.55, 0.13},   //"Direita"
    {0.13, 0.55, 0.13},   //"Atras"
    {0.13, 0.55, 0.13},    //"frente"MAXLAB
    {1, 0, 0}
  };
  int cr[24] = {
    2, 3, 7, 6,
    2, 0, 4, 6,
    0, 1, 5, 4,
    1, 3, 7, 5,
    6, 7, 5, 4,
    2, 3, 1, 0,
  };
  glBegin(GL_QUADS);
  for (i = 0; i < 6; i++) {
    if(posi == 0 && i == 1) glColor3fv(cores[0]);
    else if(posi == MAXLAB-1 && i == 3) glColor3fv(cores[0]);
    else if(posj == 0 && i == 5) glColor3fv(cores[0]);
    else if(posj == MAXLAB-1 && i == 4) glColor3fv(cores[0]);
    else glColor3fv(cores[i]);
    for (j = 0; j < 4; j++) glVertex3fv(cords[cr[pos++]]);
  }
  glEnd();
}

//Função para desenhar o cubo.
void desenhaCuboRobo() {
  int i, j, pos = 0;
  GLfloat cords[8][3] = {
    {-0.5, -0.5, -0.5}, //0
    {0.5, -0.5, -0.5}, //1
    {-0.5, -0.5, 0.5}, //2
    {0.5, -0.5, 0.5}, //3
    {-0.5, 0.5, -0.5}, //4
    {0.5, 0.5, -0.5}, //5
    {-0.5, 0.5, 0.5}, //6
    {0.5, 0.5, 0.5} //7
  };
  int cr[24] = {
    2, 3, 7, 6,
    2, 0, 4, 6,
    0, 1, 5, 4,
    1, 3, 7, 5,
    6, 7, 5, 4,
    2, 3, 1, 0,
  };
  glBegin(GL_QUADS);
  for (i = 0; i < 6; i++) {
    //glColor3fv(cores[i]);
    for (j = 0; j < 4; j++) glVertex3fv(cords[cr[pos++]]);
  }
  glEnd();
}

void desenhaRobo(){
  //printf("%d %d %c\n", count, grau, points[iPoint].nextdir);
  if(count){grau += rotation; count--;}
  glRotatef(grau, 0, 0, 1);
  glTranslatef(0, 0, 0.3);
  //Cabeca
  glPushMatrix();
  glRotatef(hRotate += 0.5, 0.0, 0.0, 1.0);
  glScalef(0.3, 0.3, 0.25);
  glColor3f(0.41f, 0.41f, 0.41f);
  glTranslatef(0, 0, 3);
  desenhaCuboRobo();
  glPopMatrix();

  //Olho esquerdo
  glPushMatrix();
  glRotatef(hRotate, -0.05, 0, 50);
  glColor3f(0, 0, 0);
  glTranslatef(0.151, 0.05, 0.85);
  glRotatef(90, 0, 1, 0);
  GLUquadricObj * eyes = quadric();
  gluDisk(eyes, 0, 0.02, 25, 1);
  glPopMatrix();

  //Olho direito
  glPushMatrix();
  glRotatef(hRotate, -0.05, 0, 50);
  glColor3f(0, 0, 0);
  glTranslatef(0.151, -0.05, 0.85);
  glRotatef(90, 0, 1, 0);
  gluDisk(eyes, 0, 0.02, 25, 1);
  glPopMatrix();

  //Boca
  glPushMatrix();
  glRotatef(hRotate+=1, -0.05, 0, 4);
  glColor3f(0, 0, 0);
  glTranslatef(0.1, 0, 0.75);
  glRotatef(90, 0, 1, 0);
  glScalef(0.08, 0.15, 0.1);
  desenhaCuboRobo();
  glPopMatrix();

  //Pescoco
  glPushMatrix();
  glScalef(0.1, 0.1, 0.3);
  glColor3f(0.41f, 0.41f, 0.41f);
  glTranslatef(0, 0.1, 1.6);
  desenhaCuboRobo();
  glPopMatrix();

  //Tronco
  glPushMatrix();
  glScalef(0.5, 0.5, 0.5);
  glColor3f(0.41f, 0.41f, 0.41f);
  glTranslatef(0, 0, 0.35);
  desenhaCuboRobo();
  glPopMatrix();

  //Braco esquerdo
  glPushMatrix();
  glScalef(0.1, 0.1, 0.5);
  glColor3f(0.7f, 0.13f, 0.13f);
  glTranslatef(0, 3, 0.3);
  desenhaCuboRobo();
  glPopMatrix();

  //Braco direito
  glPushMatrix();
  glScalef(0.1, 0.1, 0.5);
  glColor3f(0.7f, 0.13f, 0.13f);
  glTranslatef(0, -3, 0.3);
  desenhaCuboRobo();
  glPopMatrix();

  //Roda
  glPushMatrix();
  glTranslatef(0, 0, 0);
  glRotatef(-90, 1, 0, 0);
  radius = 0.3;
  for (alpha = 0.0; alpha < PI; alpha += PI/gradation) {
    glBegin(GL_TRIANGLE_STRIP);
    for (beta = 0.0+move; beta < 2.1 * PI + move; beta += PI/gradation) {
      if(beta <= PI + move && beta >= move)
	glColor3f(0.8f, 0.47f, 0.13f);
      else
	glColor3f(0.73f, 0.33f, 0.83f);
      x = radius*cos(beta)*sin(alpha);
      y = radius*sin(beta)*sin(alpha);
      z = radius*cos(alpha);
      if(alpha >= PI/3 && alpha <= 2*PI/3)
	glVertex3f(x, y, z);
      x = radius*cos(beta)*sin(alpha + PI/gradation);
      y = radius*sin(beta)*sin(alpha + PI/gradation);
      z = radius*cos(alpha + PI/gradation);
      if(alpha >= PI/3 && alpha <= 2*PI/3)
	glVertex3f(x, y, z);
    }
  }
  move += PI/gradation;
  glEnd();
  glPopMatrix();
}

void desenhaParede(void) {
  int i, j;
  for (i = 0; i < MAXLAB; i++) {
    for (j = 0; j < MAXLAB; j++) {
      if (labirinto[i][j]) {
      	glPushMatrix();
      	glScalef(1, 1, 4);
      	glTranslatef(i - MAXLAB/2, j - MAXLAB / 2, 0);
      	desenhaCubo(i, j);
      	glPopMatrix();
      }
    }
  }
}

/*void desenhaObjetos(void) {
  glTranslatef(10 - (MAXLAB/2), 12 - (MAXLAB/2), 0.3);
  //Cabeca
  glPushMatrix();
  glScalef(0.3, 0.3, 0.25);
  glColor3f(0.72f, 0.25f, 0.05f);
  glTranslatef(0, 0, 3);
  desenhaCuboRobo();
  glPopMatrix();

  //Olho esquerdo
  glPushMatrix();
  glColor3f(0, 0, 0);
  glTranslatef(0.151, 0.05, 0.85);
  glRotatef(90, 0, 1, 0);
  GLUquadricObj * eyes = quadric();
  gluDisk(eyes, 0, 0.02, 25, 1);
  glPopMatrix();

  //Olho direito
  glPushMatrix();
  glColor3f(0, 0, 0);
  glTranslatef(0.151, -0.05, 0.85);
  glRotatef(90, 0, 1, 0);
  gluDisk(eyes, 0, 0.02, 25, 1);
  glPopMatrix();

  //Boca
  glPushMatrix();
  glColor3f(0, 0, 0);
  glTranslatef(0.1, 0, 0.75);
  glRotatef(90, 0, 1, 0);
  glScalef(0.08, 0.15, 0.1);
  desenhaCuboRobo();
  glPopMatrix();

  //Pescoco
  glPushMatrix();
  glScalef(0.1, 0.1, 0.3);
  glColor3f(0.72f, 0.25f, 0.05f);
  glTranslatef(0, 0.1, 1.6);
  desenhaCuboRobo();
  glPopMatrix();

  //Tronco
  glPushMatrix();
  glScalef(0.5, 0.5, 0.5);
  glColor3f(0.72f, 0.25f, 0.05f);
  glTranslatef(0, 0, 0.35);
  desenhaCuboRobo();
  glPopMatrix();

  glTranslatef(20 - (MAXLAB/2), 19 - (MAXLAB/2), 0);
  radius = 1;
  glPushMatrix();
  glTranslatef(2, 0, 0);
  //glRotatef(-90, 1, 0, 0);
  for (alpha = 0.0; alpha < PI; alpha += PI/gradation) {
    glBegin(GL_TRIANGLE_STRIP);
    for (beta = 0.0; beta < 2.1 * PI; beta += PI/gradation) {
      glColor3f(0.66f, 0.66f, 0.66f);
      x = radius*cos(beta)*sin(alpha);
      y = radius*sin(beta)*sin(alpha);
      z = radius*cos(alpha);
      if(alpha >= PI/3 && alpha <= 2*PI/3)
	glVertex3f(x, y, z);
      x = radius*cos(beta)*sin(alpha + PI/gradation);
      y = radius*sin(beta)*sin(alpha + PI/gradation);
      z = radius*cos(alpha + PI/gradation);
      if(alpha >= PI/3 && alpha <= 2*PI/3)
	glVertex3f(x, y, z);
    }
  }
  glEnd();
  glPopMatrix();

  //Fonte mais em cima
  radius = 0.65;
  glPushMatrix();
  glTranslatef(2, 0, 0.70);
  //glRotatef(-90, 1, 0, 0);
  for (alpha = 0.0; alpha < PI; alpha += PI/gradation) {
    glBegin(GL_TRIANGLE_STRIP);
    for (beta = 0.0; beta < 2.1 * PI; beta += PI/gradation) {
      glColor3f(0.66f, 0.66f, 0.66f);
      x = radius*cos(beta)*sin(alpha);
      y = radius*sin(beta)*sin(alpha);
      z = radius*cos(alpha);
      if(alpha >= PI/3 && alpha <= 2*PI/3)
	glVertex3f(x, y, z);
      x = radius*cos(beta)*sin(alpha + PI/gradation);
      y = radius*sin(beta)*sin(alpha + PI/gradation);
      z = radius*cos(alpha + PI/gradation);
      if(alpha >= PI/3 && alpha <= 2*PI/3)
	glVertex3f(x, y, z);
    }
  }
  glEnd();
  glPopMatrix();

  // Agua e pau
  glPushMatrix();
  glTranslatef(2, 0, 0.40);
  GLUquadricObj * water = quadric();
  glColor3f(0.69, 0.93, 0.93);
  gluDisk(water, 0, .90, 25, 1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(2, 0, 0.80);
  gluDisk(water, 0, 0.60, 25, 1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.66, 0.66, 0.66);
  glTranslatef(2, 0, 0.40);
  gluCylinder(water, 0.20, 0.1, 1, 25, 1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.69, 0.93, 0.93);
  glTranslatef(2, 0, 1.37);
  gluDisk(water, 0, 0.1, 25, 1);
  glPopMatrix();
}*/


void desenha(void) {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // Limpa a janela de visualização:void desenha(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(looktop)
    gluLookAt(rotatextop, rotateytop, rotateztop, 0, 0, 0, 0, 1, 0);
  else{
    //gluLookAt(robox-(MAXLAB/2), roboy-(MAXLAB/2)-3, 3, robox-(MAXLAB/2), roboy-(MAXLAB/2), centerzthird, 0, 1, 0); }
    if(count){
      if(points[iPoint-1].nextdir == 'A')
        if(robox-(MAXLAB/2) >= robox-(MAXLAB/2) + xAdjust) xAdjust += 0.111111111;
        else if(robox-(MAXLAB/2) <= robox-(MAXLAB/2) + xAdjust) xAdjust +=  0.111111111;
        else if(roboy-(MAXLAB/2) >= roboy-(MAXLAB/2) + yAdjust) yAdjust +=  0.111111111;
        else yAdjust += 0.111111111;
      else if(speedy != 0){
        if(robox-(MAXLAB/2) >= robox-(MAXLAB/2) + xAdjust){
          if(points[iPoint-1].nextdir == 'D'){ xAdjust += 0.111111111; yAdjust += 0.111111111;}
          else if(points[iPoint-1].nextdir == 'E'){ xAdjust += 0.111111111; yAdjust -= 0.111111111;}
        }
        else{
          if(points[iPoint-1].nextdir == 'D') { xAdjust -= 0.111111111; yAdjust -= 0.111111111;}
          else if(points[iPoint-1].nextdir == 'E'){ xAdjust -= 0.111111111; yAdjust += 0.111111111;}
        }
      }
      else if(speedx != 0){
        if(roboy-(MAXLAB/2) >= roboy-(MAXLAB/2) + yAdjust){;
          if(points[iPoint-1].nextdir == 'D'){ yAdjust += 0.111111111; xAdjust -= 0.111111111; }
          else if(points[iPoint-1].nextdir == 'E') { yAdjust += 0.111111111; xAdjust += 0.111111111; }
        }
        else{
          if(points[iPoint-1].nextdir == 'D'){ yAdjust -= 0.111111111; xAdjust += 0.111111111; }
          else if(points[iPoint-1].nextdir == 'E') { yAdjust -= 0.111111111; xAdjust -= 0.111111111; }
        }
      }
    }
    //printf("%lf %lf", robox-(MAXLAB/2)+xAdjust, roboy-(MAXLAB/2)+yAdjust);
    gluLookAt(robox-(MAXLAB/2)+xAdjust, roboy-(MAXLAB/2)+yAdjust, 3, robox-(MAXLAB/2), roboy-(MAXLAB/2), centerzthird, 0, 0, 1);
  }
  //if(count) if()
  //gluLookAt(rotateqtop)
  //INICIO DO CHAO
  glPushMatrix();
  //Desenhar o chao;
  glColor3f(0, 0.39, 0);
  glBegin(GL_QUADS);
  glVertex3f(-MAXLAB/2, -MAXLAB/2 - 3, -0.001);
  glVertex3f(MAXLAB/2, -MAXLAB/2 - 3, -0.001);
  glVertex3f(MAXLAB/2, MAXLAB/2 + 3, -0.001);
  glVertex3f(-MAXLAB/2, MAXLAB/2 + 3, -0.001);
  glEnd();


  glPopMatrix();
  //FIM DO CHAO

  desenhaParede();

  glPushMatrix();
  robox += speedx; roboy += speedy;
  if((int)robox == points[iPoint].x || (int)roboy == points[iPoint].y){
    speedx = points[iPoint].speedx;
    speedy = points[iPoint].speedy;
    if(points[iPoint].nextdir == 'D'){ count = 18; rotation = -5; }
    else if(points[iPoint].nextdir == 'E'){ count = 18; rotation = 5; }
    else if(points[iPoint].nextdir == 'A'){ count = 36; rotation = 5; }
    if(iPoint < 29) iPoint++;
    if(iPoint == 5) iPoint++;
  }
  glTranslatef(robox - MAXLAB/2, roboy - MAXLAB / 2, 0);
  glScalef(1, 1, 1);
  glRotatef(90, 0, 0, 1);
  desenhaRobo();
  glPopMatrix();
  //desenhaObjetos();
  glutSwapBuffers();
  glFlush();
}

void Redesenha(int) {
  glutPostRedisplay();
  desenha();
  glutTimerFunc(60,Redesenha,1);
}


// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
	// Evita a divisao por zero
	if (h == 0) h = 1;
	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);
	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, ((GLfloat)w / (GLfloat)h), 1.0f, 100.0f);
}


int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(1366, 768);
  glutCreateWindow ("Labirinto");
  glutKeyboardFunc(getViewPos);
  glutTimerFunc(60,Redesenha,1);
  glutDisplayFunc(desenha);
  glutReshapeFunc(AlteraTamanhoJanela);
  Inicializa();
  glutMainLoop();
  return 0;
}
