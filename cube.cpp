#include "cube.h"
#include<GL/glu.h>
#include<QKeyEvent>
#include<QTimer>
#include<QPainter>
#include<QFile>
#include<QDebug>
#include<iostream>

QCube::QCube(QWidget *parent):
    QGLWidget(parent)
{
    int i,j,k;
    fullscreen=false;

    m_x=0;
    m_y=0;
    m_z=0;
    xn=0;xr=0;
    yn=0;yr=0;
    zn=0;zr=0;
    for(i=0;i<3;i++)
        for (j=0;j<3;j++)
            for(k=0;k<3;k++)
            {
                angelx[i][j][k]=0;
                angely[i][j][k]=0;
                angelz[i][j][k]=0;
            }
    scan(cube);
    record=0;
    count=0;
    pre=0;
}

QCube::~QCube()
{

}

void QCube::initializeGL()
{
    glEnable(GL_MULTISAMPLE);
    glClearColor(0.0,0.3,0.3,0.0);
    glShadeModel(GL_SMOOTH);

    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

}
void QCube::resizeGL(int w, int h)
{
    glViewport(0,0,(GLint)w,(GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0,(GLfloat)w/(GLfloat)h,0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void QCube::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    for (int i=0;i<3;i++)
      for (int j=0;j<3;j++)
            for (int k=0;k<3;k++)
            {
                paintQCube(i,j,k);
            }
}

void QCube::paintQCube(int x, int y, int z)
{
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-12.0f);
    glRotatef(m_x,1.0f,0.0f,0.0f);
    glRotatef(m_y,0.0f,1.0f,0.0f);
    glRotatef(m_z,0.0f,0.0f,1.0f);
    glRotatef(angelx[x][y][z],1.0f,0.0f,0.0f);
    glRotatef(angely[x][y][z],0.0f,1.0f,0.0f);
    glRotatef(angelz[x][y][z],0.0f,0.0f,1.0f);
 glTranslatef(2*x-2,2*y-2,2*z-2);

    float dif=0.1;
    float fl=0.01;
    glBegin(GL_QUADS);
            glColor3f(0.0f,0.0f,0.0f);
            glVertex3f(1.0f, 1.0f, -1.0f);                  //右上(顶面)
            glVertex3f(-1.0f, 1.0f, -1.0f);                 //左上(顶面)
            glVertex3f(-1.0f, 1.0f, 1.0f);                  //左下(顶面)
            glVertex3f(1.0f, 1.0f, 1.0f);                   //右下(顶面)


            glVertex3f(1.0f, -1.0f, 1.0f);                  //右上(底面)
            glVertex3f(-1.0f, -1.0f, 1.0f);                 //左上(底面)
            glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(底面)
            glVertex3f(1.0f, -1.0f, -1.0f);                 //右下(底面)

            glVertex3f(1.0f, 1.0f, 1.0f);                   //右上(前面)
            glVertex3f(-1.0f, 1.0f, 1.0f);                  //左上(前面)
            glVertex3f(-1.0f, -1.0f, 1.0f);                 //左下(前面)
            glVertex3f(1.0f, -1.0f, 1.0f);                  //右下(前面)

           glVertex3f(1.0f, -1.0f, -1.0f);                 //右上(后面)
            glVertex3f(-1.0f, -1.0f, -1.0f);                //左上(后面)
            glVertex3f(-1.0f, 1.0f, -1.0f);                 //左下(后面)
            glVertex3f(1.0f, 1.0f, -1.0f);                  //右下(后面)

            glVertex3f(-1.0f, 1.0f, 1.0f);                  //右上(左面)
            glVertex3f(-1.0f, 1.0f, -1.0f);                 //左上(左面)
            glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(左面)
            glVertex3f(-1.0f, -1.0f, 1.0f);                 //右下(左面)

            glVertex3f(1.0f, 1.0f, -1.0f);                  //右上(右面)
            glVertex3f(1.0f, 1.0f, 1.0f);                   //左上(右面)
            glVertex3f(1.0f, -1.0f, 1.0f);                  //左下(右面)
            glVertex3f(1.0f, -1.0f, -1.0f);
        glEnd();

        glBegin(GL_QUADS);
                   setcolor(cube[x][y][z].color[1]);
                    glVertex3f(1.0f-dif, 1.0f+fl, -1.0f+dif);                  //右上(顶面)
                    glVertex3f(-1.0f+dif, 1.0f+fl, -1.0f+dif);                 //左上(顶面)
                    glVertex3f(-1.0f+dif, 1.0f+fl, 1.0f-dif);                  //左下(顶面)
                    glVertex3f(1.0f-dif, 1.0f+fl, 1.0f-dif);                   //右下(顶面)


                     setcolor(cube[x][y][z].color[6]);
                    glVertex3f(1.0f-dif, -1.0f-fl, 1.0f-dif);                  //右上(底面)
                    glVertex3f(-1.0f+dif, -1.0f-fl, 1.0f-dif);                 //左上(底面)
                    glVertex3f(-1.0f+dif, -1.0f-fl, -1.0f+dif);                //左下(底面)
                    glVertex3f(1.0f-dif, -1.0f-fl, -1.0f+dif);                 //右下(底面)

                        setcolor(cube[x][y][z].color[3]);
                    glVertex3f(1.0f-dif, 1.0f-dif, 1.0f+fl);                   //右上(前面)
                    glVertex3f(-1.0f+dif, 1.0f-dif, 1.0f+fl);                  //左上(前面)
                    glVertex3f(-1.0+dif, -1.0f+dif, 1.0f+fl);                 //左下(前面)
                    glVertex3f(1.0f-dif, -1.0f+dif, 1.0f+fl);                  //右下(前面)
         setcolor(cube[x][y][z].color[5]);
          glVertex3f(1.0f-dif, -1.0f+dif, -1.0f-fl);                 //右上(后面)
          glVertex3f(-1.0f+dif, -1.0f+dif, -1.0f-fl);                //左上(后面)
          glVertex3f(-1.0f+dif, 1.0f-dif, -1.0f-fl);                 //左下(后面)
          glVertex3f(1.0f-dif, 1.0f-dif, -1.0f-fl);                  //右下(后面)

            setcolor(cube[x][y][z].color[2]);
          glVertex3f(-1.0f-fl, 1.0f-dif, 1.0f-dif);                  //右上(左面)
          glVertex3f(-1.0f-fl, 1.0f-dif, -1.0f+dif);                 //左上(左面)
          glVertex3f(-1.0f-fl, -1.0f+dif, -1.0f+dif);                //左下(左面)
          glVertex3f(-1.0f-fl, -1.0f+dif, 1.0f-dif);                 //右下(左面)

            setcolor(cube[x][y][z].color[4]);
          glVertex3f(1.0f+fl, 1.0f-dif, -1.0f+dif);                  //右上(右面)
          glVertex3f(1.0f+fl, 1.0f-dif, 1.0f-dif);                   //左上(右面)
          glVertex3f(1.0f+fl, -1.0f+dif, 1.0f-dif);                  //左下(右面)
          glVertex3f(1.0f+fl, -1.0f+dif, -1.0f+dif);
      glEnd();
}

void QCube::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_F1:
        fullscreen=!fullscreen;
        if(fullscreen)
        {
            showFullScreen();
        }
        else
        {
        showNormal();
         }
        updateGL();
        break;
       case Qt::Key_R:
        turnR();
        break;
       case Qt::Key_L:
        turnL();
        break;
    case Qt::Key_U:
        turnU();
        break;
      case Qt::Key_D:
        turnD();
        break;
    case Qt::Key_F:
        turnF();
        break;
     case Qt::Key_B:
        turnB();
        break;
      case Qt::Key_Up:
        m_x +=10;
        updateGL();
        break;
       case Qt::Key_Down:
        m_x -=10;
        updateGL();
        break;
       case Qt::Key_Left:
        m_y +=10;
        updateGL();
         break;
        case Qt::Key_Right:
         m_y -=10;
        updateGL();
        break;
    case Qt::Key_S:
        for (int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                for (int k=0;k<3;k++)
                {
                    cube2[i][j][k]=cube[i][j][k];
                }
           solve();
        break;
      case Qt::Key_Escape:
        close();
    }
}

