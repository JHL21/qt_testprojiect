#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define pi 3.1415926
extern double Angle[36001];
extern double distance[36001];

struct DispersedPoint//离散的点
{
	double Pointx;//x坐标
	double Pointy;//y坐标
};

struct LineType//直线
{
	double x_Start;//起点x坐标
	double y_Start;//起点y坐标
	double x_End;//终点x坐标
	double y_End;//终点y坐标
	
};

struct ARC_Type//圆弧
{
	double cx;//圆心x轴坐标
	double cy;//圆心y轴坐标
	double r;//半径
	double arc_Start;//圆弧起始弧度
	double arc_End;//圆弧终点弧度
};
struct Circl_Type//整圆
{
	double cx;//圆心x轴坐标
	double cy;//圆心y轴坐标
	double r;//圆半径
};

typedef struct
{
  double x;
  double y;
}PointData;


//extern PointData P[1000];
//extern int n;


extern int factor;//放大因子，初始化是毫米，若是其他转换
extern struct ARC_Type ARC_P[100];
extern struct LineType LineP[3601];
extern struct Circl_Type Circl[10];
extern struct DispersedPoint DispersedP[100000];
extern int ARC_Num;//圆弧个数
extern int CirclNum;//圆个数
extern int Line_Num;//直线个数
extern int TotalNum;//圆弧，圆，直线总的个数
extern int SortNum[5000];//将圆弧，圆，直线的顺序排列
extern double AngleCal(double x, double y);
extern void ReadDxfData(char *FilePath);//读Dxf文件函数
extern void LineDispersed(DispersedPoint *DispP);//曲线离散
extern void LineDisp(LineType Line,DispersedPoint *DispP,int *TotalPnum);//直线
extern void ArcDisp(ARC_Type ArcP,DispersedPoint *DispP, int *TotalPnum);//圆弧
extern void CirCleDisp(Circl_Type CirP,DispersedPoint *DispP, int *TotalPnum);//圆
