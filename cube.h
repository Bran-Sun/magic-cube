#ifndef QCube_H
#define QCube_H

#include <QWidget>
#include<QGLWidget>
#include<QTimer>
struct Piece
{
    int color[7];
} ;

class QCube : public QGLWidget
{
    Q_OBJECT
public:
    explicit QCube(QWidget *parent=0);
    ~QCube();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void paintQCube(int x,int y,int z);

    void setcolor(int k);
    void scan(Piece cube[3][3][3]);


    void turnX(int n,int m);
    void turnR();
    void BturnR();
    void turnL();
    void BturnL();

    void turnY(int n,int m);
    void turnU();
    void BturnU();
    void turnD();
    void BturnD();

    void turnZ(int n,int m);
    void turnF();
    void BturnF();
    void turnB();
    void BturnB();

    void turnX2(int n,int m);
    void turnR2();
    void BturnR2();
    void turnL2();
    void BturnL2();

    void turnY2(int n,int m);
    void turnU2();
    void BturnU2();
    void turnD2();
    void BturnD2();

    void turnZ2(int n,int m);
    void turnF2();
    void BturnF2();
    void turnB2();
    void BturnB2();

    void print();
    void nextstep();
    void solve();
    bool jiaokuai(int x,int y,int z,int a,int b,int c);
    void third();
    void fourth1();
    void fourth2();
    void reversethird();
    void fifth();
   void sixth();
   int correct();
   void shun();
   void ni();


    void firstlevel();
    void secondlevel();
    void thirdlevel();
    void fourthlevel();
    void fifthlevel();
    void sixthlevel();
    void seventhlevel();

    void keyPressEvent(QKeyEvent *event);
public slots:
      void turnx();
      void turny();
      void turnz();
private:
    bool fullscreen;

    GLfloat m_x;
    GLfloat m_y;
    GLfloat m_z;
    int record;
    QTimer *timer;
    int xn,xr;
    int yn,yr;
    int zn,zr;
    char ch[1000];
    int level[1000];
    int count;
    int pre;
   Piece cube[3][3][3];
   Piece cube2[3][3][3];
   int angelx[3][3][3];
   int angely[3][3][3];
   int angelz[3][3][3];
};

#endif // QCube_H