void QCube::setcolor(int k)
{
    switch(k)
    {
       case 1: glColor3f(0.0f, 1.0f, 0.0f);                    //绿色
               break;
       case 2:
        glColor3f(1.0f, 0.5f, 0.0f);                    //橙色
        break;
       case 3:
         glColor3f(1.0f, 0.0f, 0.0f);                    //红色
        break;
        case 4:
                glColor3f(1.0f, 1.0f, 0.0f);                    //黄色
               break;
        case 5:
               glColor3f(0.0f, 0.0f, 1.0f);                    //蓝色
             break;
        case 6:
            glColor3f(1.0f, 1.0f, 1.0f);                    //白色
             break;
        case 0:
          glColor3f(0.0f,0.0f,0.0f);
    }
}

void QCube::scan(Piece cube[3][3][3])
{
    int i,j,k,t;
     for (i=0;i<3;i++)
          for (j=0;j<3;j++)
           for (k=0;k<3;k++)
            for(t=1;t<=6;t++)
                cube[i][j][k].color[t]=0;
     for (i=0;i<3;i++)
          for (j=0;j<3;j++)
            {
                 cube[i][j][2].color[3]=3;
             }
         for (j=0;j<3;j++)
          for (i=0;i<3;i++)
            {
                 cube[i][0][2-j].color[6]=6;
             }
        for (j=0;j<3;j++)
          for (i=0;i<3;i++)
            {
                 cube[2][i][2-j].color[4]=4;
             }
        for (j=0;j<3;j++)
          for (i=0;i<3;i++)
            {
                 cube[2-i][2][2-j].color[1]=1;
             }
         for (j=0;j<3;j++)
          for (i=0;i<3;i++)
            {
                 cube[0][2-i][2-j].color[2]=2;
             }
         for (j=0;j<3;j++)
          for (i=0;i<3;i++)
            {
                 cube[2-j][i][0].color[5]=5;
             }

}

