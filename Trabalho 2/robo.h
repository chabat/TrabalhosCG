//AUTORES: Felipe Chabatura e Leonardo Tironi;
#ifndef ROBO_H
#define ROBO_H

#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#define MAXLAB 30 // Tamanho máximo do labirinto
#define SPEED 0.10; //Velocidade do Robô
#define INF 112345 //Valor de infinito
#define CAMTURN 0.11111111111111 * 2 //Constante para movimento da câmera
#define ROBOTURN 10 //Constante para movimento do Robô
#define CENTRO MAXLAB / 2 //Centro do labirinto

//Estrutura de ponto no labirinto (local do grid)
typedef struct{
  int x, y;
  double speedx, speedy;
  int nextdir;
}point_t;

void Inicializa(void); //Função com rotinas de inicialização
GLUquadricObj *quadric(void); //Função para desenhar quádricas
void getViewPos(unsigned char key, int x, int y); //Função para tratar comandos do teclado
void desenhaCubo(int posi, int posj); //Função que desenha cubo para as paredes
void desenhaCuboRobo(); //Função que desenha os cubos do robo
void desenhaRobo(); //Função que desenha o robo
void desenhaParede(void); //Função para desenhar as paredes do labirinto
void desenhaObjetos(void); //Função que desenha os demais objetos no labirinto
void desenha(void); //Função que desenha tudo
void Redesenha(int); //Função de redesenho
void AlteraTamanhoJanela(GLsizei w, GLsizei h); //Função para alterar tamanho da janela
void loadTexture(const char * imagepath, int i); //Função que lẽ os arquivos de textura bmp e os carrega no open gl

#endif
