//Flags de compilação: -lGL -lGLU -lglut
#include <GL/glut.h>

//Função de display (desenho)
void draw(void);
//Função de reshape (redimensionamento)
void reshape(GLsizei w, GLsizei h);
//Função com inicializações
void initialize(void);
//Função para tratar eventos do teclado
void keyboard(unsigned char key, int x, int y);

int main(int argc, char **argv){
  //Inicializa a glut
  glutInit(&argc, argv);
  //Seta o Display Mode
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  //Tamanho, posição e nome da janela
  glutInitWindowSize(800,600);
  glutInitWindowPosition(10, 10);
  glutCreateWindow("Labyrinth");

  glutDisplayFunc(draw);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  initialize();

  //Loop principal da glut
  glutMainLoop();
}

void draw(void){

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void reshape(GLsizei w, GLsizei h){
  if (h == 0) h = 1;
  //Define o Tamanho da viewport (área usada pela cena dentro da janela)
  glViewport(0, 0, w, h);
  //Inicializar sistema de cordenadas, matriz (identidade)
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //Define uma matriz de projeção ortográfica 2d
  if(w <= h) gluOrtho2D(-2.0f, 2.0f, -2.0f, 2.0f*h / w);
  else gluOrtho2D(-2.0f, 2.0f*w / h, -2.0f, 2.0f);
}

void initialize(void){
  glClearColor(0.0f, 0.0f, 0.0f, 0.1f);
}

void keyboard(unsigned char key, int x, int y){
  if(key == '+') rotateztop -= 1;
  if(key == '-') rotateztop += 1;
  if(key == '8') rotateytop += 1;
  if(key == '2') rotateytop -= 1;
  if(key == '4') rotatextop -= 1;
  if(key == '6') rotatextop += 1; 
}