void QCube::turnx()
{
   int i,j;
    for (i=0;i<3;i++)
       for(j=0;j<3;j++)
          angelx[xn][i][j]=angelx[xn][i][j]+xr;
    updateGL();

   record +=1;
   if (record>=90)
   {
         timer->stop();
         if (xr==-1)
         {
         for ( i=0;i<3;i++)
            for( j=0;j<3;j++)
               angelx[xn][i][j]=0;
         Piece layer[3][3];
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     layer[j][2-i]=cube[xn][i][j];
                     layer[j][2-i].color[1]=cube[xn][i][j].color[3];
                     layer[j][2-i].color[3]=cube[xn][i][j].color[6];
                     layer[j][2-i].color[6]=cube[xn][i][j].color[5];
                     layer[j][2-i].color[5]=cube[xn][i][j].color[1];
                 }
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     cube[xn][i][j]=layer[i][j];
               }
         }
         else
             for (int k=0;k<3;k++)
             {
                 for ( i=0;i<3;i++)
                    for( j=0;j<3;j++)
                       angelx[xn][i][j]=0;
                 Piece layer[3][3];
                     for (i=0;i<3;i++)
                      for (j=0;j<3;j++)
                       {
                             layer[j][2-i]=cube[xn][i][j];
                             layer[j][2-i].color[1]=cube[xn][i][j].color[3];
                             layer[j][2-i].color[3]=cube[xn][i][j].color[6];
                             layer[j][2-i].color[6]=cube[xn][i][j].color[5];
                             layer[j][2-i].color[5]=cube[xn][i][j].color[1];
                         }
                     for (i=0;i<3;i++)
                      for (j=0;j<3;j++)
                       {
                             cube[xn][i][j]=layer[i][j];
                       }
                 }
         updateGL();
         if ((pre<count)&&(count>0))
         {
             nextstep();
         }
    }
}

void QCube::turnX(int n,int m)
{
    if (m==0) xr=-1;
    record=0;
    xn=n;
   timer=new QTimer(this);
   connect(timer,SIGNAL(timeout()),this,SLOT(turnx()));
   timer->start(1);
}

void QCube::turnR()
{
     xr=-1;
   turnX(2,xr);

}
void QCube::BturnR()
{
    xr=1;
    turnX(2,xr);
}

void QCube::turnL()
{
    xr=1;
    turnX(0,xr);
}

void QCube::BturnL()
{
    xr=-1;
    turnX(0,xr);
}
void QCube::turny()
{
   int i,j;
    for (i=0;i<3;i++)
       for(j=0;j<3;j++)
          angely[i][yn][j]=angely[i][yn][j]+yr;
    updateGL();

   record +=1;
   if (record>=90)
   {
         timer->stop();
         if (yr==-1)
         {
         for ( i=0;i<3;i++)
            for( j=0;j<3;j++)
               angely[i][yn][j]=0;
         Piece layer[3][3];
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     layer[2-j][i]=cube[i][yn][j];
                     layer[2-j][i].color[2]=cube[i][yn][j].color[3];
                     layer[2-j][i].color[3]=cube[i][yn][j].color[4];
                     layer[2-j][i].color[4]=cube[i][yn][j].color[5];
                     layer[2-j][i].color[5]=cube[i][yn][j].color[2];
                 }
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     cube[i][yn][j]=layer[i][j];
               }
         }
         else
             for (int k=0;k<3;k++)
             {
                 for ( i=0;i<3;i++)
                    for( j=0;j<3;j++)
                       angely[i][yn][j]=0;
                 Piece layer[3][3];
                     for (i=0;i<3;i++)
                      for (j=0;j<3;j++)
                       {
                             layer[2-j][i]=cube[i][yn][j];
                             layer[2-j][i].color[2]=cube[i][yn][j].color[3];
                             layer[2-j][i].color[3]=cube[i][yn][j].color[4];
                             layer[2-j][i].color[4]=cube[i][yn][j].color[5];
                             layer[2-j][i].color[5]=cube[i][yn][j].color[2];
                         }
                     for (i=0;i<3;i++)
                      for (j=0;j<3;j++)
                       {
                             cube[i][yn][j]=layer[i][j];
                       }
                }
         updateGL();
         if ((pre<count)&&(count>0))
         {
             nextstep();
         }
    }
}


