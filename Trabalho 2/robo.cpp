#include "robo.h"

int chao = 1; // desenhar o chao ou nao.
GLdouble cam_turnx; // Direcao que a camera se move.
GLdouble cam_turny;
int count_cam;
int finished = 0;

GLfloat lightpos1[] = {0, 0, 0};

GLdouble rotacao_roda = 0;
GLdouble grau_roda = 0;
GLdouble base_grau_roda = 0.01745;

int look = 1, iPoint = 0, grau = 0, count = 0, rotation = 0;
point_t points[30];
double robox = 5, roboy = -2;
GLdouble rotatextop = 0;
GLdouble rotateytop = 0;
GLdouble rotateztop = 46;

GLdouble centerxthird = 0;
GLdouble centerythird = 2;
GLdouble centerzthird = 1;

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

//Variaveis de textura
GLuint tex[2];
float tex_coord = 2;

//Flag da janelinha
int janelinha = 0;

//Matriz do Labirinto
int labirinto[MAXLAB][MAXLAB] = {
// 0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //0
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
  GLfloat AmbientLight1[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat DiffuseLight1[] = {0.5, 0.5, 0.5, 1};
  GLfloat SpecularLight1[] = {0.5, 0.5, 0.5,1};
  GLfloat Specularity[] = {0.5, 0.5, 0.5, 1.0};
  GLint specMaterial = 10;

  // Define a cor de fundo da janela de visualização como preta
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glPolygonMode(GL_FRONT_AND_BACK, GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT1);
  glEnable(GL_COLOR_MATERIAL);

  glMaterialfv(GL_FRONT, GL_SPECULAR, Specularity);
  glMateriali(GL_FRONT, GL_SHININESS, specMaterial);

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight1);

  glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight1);
  glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight1);

  lightpos1[0] = 22;
  lightpos1[1] = 20;
  lightpos1[3] = 30;
  lightpos1[4] = 1;
  glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);

  //Variáveis da transparencia?
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  points[0].x = INF; points[0].y = 14; points[0].speedx = SPEED; points[0].speedy = 0; points[0].nextdir = 1;
  points[1].x = 10; points[1].y = INF; points[1].speedx = -SPEED; points[1].speedy = 0; points[1].nextdir = 11;
  points[2].x = 4; points[1].y = INF; points[2].speedx = 0; points[2].speedy = -SPEED; points[2].nextdir = 8;
  points[3].x = INF; points[3].y = 8; points[3].speedx = SPEED; points[3].speedy = 0; points[3].nextdir = 6;
  points[4].x = 14; points[4].y = INF; points[4].speedx = 0; points[4].speedy = -SPEED; points[4].nextdir = 3;
  points[6].x = INF; points[6].y = 4; points[6].speedx = SPEED; points[6].speedy = 0; points[6].nextdir = 6;
  points[7].x = 28; points[7].y = INF; points[7].speedx = 0; points[7].speedy = SPEED; points[7].nextdir = 7;
  points[8].x = INF; points[8].y = 13; points[8].speedx = -SPEED; points[8].speedy = 0; points[8].nextdir = 5; //
  points[9].x = 20; points[9].y = INF; points[9].speedx = 0; points[9].speedy = SPEED; points[9].nextdir = 4;
  points[10].x = INF; points[10].y = 22; points[10].speedx = SPEED; points[10].speedy = 0; points[10].nextdir = 1;
  points[11].x = 26; points[11].y = INF; points[11].speedx = -SPEED; points[11].speedy = 0;  points[11].nextdir = 11;
  points[12].x = 17; points[12].y = INF; points[12].speedx = SPEED; points[12].speedy = 0;  points[12].nextdir = 12;
  points[13].x = 21; points[13].y = INF; points[13].speedx = 0; points[13].speedy = -SPEED;  points[13].nextdir = 3;
  points[14].x = INF; points[14].y = 17; points[14].speedx = -SPEED; points[14].speedy = 0;  points[14].nextdir = 2;
  points[15].x = 13; points[15].y = INF; points[15].speedx = 0; points[15].speedy = SPEED;  points[15].nextdir = 4;
  points[16].x = INF; points[16].y = 22; points[16].speedx = -SPEED; points[16].speedy = 0;  points[16].nextdir = 5;
  points[17].x = 3; points[17].y = INF; points[17].speedx = 0; points[17].speedy = SPEED;  points[17].nextdir = 4;
  points[18].x = INF; points[18].y = 25; points[18].speedx = -SPEED; points[18].speedy = 0; points[18].nextdir = 5;
  points[19].x = 1; points[19].y = INF; points[19].speedx = 0; points[19].speedy = SPEED;  points[19].nextdir = 4;
  points[20].x = INF; points[20].y = 28; points[20].speedx = SPEED; points[20].speedy = 0; points[20].nextdir = 1;
  points[21].x = 8; points[21].y = INF; points[21].speedx = 0; points[21].speedy = -SPEED; points[21].nextdir = 3;
  points[22].x = INF; points[22].y = 24; points[22].speedx = SPEED; points[22].speedy = 0; points[22].nextdir = 6;
  points[23].x = 20; points[23].y = INF; points[23].speedx = 0; points[23].speedy = SPEED; points[23].nextdir = 7;
  points[24].x = INF; points[24].y = 28; points[24].speedx = -SPEED; points[24].speedy = 0;points[24].nextdir = 5;
  points[25].x = 17; points[25].y = INF; points[25].speedx = SPEED; points[25].speedy = 0; points[25].nextdir = 12;
  points[26].x = 20; points[26].y = INF; points[26].speedx = 0; points[26].speedy = -SPEED;points[26].nextdir = 3;
  points[27].x = INF; points[27].y = 24; points[27].speedx = SPEED; points[27].speedy = 0; points[27].nextdir = 6;
  points[28].x = 28; points[28].y = INF; points[28].speedx = 0; points[28].speedy = SPEED; points[28].nextdir = 7;
  points[29].x = INF; points[29].y = 31; points[29].speedx = 0; points[29].speedy = 0; points[29].nextdir = 1;
  points[29].x = INF; points[30].y = 31; points[30].speedx = 0; points[30].speedy = 0; points[30].nextdir = 3;
  points[29].x = INF; points[31].y = 31; points[31].speedx = 0; points[31].speedy = 0; points[31].nextdir = 2;
  points[29].x = INF; points[32].y = 31; points[32].speedx = 0; points[32].speedy = 0; points[32].nextdir = 4;

  //Coisas de textura
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  //Cria duas texturas do opengl
  glGenTextures(1, tex);
  loadTexture("./minegrama.bmp", 0);
  loadTexture("./wood.bmp", 1);
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
  if(key == 'q' || key == '/') look = 1;
  if(key == 'w' || key == ',') look = 2;
  if(key == 'e' || key == '.') look =  look == 3 ? 6 : 3;
  if(key == 'r' || key == 'p') look = 4;
  if(key == 't' || key == 'y') look =  look == 5 ? 7 : 5 ;
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
    {0.49, 0.29, 0},   //"Cima"
    {0.49, 0.29, 0},    //"esquerda"
    {0.49, 0.29, 0},   //"Embaixo"
    {0.49, 0.29, 0},   //"Direita"
    {0.49, 0.29, 0},   //"Atras"
    {0.49, 0.29, 0},   //"frente"MAXLAB
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
    for (j = 0; j < 4; j++){
      if(pos >= 0 && pos < 4) glNormal3f(0, -1, 0);
      if(pos >= 4 && pos < 8) glNormal3f(-1, 0, 0);
      if(pos >= 8 && pos < 12) glNormal3f(0, 1, 0);
      if(pos >= 12 && pos < 16) glNormal3f(1, 0, 0);
      if(pos >= 16 && pos < 20) glNormal3f(0, 0, 1);
      if(pos >= 20 && pos < 24) glNormal3f(0, 0, -1);
      //Isso aqui eh pras textura
      if(j == 0) glTexCoord2f(-tex_coord, -tex_coord);
      else if(j == 1) glTexCoord2f(tex_coord, -tex_coord);
      else if(j == 2) glTexCoord2f(tex_coord, tex_coord);
      else glTexCoord2f(-tex_coord, tex_coord);
      glVertex3fv(cords[cr[pos++]]);
    }
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
    for (j = 0; j < 4; j++){
      if(pos >= 0 && pos < 4) glNormal3f(0, -1, 0);
      if(pos >= 4 && pos < 8) glNormal3f(-1, 0, 0);
      if(pos >= 8 && pos < 12) glNormal3f(0, 1, 0);
      if(pos >= 12 && pos < 16) glNormal3f(1, 0, 0);
      if(pos >= 16 && pos < 20) glNormal3f(0, 0, 1);
      if(pos >= 20 && pos < 24) glNormal3f(0, 0, -1);
      glVertex3fv(cords[cr[pos++]]);
    }
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
  GLfloat detalhes[3] = {0.7, 0.13, 0.13};
  GLfloat corpo[3] = {0.10, 0.10, 0.10};
  //printf("%d %d %c\n", count, grau, points[iPoint].nextdir);
  if(count){grau += rotation; count--;}
  glRotatef(grau, 0, 0, 1);
  glTranslatef(0, 0, 0.3);

	//Cabeca
  glPushMatrix();
  //glRotatef(hRotate += 0.5, 0.0, 0.0, 1.0);
  glScalef(0.3, 0.3, 0.25);
  glColor3fv(corpo);
  glTranslatef(0, 0, 5);
  desenhaCuboRobo();
  glPopMatrix();

	//OLHOS
	GLUquadricObj * eyes = quadric();
  //Olho esquerdo
  glPushMatrix();
  //glRotatef(hRotate, -0.05, 0, 50);
	//Exterior
	glColor3f(1, 1, 1);
  glTranslatef(0.151, 0.08, 1.3);
  glRotatef(90, 0, 1, 0);
  gluDisk(eyes, 0, 0.04, 25, 1);
	//Interior
	glTranslatef(0.0, 0.0, 0.001);
  glColor3fv(corpo);
	gluDisk(eyes, 0, 0.02, 25, 1);
  glPopMatrix();

  //Olho direito
  glPushMatrix();
  //glRotatef(hRotate, -0.05, 0, 50);
	//Exterior
	glColor3f(1, 1, 1);
  glTranslatef(0.151, -0.08, 1.3);
  glRotatef(90, 0, 1, 0);
  gluDisk(eyes, 0, 0.04, 25, 1);
	//Interior
	glTranslatef(0.0, 0.0, 0.001);
  glColor3fv(corpo);
	gluDisk(eyes, 0, 0.02, 25, 1);
  glPopMatrix();

  //Boca
  glPushMatrix();
  //glRotatef(hRotate+=1, -0.05, 0, 4);
	glColor3fv(detalhes);
	glTranslatef(0.25, 0, 1.2);
  glRotatef(90, 0, -1, 0);
  //glScalef(0.04, 0.14, 0.001);
	gluCylinder(eyes, 0.055, 0.03, 0.25, 50, 50);
	//desenhaCuboRobo();
  glPopMatrix();

  //Pescoco
  glPushMatrix();
  glScalef(0.1, 0.1, 0.3);
  glColor3fv(corpo);
  glTranslatef(0, 0.1, 3.5);
  desenhaCuboRobo();
  glPopMatrix();

  //Tronco
  glPushMatrix();
  glScalef(0.5, 0.5, 0.5);
  glColor3fv(corpo);
  glTranslatef(0, 0, 1.5);
  desenhaCuboRobo();
  glPopMatrix();

	//Antebraco esquerdo
  glPushMatrix();
	glScalef(0.1, 0.1, 0.3);
  glColor3fv(corpo);
  glTranslatef(0, 3, 2.6);
  desenhaCuboRobo();
  glPopMatrix();

  //Antebraco direito
  glPushMatrix();
  glScalef(0.1, 0.1, 0.3);
  glColor3fv(corpo);
  glTranslatef(0, -3, 2.6);
  desenhaCuboRobo();
  glPopMatrix();

	//braco esquerdo
  glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glScalef(0.1, 0.1, 0.5);
  glColor3fv(corpo);
  glTranslatef(-6, -3, 0.4);
  desenhaCuboRobo();
  glPopMatrix();

	//braco direito
  glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glScalef(0.1, 0.1, 0.5);
  glColor3fv(corpo);
  glTranslatef(-6, 3, 0.4);
  desenhaCuboRobo();
  glPopMatrix();

  //Apoio de roda esquerdo
  glPushMatrix();
  //glScalef(0.01, 0.1, 0.5);
  glColor3fv(corpo);
  glTranslatef(0, 0.2, 0);
	gluCylinder(eyes, 0.03, 0.03, 0.5, 50, 1);
  glPopMatrix();

  //Apoio de roda direito
  glPushMatrix();
  //glScalef(0.01, 0.1, 0.5);
  glColor3fv(corpo);
  glTranslatef(0, -0.2, 0);
	gluCylinder(eyes, 0.03, 0.03, 0.5, 50, 1);
  glPopMatrix();

	//Ligação entre os apoios
  glPushMatrix();
	glRotatef(90, 1, 0, 0);
  //glScalef(0.01, 0.1, 0.5);
  glColor3fv(corpo);
  glTranslatef(0, 0, -0.225);
	gluCylinder(eyes, 0.03, 0.03, 0.45, 50, 1);
  glPopMatrix();

	//Aro 1
  glPushMatrix();
	glColor3f(0.93, 0.57, 0.13);
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
	glColor3f(0.93, 0.57, 0.13);
  glTranslatef(0, 0, -0.05);
	gluCylinder(eyes, 0.03, 0.03, 0.30, 50, 1);
  glPopMatrix();
	//Aro 3
  glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(62*move, 0, 1, 0);
  //glScalef(0.01, 0.1, 0.5);
	glColor3f(0.93, 0.57, 0.13);
  glTranslatef(0, 0, -0.01);
	gluCylinder(eyes, 0.03, 0.03, 0.30, 50, 1);
  glPopMatrix();
	//Aro 4
  glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(62*move, 0, 1, 0);
  //glScalef(0.01, 0.1, 0.5);
	glColor3f(0.93, 0.57, 0.13);
  glTranslatef(0, 0, -0.29);
	gluCylinder(eyes, 0.03, 0.03, 0.30, 50, 50);
  glPopMatrix();

	//Antena
  glPushMatrix();
	glColor3f(0.41, 0.41, 0.41);
  glTranslatef(0, 0, 1.3);
	gluCylinder(eyes, 0.01, 0.01, 0.25, 50, 50);
  glColor3fv(detalhes);
  glTranslatef(0, 0, 0.3);
  gluSphere(eyes, 0.05, 50, 50);
  glPopMatrix();

  //Barriga
  glPushMatrix();
  glRotatef(90, 0, 1, 0);
  glScalef(0.4, 0.3, 0.01);
  glColor3f(1, 1, 1);
  glTranslatef(-1.8, 0, 25);
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

