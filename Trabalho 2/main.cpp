#include "robo.h"

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(1366, 768);
  glutCreateWindow ("Labirinto");
  glutKeyboardFunc(getViewPos);
  glutTimerFunc(50,Redesenha,1);
  glutDisplayFunc(desenha);
  glutReshapeFunc(AlteraTamanhoJanela);
  Inicializa();
  glutMainLoop();
  return 0;
}