void QCube::turnY(int n,int m)
{
    if (m==0) yr=-1;
    record=0;
    yn=n;
   timer=new QTimer(this);
   connect(timer,SIGNAL(timeout()),this,SLOT(turny()));
   timer->start(1);
}

void QCube::turnU()
{
     yr=-1;
     turnY(2,yr);
}

void QCube::BturnU()
{
    yr=1;
    turnY(2,yr);
}

void QCube::turnD()
{
    yr=1;
    turnY(0,yr);
}

void QCube::BturnD()
{
    yr=-1;
    turnY(0,yr);
}
void QCube::turnz()
{
   int i,j;
    for (i=0;i<3;i++)
       for(j=0;j<3;j++)
          angelz[i][j][zn]=angelz[i][j][zn]+zr;
    updateGL();

   record +=1;
   if (record>=90)
   {
         timer->stop();
         if (zr==-1)
         {
         for ( i=0;i<3;i++)
            for( j=0;j<3;j++)
               angelz[i][j][zn]=0;
         Piece layer[3][3];
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     layer[j][2-i]=cube[i][j][zn];
                     layer[j][2-i].color[4]=cube[i][j][zn].color[1];
                     layer[j][2-i].color[1]=cube[i][j][zn].color[2];
                     layer[j][2-i].color[2]=cube[i][j][zn].color[6];
                     layer[j][2-i].color[6]=cube[i][j][zn].color[4];
                 }
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     cube[i][j][zn]=layer[i][j];
               }
         }
         else
             for (int k=0;k<3;k++)
             {
             for ( i=0;i<3;i++)
                for( j=0;j<3;j++)
                   angelz[i][j][zn]=0;
             Piece layer[3][3];
                 for (i=0;i<3;i++)
                  for (j=0;j<3;j++)
                   {
                         layer[j][2-i]=cube[i][j][zn];
                         layer[j][2-i].color[4]=cube[i][j][zn].color[1];
                         layer[j][2-i].color[1]=cube[i][j][zn].color[2];
                         layer[j][2-i].color[2]=cube[i][j][zn].color[6];
                         layer[j][2-i].color[6]=cube[i][j][zn].color[4];
                     }
                 for (i=0;i<3;i++)
                  for (j=0;j<3;j++)
                   {
                         cube[i][j][zn]=layer[i][j];
                   }
             }
         updateGL();
         if ((pre<count)&&(count>0))
         {
             nextstep();
         }
    }
}

void QCube::turnZ(int n,int m)
{
   if (m==0) zr=-1;
    record=0;
    zn=n;
   timer=new QTimer(this);
   connect(timer,SIGNAL(timeout()),this,SLOT(turnz()));
   timer->start(1);
}
void QCube::turnF()
{
    zr=-1;
    turnZ(2,zr);
}
void QCube::BturnF()
{
    zr=1;
    turnZ(2,zr);

}

void QCube::turnB()
{
    zr=1;
    turnZ(0,zr);

}
void QCube::BturnB()
{
    zr=-1;
    turnZ(0,zr);
}

void QCube::nextstep()
{
    if (pre<count)
    {
        switch (ch[pre])
        {
           case 'U': turnU();
            break;
           case 'u':BturnU();
            break;
           case 'D':turnD();
            break;
           case 'd':BturnD();
            break;
           case 'B':turnB();
            break;
           case 'b':BturnB();
            break;
           case 'L':turnL();
            break;
           case 'l':BturnL();
            break;
           case 'R':turnR();
            break;
           case 'r':BturnR();
            break;
           case 'F':turnF();
            break;
           case 'f':BturnF();
            break;
           case 'X':turnX(level[pre],0);
            break;
           case 'Y':turnY(level[pre],0);
            break;
           case 'Z':turnZ(level[pre],0);
            break;
        }
        pre++;
    }
}

