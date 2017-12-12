#include "robo.h"

GLdouble rotacao_roda = 0;
GLdouble grau_roda = 0;
GLdouble base_grau_roda = 0.01745;

point_t points[30];
int look = 0, iPoint = 0, grau = 0, count = 0, rotation = 0;
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

// Inicializa parametros de rendering
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

//Desenha quadrica
GLUquadricObj *quadric(void){
  GLUquadricObj *obj = gluNewQuadric();
  gluQuadricDrawStyle(obj, GLU_FILL);
  gluQuadricOrientation(obj, GLU_OUTSIDE);
  gluQuadricNormals(obj, GLU_SMOOTH);
  return obj;
}


//Captura comandos do teclado
void getViewPos(unsigned char key, int x, int y){
  if(look){
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
  if(key == 'q') look = 1;
  if(key == 'w') look = 2;
  if(key == 'e') look = 3;
  if(key == 'r') look = 4;
  if(key == 't') look = 5;
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
    {0.13, 0.55, 0.13},    //"esquerda"
    {0.13, 0.55, 0.13},   //"Embaixo"
    {0.13, 0.55, 0.13},   //"Direita"
    {0.13, 0.55, 0.13},   //"Atras"
    {0.13, 0.55, 0.13},   //"frente"MAXLAB
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

void desenhaPau(int angulo, int rotacao_roda, int y){
  GLUquadricObj * base = quadric();
  glPushMatrix();
  glTranslatef(-4, y, 7);
  glRotatef(angulo, 0, 1, 0);
  glRotatef(rotacao_roda, 0, 1, 0);
  gluCylinder(base, 0.1, 0.1, 6, 50, 25);
  glPopMatrix();
}

void desenhaPau2(int i, GLdouble grau_roda){
  GLUquadricObj * base = quadric();
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  glTranslatef(-4 + sin(grau_roda+i*base_grau_roda)*5.9, 7 + cos(grau_roda+i*base_grau_roda)*5.9, -1);
  gluCylinder(base, 0.1, 0.1, 4, 50, 25);
  glPopMatrix();
}

void desenhaPau3(int i, GLdouble grau_roda, int rotacao_roda, int y){
  GLUquadricObj * base = quadric();
  glPushMatrix();
  glTranslatef(-4 + sin(grau_roda + i * base_grau_roda) * 5.9, y, 7 + cos(grau_roda + i * base_grau_roda)*5.9);
  glRotatef(rotacao_roda, 0, 1, 0);
  glRotatef(113 + i, 0, 1, 0);
  gluCylinder(base, 0.1, 0.1, 4.6, 50, 25);
  glPopMatrix();
}

void desenhaCadeira(int i, GLdouble grau_roda){

  glPushMatrix();
  glColor3f(0.41f, 0.41f, 0.41f);
  glTranslatef(-4 + sin(grau_roda + i * base_grau_roda) * 5.9, -1, 6.75 + cos(grau_roda + i * base_grau_roda) * 5.9);
  glScalef(0.1, 0.75, 0.5);
  desenhaCuboRobo();
  //gluCylinder(base, 0.1, 0.1, 6, 50, 25);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(-3.75 + sin(grau_roda + i * base_grau_roda) * 5.9, -1, 6.5 + cos(grau_roda + i * base_grau_roda) * 5.9);
  glScalef(0.5, 0.5, 0.1);
  desenhaCuboRobo();
  glPopMatrix();
}
void desenhaRodaGigante(){
  glTranslatef(-20, 0, 0);
  glRotatef(90, 0, 0, 1);
  glColor3f(0.43f, 0.21f, 0.01f);
  glPushMatrix();
  glTranslatef(0, 0, 3.3);
  glRotatef(45, 0, 1, 0);
  glScalef(10, 0.3, 0.3);
  desenhaCuboRobo();
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0, -2, 3.3);
  glRotatef(45, 0, 1, 0);
  glScalef(10, 0.3, 0.3);
  desenhaCuboRobo();
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(-8, 0, 3.3);
  glRotatef(-45, 0, 1, 0);
  glScalef(10, 0.3, 0.3);
  desenhaCuboRobo();
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-8, -2, 3.3);
  glRotatef(-45, 0, 1, 0);
  glScalef(10, 0.3, 0.3);
  desenhaCuboRobo();
  //gluCylinder(base, 0.25, 0.25, 2, 50, 25);
  glPopMatrix();

  GLUquadricObj * base = quadric();
  glPushMatrix();
  glTranslatef(-4, 1, 7);
  glRotatef(90, 1, 0, 0);
  gluCylinder(base, 0.6, 0.6, 4, 50, 25);
  glPopMatrix();

  glColor3f(0.55f, 0.27f, 0.07f);
  
  glPushMatrix();
  glTranslatef(-4, 1, 7);
  glRotatef(90, 1, 0, 0);
  gluDisk(base, 0, 0.6, 50, 25);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(-4, -3, 7);
  glRotatef(90, 1, 0, 0);
  gluDisk(base, 0, 0.6, 50, 25);
  glPopMatrix();


  
  for(int i = 0; i < 360; i += 45) desenhaPau(i, rotacao_roda, -3);
  for(int i = 0; i < 360; i += 45) desenhaPau(i, rotacao_roda, 1);
 
  for(int i = 0; i < 360; i += 45) desenhaPau2(i, grau_roda);

  for(int i = 0; i < 360; i += 45) desenhaPau3(i, grau_roda, rotacao_roda, -3);
  for(int i = 0; i < 360; i += 45) desenhaPau3(i, grau_roda, rotacao_roda, 1);
  
  for(int i = 0; i < 360; i += 45) desenhaCadeira(i, grau_roda);
  grau_roda += 0.01745;
  rotacao_roda += 1;
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
  glTranslatef(0, 0, 5);
  desenhaCuboRobo();
  glPopMatrix();

	//OLHOS
	GLUquadricObj * eyes = quadric();
  //Olho esquerdo
  glPushMatrix();
  glRotatef(hRotate, -0.05, 0, 50);
	//Exterior
	glColor3f(1, 1, 1);
  glTranslatef(0.151, 0.08, 1.3);
  glRotatef(90, 0, 1, 0);
  gluDisk(eyes, 0, 0.04, 25, 1);
	//Interior
	glTranslatef(0.0, 0.0, 0.001);
	glColor3f(1, 0.27, 0);
	gluDisk(eyes, 0, 0.02, 25, 1);
  glPopMatrix();

  //Olho direito
  glPushMatrix();
  glRotatef(hRotate, -0.05, 0, 50);
	//Exterior
	glColor3f(1, 1, 1);
  glTranslatef(0.151, -0.08, 1.3);
  glRotatef(90, 0, 1, 0);
  gluDisk(eyes, 0, 0.04, 25, 1);
	//Interior
	glTranslatef(0.0, 0.0, 0.001);
	glColor3f(1, 0.27, 0);
	gluDisk(eyes, 0, 0.02, 25, 1);
  glPopMatrix();

  //Boca
  glPushMatrix();
  glRotatef(hRotate+=1, -0.05, 0, 4);
  glColor3f(1, 0.98, 0.98);
  glTranslatef(0.135, 0.0, 1.2);
  glRotatef(90, 0, 1, 0);
  glScalef(0.04, 0.14, 0.001);
  desenhaCuboRobo();
  glPopMatrix();

  //Pescoco
  glPushMatrix();
  glScalef(0.1, 0.1, 0.3);
  glColor3f(0.41f, 0.41f, 0.41f);
  glTranslatef(0, 0.1, 3.5);
  desenhaCuboRobo();
  glPopMatrix();

  //Tronco
  glPushMatrix();
  glScalef(0.5, 0.5, 0.5);
  glColor3f(0.41f, 0.41f, 0.41f);
  glTranslatef(0, 0, 1.5);
  desenhaCuboRobo();
  glPopMatrix();

	//Braco esquerdo
  glPushMatrix();
  glScalef(0.1, 0.1, 0.5);
  glColor3f(1, 0.27, 0);
  glTranslatef(0, 3, 1.3);
  desenhaCuboRobo();
  glPopMatrix();

  //Braco direito
  glPushMatrix();
  glScalef(0.1, 0.1, 0.5);
  glColor3f(1, 0.27, 0);
  glTranslatef(0, -3, 1.3);
  desenhaCuboRobo();
  glPopMatrix();

  //Apoio de roda esquerdo
  glPushMatrix();
  //glScalef(0.01, 0.1, 0.5);
	glColor3f(0.41f, 0.41f, 0.41f);
  glTranslatef(0, 0.2, 0);
	gluCylinder(eyes, 0.03, 0.03, 0.5, 50, 1);
  glPopMatrix();

  //Apoio de roda direito
  glPushMatrix();
  //glScalef(0.01, 0.1, 0.5);
	glColor3f(0.41f, 0.41f, 0.41f);
  glTranslatef(0, -0.2, 0);
	gluCylinder(eyes, 0.03, 0.03, 0.5, 50, 1);
  glPopMatrix();

	//Ligação entre os apoios
  glPushMatrix();
	glRotatef(90, 1, 0, 0);
  //glScalef(0.01, 0.1, 0.5);
	glColor3f(0.41f, 0.41f, 0.41f);
  glTranslatef(0, 0, -0.225);
	gluCylinder(eyes, 0.03, 0.03, 0.45, 50, 1);
  glPopMatrix();

	//Aro 1
  glPushMatrix();
	glColor3f(1, 0.27, 0);
	glRotatef(180, 1, 0, 0);
	glRotatef(62*move, 0, -1, 0);
  //glScalef(0.01, 0.1, 0.5);
  glTranslatef(0, 0, -0.29);
	gluCylinder(eyes, 0.03, 0.03, 0.30, 50, 1);
  glPopMatrix();
	//Aro 2
  glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glRotatef(62*move, 0, -1, 0);
  //glScalef(0.01, 0.1, 0.5);
	glColor3f(1, 0.27, 0);
  glTranslatef(0, 0, -0.05);
	gluCylinder(eyes, 0.03, 0.03, 0.30, 50, 1);
  glPopMatrix();
	//Aro 3
  glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(62*move, 0, 1, 0);
  //glScalef(0.01, 0.1, 0.5);
	glColor3f(1, 0.27, 0);
  glTranslatef(0, 0, -0.01);
	gluCylinder(eyes, 0.03, 0.03, 0.30, 50, 1);
  glPopMatrix();
	//Aro 4
  glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(62*move, 0, 1, 0);
  //glScalef(0.01, 0.1, 0.5);
	glColor3f(1, 0.27, 0);
  glTranslatef(0, 0, -0.29);
	gluCylinder(eyes, 0.03, 0.03, 0.30, 50, 1);
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
	glColor3f(0.47, 0.53, 0.6);
      else
	glColor3f(0.44, 0.5, 0.56);
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

//Desenha as paredes do labirinto
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

void desenhaObjetos(void) {
  glTranslatef(10 - (MAXLAB/2), 12 - (MAXLAB/2), 0.3);
  //Cabeca
  glPushMatrix();
  glRotatef(90, 0, 0, 1);
  glScalef(0.3, 0.3, 0.25);
  glColor3f(0.72f, 0.25f, 0.05f);
  glTranslatef(0, 0, 3);
  desenhaCuboRobo();
  glPopMatrix();

  //Olho esquerdo
  glPushMatrix();
  glRotatef(90, 0, 0, 1);
  glColor3f(0, 0, 0);
  glTranslatef(0.151, 0.05, 0.85);
  glRotatef(90, 0, 1, 0);
  GLUquadricObj * eyes = quadric();
  gluDisk(eyes, 0, 0.02, 25, 1);
  glPopMatrix();
  
  //Olho direito
  glPushMatrix();
  glRotatef(90, 0, 0, 1);
  glRotatef(90, 0, 1, 0);
  glColor3f(0, 0, 0);
  glTranslatef(0.151, -0.05, 0.85);
  gluDisk(eyes, 0, 0.02, 25, 1);
  glPopMatrix();

  //Boca
  glPushMatrix();
  glRotatef(90, 0, 0, 1);
  glColor3f(0, 0, 0);
  glTranslatef(0.11, 0, 0.75);
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
}


void desenha(void) {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // Limpa a janela de visualização:
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(count){
    if(points[iPoint-1].nextdir == 'A')
      if(robox-(MAXLAB/2) >= robox-(MAXLAB/2) + xAdjust) xAdjust += CAMTURN;
      else if(robox-(MAXLAB/2) <= robox-(MAXLAB/2) + xAdjust) xAdjust +=  CAMTURN;
      else if(roboy-(MAXLAB/2) >= roboy-(MAXLAB/2) + yAdjust) yAdjust +=  CAMTURN;
      else yAdjust += CAMTURN;
    else if(speedy != 0){
      if(robox-(MAXLAB/2) >= robox-(MAXLAB/2) + xAdjust){
	if(points[iPoint-1].nextdir == 'D'){ xAdjust += CAMTURN; yAdjust += CAMTURN;}
	else if(points[iPoint-1].nextdir == 'E'){ xAdjust += CAMTURN; yAdjust -= CAMTURN;}
      }
      else{
	if(points[iPoint-1].nextdir == 'D') { xAdjust -= CAMTURN; yAdjust -= CAMTURN;}
	else if(points[iPoint-1].nextdir == 'E'){ xAdjust -= CAMTURN; yAdjust += CAMTURN;}
      }
    }
    else if(speedx != 0){
      if(roboy-(MAXLAB/2) >= roboy-(MAXLAB/2) + yAdjust){;
	if(points[iPoint-1].nextdir == 'D'){ yAdjust += CAMTURN; xAdjust -= CAMTURN; }
	else if(points[iPoint-1].nextdir == 'E') { yAdjust += CAMTURN; xAdjust += CAMTURN; }
      }
      else{
	if(points[iPoint-1].nextdir == 'D'){ yAdjust -= CAMTURN; xAdjust += CAMTURN; }
	else if(points[iPoint-1].nextdir == 'E') { yAdjust -= CAMTURN; xAdjust -= CAMTURN; }
      }
    }
  }

  if(look <= 1){
    printf("%lf %lf %lf\n", rotatextop, rotateytop, rotateztop);
    gluLookAt(rotatextop, rotateytop, rotateztop, 0, 0, 0, 0, 1, 0);
  }
  else if(look == 2){
    gluLookAt(robox-(MAXLAB/2)+xAdjust, roboy-(MAXLAB/2)+yAdjust, 3, robox-(MAXLAB/2), roboy-(MAXLAB/2), centerzthird, 0, 0, 1);
  }
  else if(look == 3) gluLookAt(-40.0, -4.0, 12.0, 0.0, 0.0, 5.0, 0.0, 0.0, 1.0);
  else if(look == 4) gluLookAt(-6.0, 0.0, 2.0, 0.0, -7.0, -2.0, 0.0, 0.0, 1.0);
  else if(look == 5) gluLookAt( -1.0, 3.0, 5.0, 4.0, 1.0, 0.0, 0.0, 0.0, 1.0);
  
    //INICIO DO CHAO
  glPushMatrix();
  //Desenhar o chao;
  glColor3f(0, 0.39, 0);
  glBegin(GL_QUADS);
  glVertex3f(-2*MAXLAB/2, -2*MAXLAB/2 - 3, -0.001);
  glVertex3f(2*MAXLAB/2, -2*MAXLAB/2 - 3, -0.001);
  glVertex3f(2*MAXLAB/2, 2*MAXLAB/2 + 3, -0.001);
  glVertex3f(-2*MAXLAB/2, 2*MAXLAB/2 + 3, -0.001);
  glEnd();


  glPopMatrix();
  //FIM DO CHAO

  desenhaParede();

	glPushMatrix();
  robox += speedx; roboy += speedy;
  if((int)robox == points[iPoint].x || (int)roboy == points[iPoint].y){
    speedx = points[iPoint].speedx;
    speedy = points[iPoint].speedy;
    if(points[iPoint].nextdir == 'D'){ count = 9; rotation = -ROBOTURN; }
    else if(points[iPoint].nextdir == 'E'){ count = 9; rotation = ROBOTURN; }
    else if(points[iPoint].nextdir == 'A'){ count = 18; rotation = ROBOTURN; }
    if(iPoint < 29) iPoint++;
    if(iPoint == 5) iPoint++;
  }
  glTranslatef(robox - MAXLAB/2, roboy - MAXLAB / 2, 0);
  glScalef(1, 1, 1);
  glRotatef(90, 0, 0, 1);
  desenhaRobo();
  glPopMatrix();
  desenhaObjetos();
  desenhaRodaGigante();
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
