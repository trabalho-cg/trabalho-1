#include <GL/glut.h>
void init(void)
{
    /* determina cor da janela de branca*/
    glClearColor(1.0, 1.0, 1.0, 0.0);
    /* Estabelece parâmetros das coordenadas do mundo  para a janela de clipping*/
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
    /*Construcao da matrix de transformacao geométrica*/
    glMatrixMode(GL_MODELVIEW);
}
void displayFcn(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //limpa a janela de visão (display window)
    glColor3f (0.0,0.0,1.0); //estalebece a cor de preenchimento inicial como azul
    glViewport(0,0,300,300); // Estabelece viewport esquerda/*Exibe segmento de reta*/
    glBegin(GL_LINES);
    glVertex2i(-10, -15);
    glVertex2i(20, 25);
    glEnd();                        /*Roda segmento de reta  para ser visto na outra viewport*/
    glColor3f(1.0, 0.0, 0.0);       //estalebece a cor de preenchimento como vermelho
    glViewport(300, 0, 300, 300);   // Estabelece viewport esquerda
    glRotatef(90.0, 0.0, 0.0, 1.0); // Rotaciona em torno de z
    glBegin(GL_LINES);
    glVertex2i(-10, -15);
    glVertex2i(20, 25);
    glEnd();
    glFlush();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(600, 300);
    glutCreateWindow("Exemplo de Window/Viewport");
    init();
    glutDisplayFunc(displayFcn);
    glutMainLoop();
}