void QCube::turnX2(int n,int m)
{
    if (m==0) xr=-1;
    int i,j;
    if (xr==-1)
    {
         Piece layer[3][3];
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     layer[j][2-i]=cube2[n][i][j];
                     layer[j][2-i].color[1]=cube2[n][i][j].color[3];
                     layer[j][2-i].color[3]=cube2[n][i][j].color[6];
                     layer[j][2-i].color[6]=cube2[n][i][j].color[5];
                     layer[j][2-i].color[5]=cube2[n][i][j].color[1];
                 }
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     cube2[n][i][j]=layer[i][j];
               }
    }
    else
     for (int s=0;s<3;s++)
     {
         Piece layer[3][3];
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     layer[j][2-i]=cube2[n][i][j];
                     layer[j][2-i].color[1]=cube2[n][i][j].color[3];
                     layer[j][2-i].color[3]=cube2[n][i][j].color[6];
                     layer[j][2-i].color[6]=cube2[n][i][j].color[5];
                     layer[j][2-i].color[5]=cube2[n][i][j].color[1];
                 }
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     cube2[n][i][j]=layer[i][j];
               }
    }
}
void QCube::turnR2()
{
    xr=-1;
     turnX2(2,xr);
     ch[count]='R';
     count++;
}
void QCube::BturnR2()
{
    xr=1;
    turnX2(2,xr);
    ch[count]='r';
    count++;
}

void QCube::turnL2()
{
    xr=1;
    turnX2(0,xr);
    ch[count]='L';
    count++;
}

void QCube::BturnL2()
{
    xr=-1;
    turnX2(0,xr);
    ch[count]='l';
    count++;
}
void QCube::turnY2(int n,int m)
{
     if (m==0) yr=-1;
    int i,j;
    if(yr==-1)
    {
         Piece layer[3][3];
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     layer[2-j][i]=cube2[i][n][j];
                     layer[2-j][i].color[2]=cube2[i][n][j].color[3];
                     layer[2-j][i].color[3]=cube2[i][n][j].color[4];
                     layer[2-j][i].color[4]=cube2[i][n][j].color[5];
                     layer[2-j][i].color[5]=cube2[i][n][j].color[2];
                 }
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     cube2[i][n][j]=layer[i][j];
               }
    }
    else
        for (int s=0;s<3;s++)
        {
            Piece layer[3][3];
                for (i=0;i<3;i++)
                 for (j=0;j<3;j++)
                  {
                        layer[2-j][i]=cube2[i][n][j];
                        layer[2-j][i].color[2]=cube2[i][n][j].color[3];
                        layer[2-j][i].color[3]=cube2[i][n][j].color[4];
                        layer[2-j][i].color[4]=cube2[i][n][j].color[5];
                        layer[2-j][i].color[5]=cube2[i][n][j].color[2];
                    }
                for (i=0;i<3;i++)
                 for (j=0;j<3;j++)
                  {
                        cube2[i][n][j]=layer[i][j];
                  }
       }
}
void QCube::turnU2()
{
    yr=-1;
     turnY2(2,yr);
     ch[count]='U';
     count++;
}

void QCube::BturnU2()
{
    yr=1;
    turnY2(2,yr);
    ch[count]='u';
    count++;
}

void QCube::turnD2()
{
    yr=1;
    turnY2(0,yr);
    ch[count]='D';
    count++;
}

void QCube::BturnD2()
{
    yr=-1;
    turnY2(0,yr);
    ch[count]='d';
    count++;
}
void QCube::turnZ2(int n,int m)
{
     if (m==0) zr=-1;
   int i,j;
   if (zr==-1)
   {
         Piece layer[3][3];
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     layer[j][2-i]=cube2[i][j][n];
                     layer[j][2-i].color[4]=cube2[i][j][n].color[1];
                     layer[j][2-i].color[1]=cube2[i][j][n].color[2];
                     layer[j][2-i].color[2]=cube2[i][j][n].color[6];
                     layer[j][2-i].color[6]=cube2[i][j][n].color[4];
                 }
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     cube2[i][j][n]=layer[i][j];
               }
       }
   else
       for (int s=0;s<3;s++)
       {
           Piece layer[3][3];
               for (i=0;i<3;i++)
                for (j=0;j<3;j++)
                 {
                       layer[j][2-i]=cube2[i][j][n];
                       layer[j][2-i].color[4]=cube2[i][j][n].color[1];
                       layer[j][2-i].color[1]=cube2[i][j][n].color[2];
                       layer[j][2-i].color[2]=cube2[i][j][n].color[6];
                       layer[j][2-i].color[6]=cube2[i][j][n].color[4];
                   }
               for (i=0;i<3;i++)
                for (j=0;j<3;j++)
                 {
                       cube2[i][j][n]=layer[i][j];
                 }
         }
}

