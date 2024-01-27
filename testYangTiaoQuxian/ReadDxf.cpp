#include "DxfData.h"
#include<math.h>
#define PI 3.1415926
#define CalAngle 0.5//间隔0.5度计算圆或者圆弧
#define LineSpace 10//每条直线分成10点

//int n = 0;
//PointData P[1000];
int factor = 1;
struct ARC_Type ARC_P[100];
struct LineType LineP[3601];
struct Circl_Type Circl[10];
struct DispersedPoint DispersedP[100000];
int ARC_Num;
int CirclNum;
int Line_Num;
int TotalNum;//圆弧，圆，直线总的个数
int SortNum[5000];//将圆弧，圆，直线的顺序排列

void ReadDxfData(char *FilePath)
{
	FILE * fp;
	char str[255];
	int buffsize;
	int linesize;
	fp = fopen(FilePath, "r");
	if (fp == NULL)
	{
		printf("error!opening file!\n");
		exit(1);
	}
	while (!feof(fp))
	{
		fgets(str, 255, fp);
		//if (strcmp(str,"ENTITIES\n") == 0)//进入实体 
		if (strcmp(str,"$INSUNITS\n") == 0)//获取单位，其中4是毫米，5是厘米，6是米
		{
			fgets(str, 255, fp);//70
			fgets(str,255,fp);//单位
			int fum = atoi(str);
			
			if (fum == 4) //毫米
			{
				factor = 1;
			}
			else if (fum == 5) //厘米
			{
				factor = 10;
			}
			else if (fum == 6) //米
			{
				factor = 1000;
			}
			printf("放大倍数：%d\n", factor);
		}
		if (strcmp(str, "LINE\n") == 0)
		{
			printf("LINE:\n");
			while (!feof(fp))
			{
				fgets(str, 255, fp);
				bool isEnd = false;
				while (strcmp(str, " 10\n") == 0) {
					/*fscanf(fp, "%s\n", str);*/
					fgets(str, 255, fp);
					LineP[Line_Num].x_Start = atof(str) * factor;
					printf("%s\n", str);
					break;
				}
				while (strcmp(str, " 20\n") == 0) {
					/*fscanf(fp, "%s\n", str);*/
					fgets(str, 255, fp);
					LineP[Line_Num].y_Start = atof(str) * factor;
					printf("%s\n", str);
					break;
				}
				while (strcmp(str, " 30\n") == 0) {
					/*fscanf(fp, "%s\n", str);*/
					fgets(str, 255, fp);
					//LineP[Line_Num].z_Start = atof(str);
					printf("%s\n", str);
					break;
				}

				while (strcmp(str, " 11\n") == 0) {
					/*fscanf(fp, "%s\n", str);*/
					fgets(str, 255, fp);
					LineP[Line_Num].x_End = atof(str) * factor;
					printf("%s\n", str);
					break;
				}
				while (strcmp(str, " 21\n") == 0) {
					/*fscanf(fp, "%s\n", str);*/
					fgets(str, 255, fp);
					LineP[Line_Num].y_End = atof(str) * factor;
					printf("%s\n", str);
					
					break;
				}
				while (strcmp(str, " 31\n") == 0) {
					/*fscanf(fp, "%s\n", str);*/
					fgets(str, 255, fp);
					printf("%s\n", str);
					isEnd = true;
					Line_Num++;
					SortNum[TotalNum] = 0;
					TotalNum++;
					break;
				}
				if (isEnd)
					break;
			}

		}
		if (strcmp(str, "ARC\n") == 0)
		{
			printf("ARC\n");
			while (!feof(fp))
			{
				fgets(str, 255, fp);
				bool isEnd = false;
				while (strcmp(str, " 10\n") == 0) {
					/*fscanf(fp, "%s\n", str);*/
					fgets(str, 255, fp);
					printf("%s\n", str);
					ARC_P[ARC_Num].cx = atof(str) * factor;
					break;
				}
				while (strcmp(str, " 20\n") == 0) {
					/*fscanf(fp, "%s\n", str);*/
					fgets(str, 255, fp);
					printf("%s\n", str);
					ARC_P[ARC_Num].cy = atof(str) * factor;
					break;
				}
				while (strcmp(str, " 30\n") == 0) {
					/*fscanf(fp, "%s\n", str);*/
					fgets(str, 255, fp);
					printf("%s\n", str);
					break;
				}

				while (strcmp(str, " 40\n") == 0) {
					/*fscanf(fp, "%s\n", str);*/
					fgets(str, 255, fp);
					printf("%s\n", str);
					ARC_P[ARC_Num].r = atof(str) * factor;
					break;
				}
				while (strcmp(str, " 50\n") == 0) {
					/*fscanf(fp, "%s\n", str);*/
					fgets(str, 255, fp);
					printf("%s\n", str);
					ARC_P[ARC_Num].arc_Start = atof(str) * factor;
					break;
				}
				while (strcmp(str, " 51\n") == 0) {
					/*fscanf(fp, "%s\n", str);*/
					fgets(str, 255, fp);
					printf("%s\n", str);
					ARC_P[ARC_Num].arc_End = atof(str) * factor;
					isEnd = true;
					ARC_Num++;
					SortNum[TotalNum] = 1;
					TotalNum++;
					break;
				}
				if (isEnd)
					break;
			}
		}
		if (strcmp(str, "CIRCLE\n") == 0)
		{
			printf("CIRCLE\n");
			while (!feof(fp))
			{
				fgets(str, 255, fp);
				bool isEnd = false;
				while (strcmp(str, " 10\n") == 0) {
					/*fscanf(fp, "%s\n", str);*/
					fgets(str, 255, fp);
					printf("%s\n", str);
					Circl[CirclNum].cx = atof(str) * factor;
					break;
				}
				while (strcmp(str, " 20\n") == 0) {
					/*fscanf(fp, "%s\n", str);*/
					fgets(str, 255, fp);
					printf("%s\n", str);
					Circl[CirclNum].cy = atof(str) * factor;
					break;
				}
				while (strcmp(str, " 30\n") == 0) {
					/*fscanf(fp, "%s\n", str);*/
					fgets(str, 255, fp);
					printf("%s\n", str);
					break;
				}
				//半径
				while (strcmp(str, " 40\n") == 0) {
					/*fscanf(fp, "%s\n", str);*/
					fgets(str, 255, fp);
					printf("%s\n", str);
					Circl[CirclNum].r = atof(str) * factor;
					isEnd = true;
					CirclNum++;
					SortNum[TotalNum] = 2;
					TotalNum++;
					break;
				}
				if (isEnd)
					break;
			}
		}
	}
	fclose(fp);
	LineDispersed(DispersedP);//将曲线离散化

    //P = P2;
	printf("");
}

