#include "DxfData.h"
#include<math.h>
#define PI 3.1415926
#define CalAngle 0.5//���0.5�ȼ���Բ����Բ��
#define LineSpace 10//ÿ��ֱ�߷ֳ�10��

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
int TotalNum;//Բ����Բ��ֱ���ܵĸ���
int SortNum[5000];//��Բ����Բ��ֱ�ߵ�˳������

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
		//if (strcmp(str,"ENTITIES\n") == 0)//����ʵ�� 
		if (strcmp(str,"$INSUNITS\n") == 0)//��ȡ��λ������4�Ǻ��ף�5�����ף�6����
		{
			fgets(str, 255, fp);//70
			fgets(str,255,fp);//��λ
			int fum = atoi(str);
			
			if (fum == 4) //����
			{
				factor = 1;
			}
			else if (fum == 5) //����
			{
				factor = 10;
			}
			else if (fum == 6) //��
			{
				factor = 1000;
			}
			printf("�Ŵ�����%d\n", factor);
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
				//�뾶
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
	LineDispersed(DispersedP);//��������ɢ��

    //P = P2;
	printf("");
}

void LineDispersed(DispersedPoint *DispP)//������ɢ
{
	int LineN = 0,ArcN = 0, CircleN = 0;//Բ����Բ��ֱ�ߵ�����
	int TotalPnum = 0;//�ܵķֳɵ������
	for (int i = 0; i < TotalNum;i++)//
	{
		int unType = SortNum[i];
		if (unType == 0) //ֱ��
		{
			for (int j = 0; j < Line_Num;j++)
			{
				if (j == LineN)//�ҵ���ǰ���߶� 
				{
					LineDisp(LineP[j],DispP, &TotalPnum);//ֱ����ɢ
					break;
				}
			}
			LineN++;
		}
		else if(unType == 1)//Բ��
		{
			for (int j = 0; j < ARC_Num; j++)
			{
				if (j == ArcN)//�ҵ���ǰ���߶� 
				{
					ArcDisp(ARC_P[j], DispP, &TotalPnum);//Բ����ɢ
					break;
				}
			}
			ArcN++;
		}
		else if (unType == 2) 
		{
			for (int j = 0; j < CirclNum; j++)
			{
				if (j == CircleN)//�ҵ���ǰ���߶� 
				{
					CirCleDisp(Circl[j], DispP, &TotalPnum);//Բ��ɢ
					break;
				}
				
			}
			CircleN++;
		}
	}

    printf("1\n");
}

//��ֱ����ɢ�ɵ�
void LineDisp(LineType Line, DispersedPoint *DispP, int *TotalPnum)//ֱ��
{
	double StartX = Line.x_Start;//���x����
	double StartY = Line.y_Start;//���y����
	double EndX = Line.x_End;//�յ�x����
	double EndY = Line.y_End;//�յ�y����
	if (StartX != EndX && EndY != StartY) 
	{
		double LineX, LineY,LineB;
		double LineK = (EndY - StartY) / (EndX - StartX);//б��
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
void ArcDisp(ARC_Type ArcP, DispersedPoint *DispP, int *TotalPnum)//Բ��
{
	double CenterX = ArcP.cx;//���x����
	double CenterY = ArcP.cy;//���y����
	double AngleStart = ArcP.arc_Start;//�յ�x����
	double AngleEnd = ArcP.arc_End;//�յ�y����
	double ArcR = ArcP.r;//Բ�뾶
	if (AngleStart != AngleEnd) 
	{
		
		double Angle = fabs(AngleEnd - AngleStart);
		int num = Angle / CalAngle;//ÿ0.5����Բ���ϵĵ�
		
		double nextAngle,ArcX, ArcY;
		for (int i = 0; i < num;i++)
		{
			if (i == num - 1)//���һ�ν��յ�ĽǶȴ洢
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
void CirCleDisp(Circl_Type CirP, DispersedPoint *DispP, int *TotalPnum) //Բ
{
	double CenterX = CirP.cx;//���x����
	double CenterY = CirP.cy;//���y����
	double AngleStart = 0;//�յ�x����
	double AngleEnd = 360;//�յ�y����
	double CirR = CirP.r;//Բ�뾶
	if (AngleStart != AngleEnd)
	{
		double Angle = fabs(AngleEnd - AngleStart);
		int num = Angle / CalAngle;//ÿ0.5����Բ���ϵĵ�

		double nextAngle, ArcX, ArcY;
		for (int i = 0; i < num; i++)
		{
			if (i == num - 1)//���һ�ν��յ�ĽǶȴ洢
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