void drawGlass(){
  int i, j;
  GLfloat cor_vidro[4] = {0.69, 0.89, 0.9, 0.4};

  for (i = 0; i < MAXLAB; i++) {
    for (j = 0; j < MAXLAB; j++) {
      if (labirinto[i][j] == 2) {
        glPushMatrix();
        //Faz a parte de cima da janelinha
        glRotatef(270, 0, 0, 1);
        glTranslatef(i - MAXLAB/2 + 20, j - MAXLAB / 2 - 1, -0.30);
        desenhaCubo(i, j);
        //Faz a parte de baixo da janelinha
        glTranslatef(0, 0, 3);
        desenhaCubo(i, j);

        //glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_COLOR_MATERIAL);

        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,cor_vidro);
        glTranslatef(0, 0, -2);
        glScalef(1, 1, 2);
        glRotatef(90, 0, 1, 0);
        glBegin(GL_QUADS);
        glVertex2f(-1, 1);
        glVertex2f(-1, 0);
        glVertex2f(0, 0);
        glVertex2f(0, 1);
        glEnd();


        glEnable(GL_COLOR_MATERIAL);
        glDisable(GL_BLEND);
        //glEnable(GL_LIGHTING);

        //glDisable(GL_TEXTURE_2D);

        //glEnable(GL_TEXTURE_2D);
        glPopMatrix();
      }
    }
  }
}