void QCube::turnF2()
{
    zr=-1;
    turnZ2(2,zr);
    ch[count]='F';
    count++;
}
void QCube::BturnF2()
{
    zr=1;
    turnZ2(2,zr);
    ch[count]='f';
    count++;
}

void QCube::turnB2()
{
    zr=1;
    turnZ2(0,zr);
    ch[count]='B';
    count++;
}
void QCube::BturnB2()
{
    zr=-1;
    turnZ2(0,zr);
    ch[count]='b';
    count++;
}

bool QCube::jiaokuai(int x,int y,int z,int a,int b,int c)
{
    if (x==a&&y==b&&z==c)
     return true;
     if (x==b&&y==c&&z==a)
     return true;
     if (x==c&&y==a&&z==b)
     return true;
     if (x==a&&y==c&&z==b)
      return true;
      if (x==b&&y==a&&z==c)
      return true;
      if (x==c&&y==b&&z==a)
      return true;
      return false;
    }
void QCube::solve()
{
      firstlevel();
    secondlevel();
    for (int j=0;j<2;j++)
    for (int i=0;i<3;i++)
   {
       turnZ2(i,0);
       ch[count]='Z';
       level[count]=i;
       count++;
    }
    thirdlevel();
    fourthlevel();
    fifthlevel();print();
    sixthlevel();print();
    seventhlevel();print();
    nextstep();

}

void QCube::firstlevel()
{
    for (int k=0;k<4;k++)
    {
       int i,j,x,y;
       x=cube2[1][2][1].color[1];
       y=cube2[2][1][1].color[4];
    for (i=0;i<4;i++)
    {
    if ((cube2[2][2][1].color[1]==x&&cube2[2][2][1].color[4]==y)||(cube2[2][2][1].color[1]==y&&cube2[2][2][1].color[4]==x))
       {
           turnR2();
       }
     turnU2();
    }
    for (i=0;i<4;i++)
     {
        if ((cube2[2][1][2].color[3]==x&&cube2[2][1][2].color[4]==y)||(cube2[2][1][2].color[3]==y&&cube2[2][1][2].color[4]==x))
         {
            BturnR2();
            turnD2();
            turnR2();
        }
        for (j=0;j<3;j++)
         {
          turnY2(j,0);
          ch[count]='Y';
          level[count]=j;
          count++;
        }
    }
    for (i=0;i<4;i++)
     {
        if ((cube2[2][0][1].color[6]==x&&cube2[2][0][1].color[4]==y)||(cube2[2][0][1].color[6]==y&&cube2[2][0][1].color[4]==x))
        {
            turnR2();
            turnR2();
            break;
        }
       turnD2();
     }
    for (i=0;i<4;i++)
    {
        if (cube2[2][2][1].color[1]==x&&cube2[2][2][1].color[4]==y)
          break;
        else if (cube2[2][2][1].color[1]==y&&cube2[2][2][1].color[4]==x)
         {
                BturnR2();
                turnU2();
                BturnF2();
                BturnU2();
                break;
        }
        turnU2();
    }
    for (i=0;i<3;i++)
    {
       turnY2(i,0);
       ch[count]='Y';
       level[count]=i;
       count++;
    }
   }
}

void QCube::secondlevel()
{
    int i,j,x,y,z;
        for (int k=0;k<4;k++)
        {
             z=cube2[1][1][2].color[3];
             y=cube2[1][2][1].color[1];
             x=cube2[2][1][1].color[4];
             for (i=0;i<4;i++)
              {
                    if (jiaokuai(x,y,z,cube2[2][2][2].color[3],cube2[2][2][2].color[4],cube2[2][2][2].color[1]))
                       {
                            BturnR2();
                            turnD2();
                            turnR2();
                        }
                    for (j=0;j<3;j++)
                    {
                     turnY2(j,0);
                     ch[count]='Y';
                     level[count]=j;
                     count++;
                    }
              }
            for (i=0;i<4;i++)
            {
                if (jiaokuai(x,y,z,cube2[2][0][2].color[3],cube2[2][0][2].color[4],cube2[2][0][2].color[6]))
                {
                    do
                    {
                        BturnR2();
                        BturnD2();
                        turnR2();
                        turnD2();
                    }while(x!=cube2[2][2][2].color[4]||y!=cube2[2][2][2].color[1]||z!=cube2[2][2][2].color[3]);
                    break;
                }
                turnD2();
            }
            for (i=0;i<3;i++)
            {
             turnY2(i,0);
             ch[count]='Y';
             level[count]=i;
             count++;
            }
        }
}