void LineDispersed(DispersedPoint *DispP)//曲线离散
{
	int LineN = 0,ArcN = 0, CircleN = 0;//圆弧，圆，直线的数量
	int TotalPnum = 0;//总的分成点的数量
	for (int i = 0; i < TotalNum;i++)//
	{
		int unType = SortNum[i];
		if (unType == 0) //直线
		{
			for (int j = 0; j < Line_Num;j++)
			{
				if (j == LineN)//找到当前的线段 
				{
					LineDisp(LineP[j],DispP, &TotalPnum);//直线离散
					break;
				}
			}
			LineN++;
		}
		else if(unType == 1)//圆弧
		{
			for (int j = 0; j < ARC_Num; j++)
			{
				if (j == ArcN)//找到当前的线段 
				{
					ArcDisp(ARC_P[j], DispP, &TotalPnum);//圆弧离散
					break;
				}
			}
			ArcN++;
		}
		else if (unType == 2) 
		{
			for (int j = 0; j < CirclNum; j++)
			{
				if (j == CircleN)//找到当前的线段 
				{
					CirCleDisp(Circl[j], DispP, &TotalPnum);//圆离散
					break;
				}
				
			}
			CircleN++;
		}
	}

    printf("1\n");
}

//将直线离散成点
void LineDisp(LineType Line, DispersedPoint *DispP, int *TotalPnum)//直线
{
	double StartX = Line.x_Start;//起点x坐标
	double StartY = Line.y_Start;//起点y坐标
	double EndX = Line.x_End;//终点x坐标
	double EndY = Line.y_End;//终点y坐标
	if (StartX != EndX && EndY != StartY) 
	{
		double LineX, LineY,LineB;
		double LineK = (EndY - StartY) / (EndX - StartX);//斜率
		double distant = EndX - StartX;
		double simp = distant / LineSpace;
		LineB = StartY - StartX * LineK;
		for (int i = 0; i < LineSpace;i++)
		{
			if (i == LineSpace - 1)
			{
				DispP[*TotalPnum + i].Pointx = EndX;
				DispP[*TotalPnum + i].Pointy = EndY;
			}
			else
			{
				LineX = StartX + i * simp;
				LineY = StartY + LineK * LineX + LineB;
				DispP[*TotalPnum + i].Pointx = LineX;
				DispP[*TotalPnum + i].Pointy = LineY;
			}
				
		}
		*TotalPnum = *TotalPnum + LineSpace;
	}
}
void ArcDisp(ARC_Type ArcP, DispersedPoint *DispP, int *TotalPnum)//圆弧
{
	double CenterX = ArcP.cx;//起点x坐标
	double CenterY = ArcP.cy;//起点y坐标
	double AngleStart = ArcP.arc_Start;//终点x坐标
	double AngleEnd = ArcP.arc_End;//终点y坐标
	double ArcR = ArcP.r;//圆半径
	if (AngleStart != AngleEnd) 
	{
		
		double Angle = fabs(AngleEnd - AngleStart);
		int num = Angle / CalAngle;//每0.5度求圆弧上的点
		
		double nextAngle,ArcX, ArcY;
		for (int i = 0; i < num;i++)
		{
			if (i == num - 1)//最后一次将终点的角度存储
				nextAngle = AngleEnd;
			else
				nextAngle = AngleStart + i * Angle / num;
            ArcX = CenterX + ArcR * cos(nextAngle *PI/180);
            ArcY = CenterY + ArcR * sin(nextAngle *PI/180);
			DispP[*TotalPnum + i].Pointx = ArcX;
			DispP[*TotalPnum + i].Pointy = ArcY;
		}
		*TotalPnum = *TotalPnum + num;
	}
}
void CirCleDisp(Circl_Type CirP, DispersedPoint *DispP, int *TotalPnum) //圆
{
	double CenterX = CirP.cx;//起点x坐标
	double CenterY = CirP.cy;//起点y坐标
	double AngleStart = 0;//终点x坐标
	double AngleEnd = 360;//终点y坐标
	double CirR = CirP.r;//圆半径
	if (AngleStart != AngleEnd)
	{
		double Angle = fabs(AngleEnd - AngleStart);
		int num = Angle / CalAngle;//每0.5度求圆弧上的点

		double nextAngle, ArcX, ArcY;
		for (int i = 0; i < num; i++)
		{
			if (i == num - 1)//最后一次将终点的角度存储
				nextAngle = AngleEnd;
			else
				nextAngle = AngleStart + i * Angle / num;
            ArcX = CenterX + CirR * cos(nextAngle *PI/180);
            ArcY = CenterY + CirR * sin(nextAngle *PI/180);
			DispP[*TotalPnum + i].Pointx = ArcX;
			DispP[*TotalPnum + i].Pointy = ArcY;
		}
		*TotalPnum = *TotalPnum + num;
	}
}
