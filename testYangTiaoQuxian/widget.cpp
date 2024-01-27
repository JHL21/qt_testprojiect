#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <string.h>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    char *PathName = "D:/QT/testYangTiaoQuxian/myfile.dxf";
	ReadDxfData(PathName);
}



void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    int n = 0;
    for(int i=0;i<100000;i++)
    {
        if(DispersedP[i].Pointx ==0 && DispersedP[i].Pointy == 0)
        {
            n = i;

            break;
        }
    }
    n = n-1;
    PointData P[n];
    memcpy(P,DispersedP,sizeof(P));


  /*  P[1].x = 0, P[1].y = 0;
    P[1].x = 0, P[1].y = 0;
    P[2].x = 40, P[2].y =  40;
    P[3].x =  60,   P[3].y =  23;
    P[4].x =  100, P[4].y =  40;
    P[5].x =  120, P[5].y =  20;
    P[6].x =  160, P[6].y =  40;*/

    const int dim = n;//二维数组维数
    double b1 = 0, bn = 0;//边界条件:"夹持端",给出起点和终点的一阶导数
    double h[dim], lambda[dim], mu[dim], D[dim];
    double l[dim], m[dim], u[dim];
    double M[dim], K[dim];
    double a[dim], b[dim], c[dim], d[dim];
    for(int i = 1; i < n; i++)//计算hi＝xi+1-xi
        h[i] = P[i+1].x - P[i].x;
    for(int i = 2; i < n; i++)
    {
        lambda[i] = h[i-1]/(h[i-1]+h[i]);//计算λ
        mu[i] = h[i]/(h[i-1]+h[i]);//计算μ
        D[i] = 6/(h[i-1]+h[i])*((P[i+1].y-P[i].y)/h[i]-(P[i].y-P[i-1].y)/h[i-1]);//计算D
    }
    D[1]=6*((P[2].y-P[1].y)/h[1]-b1)/h[1];//夹持端的D[1]
    D[n]=6*(bn-(P[n].y-P[n-1].y)/h[n-1])/h[n-1];//夹持端的D[n]
    mu[1]=1;//夹持端的μ[1],
    lambda[n]=1;//夹持端的λ[n]
    //追赶法求解三弯矩方程
    l[1]=2;
    u[1]=mu[1]/l[1];
    for(int i=2; i <= n; i++)
    {
        m[i]=lambda[i];
        l[i]=2-m[i]*u[i-1];
        u[i]=mu[i]/l[i];
    }
    K[1] = D[1]/l[1];//解LK=D
    for(int i = 2; i <= n;i++)
    {
        K[i]=(D[i]-m[i]*K[i-1])/l[i];
    }
    M[n] = K[n];//解UM=K
    for(int i = n-1; i >= 1;i--)
    {
        M[i]=K[i]-u[i]*M[i+1];
    }
    //计算三次样条函数的系数
    for(int i = 1; i < n; i++)
    {
        a[i] = P[i].y;
        b[i] = (P[i+1].y-P[i].y)/h[i] - h[i]*(M[i]/3+M[i+1]/6);
        c[i] = M[i]/2;
        d[i] = (M[i+1]-M[i])/(6*h[i]);
    }
    double xStep = 0.5;//x的步长
    double x, y;//当前点
    double lineStartX = -1,lineStartY,lineEndX,lineEndY;
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue,4));
    for(int i = 1; i < n; i++)//循环访问每个节点
    {
        for(x = P[i].x; x < P[i+1].x; x += xStep)//循环访问每个节点
        {
            y=a[i]+b[i]*(x-P[i].x)+c[i]*(x-P[i].x)*(x-P[i].x)+d[i]*(x-P[i].x)*(x-P[i].x)*(x-P[i].x);
            lineEndX = x;
            lineEndY = y;
            if(lineStartX != -1)
            {

                painter.drawLine(lineStartX,lineStartY,lineEndX,lineEndY);
            }
            lineStartX = lineEndX;
            lineStartY = lineEndY;
        }
    }


        //painter.drawLine(0,0,100,100);
}

Widget::~Widget()
{
    delete ui;
}