//Desenha as paredes do labirinto
void desenhaParede(void) {

  int i, j;
  for (i = 0; i < MAXLAB; i++) {
    for (j = 0; j < MAXLAB; j++) {
      if (labirinto[i][j] == 1) {
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
      if(alpha >= PI/3 && alpha <= 2*PI/3){
	glNormal3f(0,1,0);
	glVertex3f(x, y, z);
      }
      x = radius*cos(beta)*sin(alpha + PI/gradation);
      y = radius*sin(beta)*sin(alpha + PI/gradation);
      z = radius*cos(alpha + PI/gradation);
      if(alpha >= PI/3 && alpha <= 2*PI/3){
	glNormal3f(0,1,0);
	glVertex3f(x, y, z);
      }
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


  if(count_cam){
    count_cam--;
    //printf("%f %f %d %d\n", xAdjust, yAdjust, cam_turnx, cam_turny);
    xAdjust += cam_turnx;
    yAdjust += cam_turny;
  }




  if(look <= 1){
    //printf("%lf %lf %lf\n", rotatextop, rotateytop, rotateztop);
    gluLookAt(rotatextop, rotateytop, rotateztop, 0, 0, 0, 0, 1, 0);
  }
  else if(look == 2){
    if(!finished)
      gluLookAt(robox - (MAXLAB/2) + xAdjust, roboy - (MAXLAB/2) + yAdjust, 3, robox - (MAXLAB/2), roboy - (MAXLAB/2), centerzthird, 0, 0, 1);
    else
      gluLookAt( 19.0, 25.0, 4.0, 14.0, 17.0, 1.0, 0.0, 0.0, 1.0);
  }
  else if(look == 3) gluLookAt(-40.0, -4.0, 12.0, 0.0, 0.0, 5.0, 0.0, 0.0, 1.0);
  else if(look == 4) gluLookAt(-6.0, 0.0, 2.0, 0.0, -7.0, -2.0, 0.0, 0.0, 1.0);
  else if(look == 5) gluLookAt( -1.0, 3.0, 5.0, 4.0, 1.0, 0.0, 0.0, 0.0, 1.0);
  else if(look == 6) gluLookAt( -19.0, -20.0, 23.0, -19.0, -3.0, 8.0, 0.0, 0.0, 1.0);
  else if(look == 7) gluLookAt( 7.0, 3.0, 4.0, 2.0, 1.0, 1.0, 0.0, 0.0, 1.0);
  if(chao){
    //INICIO DO CHAO
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    //Desenhar o chao;
    glColor3f(0.49, 0.99, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(-2*MAXLAB/2, -2*MAXLAB/2 - 3);
    glVertex3f(-2*MAXLAB/2, -2*MAXLAB/2 - 3, -0.001);
    glTexCoord2f(2*MAXLAB/2, -2*MAXLAB/2 - 3);
    glVertex3f(2*MAXLAB/2, -2*MAXLAB/2 - 3, -0.001);
    glTexCoord2f(2*MAXLAB/2, 2*MAXLAB/2 + 3);
    glVertex3f(2*MAXLAB/2, 2*MAXLAB/2 + 3, -0.001);
    glTexCoord2f(-2*MAXLAB/2, 2*MAXLAB/2 + 3);
    glVertex3f(-2*MAXLAB/2, 2*MAXLAB/2 + 3, -0.001);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //FIM DO CHAO
  }

  glPushMatrix();
  robox += speedx; roboy += speedy;
  // VERIFICAR SE O ROBO TEM Q VIRAR
  if((int)robox == points[iPoint].x || (int)roboy == points[iPoint].y){
    if(iPoint == 30){
      finished = 1;
    }
    speedx = points[iPoint].speedx;
    speedy = points[iPoint].speedy;
    if(points[iPoint].nextdir == 1){ // DB
      count = 9;
      rotation = -ROBOTURN;
      count_cam = 9;
      cam_turnx = -CAMTURN;
      cam_turny = CAMTURN;
    }
    if(points[iPoint].nextdir == 2){// DC
      count = 9;
      rotation = -ROBOTURN;
      count_cam = 9;
      cam_turnx = CAMTURN;
      cam_turny = -CAMTURN;
    }
    if(points[iPoint].nextdir == 3){//DE
      count = 9;
      rotation = -ROBOTURN;
      count_cam = 9;
      cam_turnx = CAMTURN;
      cam_turny = CAMTURN;
    }
    if(points[iPoint].nextdir == 4){//DD
      count = 9;
      rotation = -ROBOTURN;
      count_cam = 9;
      cam_turnx = -CAMTURN;
      cam_turny = -CAMTURN;
    }
    if(points[iPoint].nextdir == 5){//EB
      count = 9;
      rotation = ROBOTURN;
      count_cam = 9;
      cam_turnx = CAMTURN;
      cam_turny = CAMTURN;
    }
    if(points[iPoint].nextdir == 6){//EC
      count = 9;
      rotation = ROBOTURN;
      count_cam = 9;
      cam_turnx = -CAMTURN;
      cam_turny = -CAMTURN;
    }
    if(points[iPoint].nextdir == 7){//EE
      count = 9;
      rotation = ROBOTURN;
      count_cam = 9;
      cam_turnx = CAMTURN;
      cam_turny = -CAMTURN;
    }
    if(points[iPoint].nextdir == 8){//ED
      count = 9;
      rotation = ROBOTURN;
      count_cam = 9;
      cam_turnx = -CAMTURN;
      cam_turny = CAMTURN;
    }
    if(points[iPoint].nextdir == 9){//AB
      count = 18;
      rotation = ROBOTURN;
      count_cam = 18;
      cam_turnx = 0;
      cam_turny = CAMTURN;

    }
    if(points[iPoint].nextdir == 10){//AC
      count = 18;
      rotation = ROBOTURN;
      count_cam = 18;
      cam_turnx = 0;
      cam_turny = -CAMTURN;

    }
    if(points[iPoint].nextdir == 11){//AE
      count = 18;
      rotation = ROBOTURN;
      count_cam = 18;
      cam_turnx = CAMTURN;
      cam_turny = 0;

    }
    if(points[iPoint].nextdir == 12){//AD
      count = 18;
      rotation = ROBOTURN;
      count_cam = 18;
      cam_turnx = -CAMTURN;
      cam_turny = 0;
    }

    if(iPoint <= 29) iPoint++;
    if(iPoint == 5) iPoint++;
  }
  glTranslatef(robox - MAXLAB/2, roboy - MAXLAB / 2, 0);
  glScalef(1, 1, 1);
  glRotatef(90, 0, 0, 1);
  desenhaRobo();
  glPopMatrix();

  glEnable(GL_TEXTURE_2D);
  tex_coord = 0.75;
  glBindTexture(GL_TEXTURE_2D, tex[1]);
  desenhaParede();
  glDisable(GL_TEXTURE_2D);

  desenhaObjetos();
  desenhaRodaGigante();

  glEnable(GL_TEXTURE_2D);
  drawGlass();
  glDisable(GL_TEXTURE_2D);

  glutSwapBuffers();
  glFlush();
}

void Redesenha(int) {
  glutPostRedisplay();
  desenha();
  glutTimerFunc(30,Redesenha,1);
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

void loadTexture(const char * imagepath, int i){
  unsigned char header[54]; //Todo bmp começa com um header de 54bytes
  unsigned int dataPos, width, height; //Posicao onde os dados começam no arquivo
  unsigned imageSize; //Largura*Altura*3
  unsigned char * data; //Dados RGB

  //Abre arquivo binário em modo de leitura
  FILE *img = fopen(imagepath, "rb");
  if(!img){printf("Imagem da textura não pode ser carregada!\n"); return;}

  if(fread(header, 1, 54, img) != 54 || header[0] != 'B' || header[1] != 'M'){printf("Imagem da textura não é um BMP válido!\n"); return;}

  //Lê informações do Header
  dataPos    = *(int*)&(header[0x0A]);
  imageSize  = *(int*)&(header[0x22]);
  width      = *(int*)&(header[0x12]);
  height     = *(int*)&(header[0x16]);

  //printf("Tamanho da imagem: %u, W: %u, H: %d\n", imageSize, width, height);

  //Caso o arquivo BMP não esteja corretamente formatado
  if(imageSize == 0) imageSize = width * height*3; // 3 por causa do RGB
  if(dataPos == 0) dataPos = 54;

  //Aloca buffer e lê
  data = new unsigned char[imageSize];
  fread(data, 1, imageSize, img);

  //Fecha o arquivo
  fclose(img);

  //"Liga" a nova textura, todas as funções de textura posteriores vão modificar ela
  glBindTexture(GL_TEXTURE_2D, tex[i]);
  //"Dá" a imagem ao opengl
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
  //Constroi MipMap
  gluBuild2DMipmaps(tex[i], GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
  //MipMap coisa la, n sei bemt tambem
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  //Repetir
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  //Oque fazer se a textura não corresponder ao poligono
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  //Substitui a cor original
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);

}
