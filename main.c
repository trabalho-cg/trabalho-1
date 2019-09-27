#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

#include <unistd.h>
#include <stdio.h>

#define PI 3.141592
#define QTD 3

enum Func {Translate, Rotate, Scale, Todos};
enum Func tipo;
 
void myTranslate(float x, float y, float z){
    GLfloat matrix[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, y, z, 1};
    glMultMatrixf(matrix);
}
void myRotate(float alpha, float x, float y, float z){
    alpha *= PI/180.0;
    GLfloat matrixX[16] = {1, 0, 0, 0, 0, cos(alpha), sin(alpha), 0, 0, -sin(alpha), cos(alpha), 0, 0, 0, 0, 1};
    GLfloat matrixY[16] = {cos(alpha), 0, -sin(alpha), 0, 0, 1, 0, 0, sin(alpha), 0, cos(alpha), 0, 0, 0, 0, 1};
    GLfloat matrixZ[16] = {cos(alpha), sin(alpha), 0, 0, -sin(alpha), cos(alpha), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
   
    glMultMatrixf(matrixX);
    glMultMatrixf(matrixY);
    glMultMatrixf(matrixZ);
}
void myScale(float x, float y, float z){
    GLfloat matriz[16] = {x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1};
    glMultMatrixf(matriz);
}
void init (void)
{
/* determina cor da janela de branca*/
    glClearColor (1.0,1.0,1.0,0.0);
/* Estabelece parâmetros das coordenadas do mundo para a janela de clipping*/
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (-100.0,100.0, -100.0, 100.0);
/*Construcao da matrix de transformacao geométrica*/
    glMatrixMode(GL_MODELVIEW);
}

void cmp_history(GLfloat gl_history[QTD][16], GLfloat my_history[QTD][16], const char* msg_igual, const char* msg_dif)
{
    int i, j;
    for (i = 0; i < QTD; i++) {
        for (j = 0; j < 16; j++) {
            // if (gl_history[i][j] == -0) gl_history[i][j] = 0;
            if (gl_history[i][j] != my_history[i][j]) {
                printf("gl[%d][%d]: %f VS my[%d][%d]: %f\n", i, j, gl_history[i][j], i, j, my_history[i][j]);
                printf("%s", msg_dif);
                goto out;
            }
        }
    }
    out:
    if (i == QTD) printf("%s", msg_igual);
}

void desenha_linhas_1()
{
    glClear (GL_COLOR_BUFFER_BIT); //limpa a janela de visão (display window)
    glColor3f (0.0,0.0,1.0); //estalebece a cor de preenchimento inicial como azul
    glViewport(0,0,300,300); // Estabelece viewport esquerda
    glBegin (GL_LINES);
    glVertex2i (-10, -15);
    glVertex2i (20, 25);
    glEnd ();
}

void desenha_linhas_2()
{
    glColor3f (1.0,0.0,0.0); //estalebece a cor de preenchimento como vermelho
    glViewport(300,0,300,300); // Estabelece viewport esquerda
    glBegin (GL_LINES);
    glVertex2i (-10, -15);
    glVertex2i (20, 25);
    glEnd ();
    glFlush();
}

void test_func(enum Func tipo, float x, float y, float z, float alpha)
{
    int i, j;
    GLfloat gl_history[QTD][16];
    GLfloat my_history[QTD][16];

    desenha_linhas_1();
    desenha_linhas_2();
    sleep(5);
    glutSetWindowTitle("Comecando visualizacao openGL");
    // implementação do openGL
    glPushMatrix();
    for (i = 0; i < QTD; i++) {
        desenha_linhas_1();
        if (tipo == Rotate) {
            glRotatef(alpha,x,y,z);
        }
        else if (tipo == Translate) {
            glTranslatef(x, y, z);
        }
        else if (tipo == Scale) {
            glScalef(x, y, z);
        }
        glGetFloatv (GL_MODELVIEW_MATRIX, gl_history[i]);
        desenha_linhas_2();
        sleep(1);
    }
    glutSetWindowTitle("Terminou visualizacao openGL");
    sleep(3);
    glPopMatrix();
    desenha_linhas_1();
    desenha_linhas_2();
    glutSetWindowTitle("Cena reinicializada");
    sleep(3);
    glutSetWindowTitle("Comecando visualizacao da nossa implementacao");
    
    glPushMatrix();
    // nossa implementação
    for (i = 0; i < QTD; i++) {
        desenha_linhas_1();
        if (tipo == Rotate) {
            myRotate(alpha,x,y,z);
        }
        else if (tipo == Translate) {
            myTranslate(x, y, z);
        }
        else if (tipo == Scale) {
            myScale(x, y, z);
        }
        glGetFloatv (GL_MODELVIEW_MATRIX, my_history[i]);
        desenha_linhas_2();
        sleep(1);
    }
    glutSetWindowTitle("Terminou visualizacao da nossa implementacao");
    sleep(3);
    glPopMatrix();

    if (tipo == Rotate) {
        cmp_history(gl_history, my_history, "Rotação deu igual.\n", "Rotação deu diferente!\n");
    }
    else if (tipo == Translate) {
        cmp_history(gl_history, my_history, "Translação deu igual.\n", "Translação deu diferente!\n");
    }
    else if (tipo == Scale) {
        cmp_history(gl_history, my_history, "Escala deu igual.\n", "Escala deu diferente!\n");
    }
}

void displayFcn (void)
{
    if (tipo == Scale || tipo == Todos) {
        glutSetWindowTitle("Cena inicial (testando escala)");
        test_func(Scale, 1.5, 1.5, 1.5, 90.0);
    }
    if (tipo == Translate || tipo == Todos) {
        glutSetWindowTitle("Cena inicial (testando translacao)");
        test_func(Translate, 19, 10, 0, 90.0);
    }
    if (tipo == Rotate || tipo == Todos) {
        glutSetWindowTitle("Cena inicial (testando rotacao)");
        test_func(Rotate, 0, 0, 1.0, 90.0);
    }
    exit(0);
}
 
int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(600,300);
 
    glutCreateWindow("Exemplo de Window/Viewport");
    init();
    tipo = Rotate;
    glutDisplayFunc(displayFcn);
    glutMainLoop();
    return 0;
}