void QCube::third()
{
    turnU2();
    turnR2();
    BturnU2();
    BturnR2();
    BturnU2();
    BturnF2();
    turnU2();
    turnF2();
}
void QCube::reversethird()
{
    BturnU2();
    BturnL2();
    turnU2();
    turnL2();
    turnU2();
    turnF2();
    BturnU2();
    BturnF2();
}

void QCube::thirdlevel()
{
    int i,j,x,y,k;
        for (k=0;k<4;k++)
        {
            x=cube2[1][1][2].color[3];
            y=cube2[0][1][1].color[2];
            for (i=0;i<4;i++)
            {
             if (((cube2[0][1][2].color[2]==x)&&(cube2[0][1][2].color[3]==y))||((cube2[0][1][2].color[2]==y)&&(cube2[0][1][2].color[3]==x)))
              reversethird();
             for (j=0;j<3;j++)
             {
               turnY2(j,0);
               ch[count]='Y';
               level[count]=j;
               count++;
             }
         }
            for (i=0;i<4;i++)
            {
                if ((cube2[1][2][2].color[3]==x)&&(cube2[1][2][2].color[1]==y))
                 {
                        reversethird();
                        break;
                 }
                if ((cube2[1][2][2].color[3]==y)&&(cube2[1][2][2].color[1]==x))
                {
                    turnU2();
                    for (int s=0;s<3;s++)
                      for (j=0;j<3;j++)
                        {
                        turnY2(j,0);
                        ch[count]='Y';
                         level[count]=j;
                        count++;
                         }
                     third();
                      for (j=0;j<3;j++)
                          {
                       turnY2(j,0);
                       ch[count]='Y';
                       level[count]=j;
                       count++;
                       }
                       break;
               }
               turnU2();
            }
            for (i=0;i<3;i++)
                {
                 turnY2(i,0);
                ch[count]='Y';
                level[count]=i;
                count++;
                }
        }
}

void QCube::fourth1()
{
    turnF2();
    turnU2();
    turnR2();
    BturnU2();
    BturnR2();
    BturnF2();
}

void QCube::fourth2()
{
    turnF2();
    turnR2();
    turnU2();
    BturnR2();
    BturnU2();
    BturnF2();
}

void QCube::fourthlevel()
{
    int i,z=0,y=0;
    bool b=false;
    z=cube2[1][2][1].color[1];
    y=(z==cube2[1][2][2].color[1])+(z==cube2[2][2][1].color[1])+(z==cube2[1][2][0].color[1])+(z==cube2[0][2][1].color[1]);
    if (y==0)
      fourth1();
    if(y==4)
      return;
    for (i=0;i<4;i++)
    {
        if (cube2[0][2][1].color[1]==z&&cube2[1][2][0].color[1]==z)
         {
                fourth1();
                b=true;
                break;
        }
       turnU2();
    }
    if (b) return;
    if (cube2[0][2][1].color[1]==z&&cube2[2][2][1].color[1]==z)
     fourth2();
     else {
            turnU2();
            fourth2();
        }
}

void QCube::fifth()
{
    turnR2();turnU2();BturnR2();turnU2();turnR2();
    turnU2();turnU2();BturnR2();
}

void QCube::fifthlevel()
{
    int z,i,j,t=0;
    z=cube2[1][2][1].color[1];
    for (i=0;i<=6;i++)
    {
      t=(z==cube2[2][2][2].color[1])+(z==cube2[0][2][2].color[1])+(z==cube2[0][2][0].color[1])+(z==cube2[2][2][0].color[1]);
      if (t==4) return;
      if (t==0)
            for (j=0;j<4;j++)
            {
                if (cube2[0][2][2].color[2]==z) {fifth();break;}
                 turnU2();
            }
    if (t==1)
        for (j=0;j<4;j++)
        {
            if (cube2[0][2][2].color[1]==z)  {fifth();break;}
            turnU2();
        }
   if (t==2)
   {
        for (j=0;j<4;j++)
        {
          if (cube2[0][2][2].color[3]==z) {fifth();break;}
          turnU2();
        }
    }
}
}

