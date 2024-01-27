#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//
//#define pi 3.1415926
extern double Angle[36001];
extern double distance[36001];

struct DispersedPoint//??????
{
	double Pointx;//x????
	double Pointy;//y????
};

struct LineType//ֱ��
{
	double x_Start;//���x����
	double y_Start;//���y����
	double x_End;//�յ�x����
	double y_End;//�յ�y����
	
};

struct ARC_Type//Բ��
{
	double cx;//Բ��x������
	double cy;//Բ��y������
	double r;//�뾶
	double arc_Start;//Բ����ʼ����
	double arc_End;//Բ���յ㻡��
};
struct Circl_Type//��Բ
{
	double cx;//Բ��x������
	double cy;//Բ��y������
	double r;//Բ�뾶
};

typedef struct
{
  double x;
  double y;
}PointData;


//extern PointData P[1000];
//extern int n;


extern int factor;//�Ŵ����ӣ���ʼ���Ǻ��ף���������ת��
extern struct ARC_Type ARC_P[100];
extern struct LineType LineP[3601];
extern struct Circl_Type Circl[10];
extern struct DispersedPoint DispersedP[100000];
extern int ARC_Num;//Բ������
extern int CirclNum;//Բ����
extern int Line_Num;//ֱ�߸���
extern int TotalNum;//Բ����Բ��ֱ���ܵĸ���
extern int SortNum[5000];//��Բ����Բ��ֱ�ߵ�˳������
extern double AngleCal(double x, double y);
extern void ReadDxfData(char *FilePath);//��Dxf�ļ�����
extern void LineDispersed(DispersedPoint *DispP);//������ɢ
extern void LineDisp(LineType Line,DispersedPoint *DispP,int *TotalPnum);//ֱ��
extern void ArcDisp(ARC_Type ArcP,DispersedPoint *DispP, int *TotalPnum);//Բ��
extern void CirCleDisp(Circl_Type CirP,DispersedPoint *DispP, int *TotalPnum);//Բ