void QCube::sixth()
{
    BturnR2();turnF2();BturnR2();turnB2();turnB2();turnR2();BturnF2();
    BturnR2();turnB2();turnB2();turnR2();turnR2();BturnU2();
}

int QCube::correct()
{
    int t=0;
    for (int i=0;i<4;i++)
    {
      t=t+((cube2[1][1][2].color[3]==cube2[0][2][2].color[3])&&(cube2[0][1][1].color[2]==cube2[0][2][2].color[2]));
      for (int j=0;j<3;j++)
      {
        turnY2(j,0);
      }
    }
    return t;
}

void QCube::sixthlevel()
{
    int i,j,t;
    for(i=0;i<4;i++)
    {
        t=correct();
        if(t==4)
        {
        return;
        }
        if (t>=2) break;
        turnU2();
    }
   for (i=0;i<2;i++)
   {
    if ((cube2[1][1][2].color[3]==cube2[0][2][2].color[3])&&(cube2[0][1][1].color[2]==cube2[0][2][2].color[2])&&(cube2[2][1][1].color[4]==cube2[2][2][0].color[4])&&(cube2[1][1][0].color[5]==cube2[2][2][0].color[5]))
    {
        sixth();break;
     }
    for (j=0;j<3;j++)
        {
         turnY2(j,0);
        ch[count]='Y';
        level[count]=j;
        count++;
        }
   }
   bool b=false;
   for (int w=0;w<4;w++)
   {
       if (b) break;
   for (j=0;j<4;j++)
   {
       if ((cube2[0][1][1].color[2]==cube2[0][2][0].color[2])&&(cube2[1][1][0].color[5]==cube2[0][2][0].color[5])&&(cube2[2][1][1].color[4]==cube2[2][2][0].color[4])&&(cube2[1][1][0].color[5]==cube2[2][2][0].color[5]))
           {
           sixth();b=true;break;
           }
       turnU2();
   }
   if (!b)
   {
         for (i=0;i<3;i++)
             {
           turnY2(i,0);
          ch[count]='Y';
          level[count]=i;
          count++;
             }
   }
   }
}

void QCube::shun()
{
    turnF2();turnF2();turnU2();turnL2();BturnR2();turnF2();turnF2();BturnL2();turnR2();turnU2();turnF2();turnF2();
}

void QCube::ni()
{
    turnF2();turnF2();BturnU2();turnL2();BturnR2();turnF2();turnF2();BturnL2();turnR2();BturnU2();turnF2();turnF2();
}

void QCube::seventhlevel()
{
    bool complete=false;
    if ((cube2[1][2][0].color[5]==cube2[1][1][0].color[5])&&(cube2[0][1][1].color[2]==cube2[0][2][1].color[2]))
        return;
    while(!complete)
    {
        for(int i=0;i<4;i++)
        {
            if(cube2[1][2][0].color[5]==cube2[1][1][0].color[5])
            {
                if(cube2[1][2][2].color[3]==cube2[0][1][1].color[2])
                shun();
                else
                ni();
                complete=true;
                return;
            }
            for(int j=0;j<3;j++)
            {
            turnY2(j,0);
            ch[count]='Y';
            level[count]=j;
            count++;
             }
        }
        shun();
    }
}

void QCube::print()
{
    int i,j;
    for (i=0;i<3;i++)
    {
     qDebug()<<"         ";
     for (j=0;j<3;j++)
       {
            qDebug()<<cube2[j][2][i].color[1]<<" ";
        }
        qDebug()<<endl;
    }
    qDebug()<<"||";
    for (j=0;j<3;j++)
    {
     for (i=0;i<3;i++)
       {
            qDebug()<<cube2[0][2-j][i].color[2]<<" ";
        }
    }
    qDebug()<<"||";
    for (j=0;j<3;j++)
     for (i=0;i<3;i++)
       {
            qDebug()<<cube2[i][2-j][2].color[3]<<" ";
        }
       qDebug()<<"||";
      for (j=0;j<3;j++)
   for (i=0;i<3;i++)
       {
            qDebug()<<cube2[2][2-j][2-i].color[4]<<" ";
        }
        qDebug()<<"||";
        for(j=0;j<3;j++)
    for (i=0;i<3;i++)
       {
            qDebug()<<cube2[2-i][2-j][0].color[5]<<" ";
        }
    qDebug()<<endl;
    for (j=0;j<3;j++)
    {
        qDebug()<<"        ";
     for (i=0;i<3;i++)
       {
            qDebug()<<cube2[i][0][2-j].color[6]<<" ";
        }
        qDebug()<<endl;
    }
    }

