
#define IBPP_WINDOWS

#include "ibpp_core\_ibpp.h"

//ibpp,̨λǰ׺,̨λ����,̨λ[��ʼ��],̨λ[β��],¥����,̨λ��������,�ܲ�������,ÿ����ʾ̨λ��,̨λλ��x,y,Ӫҵ���,TBL��,GRAD���,����,X����,Y����,��,��,��4���� ,����ֵ1�ɹ�,0ʧ��
int Add_Tables_Format(IBPP::Statement mst,		//ibpp,
						char (*des_lay)[50],	//̨λǰ׺,
						char (*pinit)[50],		//̨λ��д,
						int *des_each_start,	//̨λ[��ʼ��],
						int *des_each_end,		//̨λ[β��],
						int *cpx,				//¥����,
						int *pax,				//̨λ��������,
						int cnt,				//�ܲ�������,
						int cols,				//ÿ����ʾ̨λ��,
						int colx,				//��ʼ��
						int coly,				//��ʼ��
						int offsetx,			//�Ƿ�����������������ʼ�п�ʼ
						int prest,				//Ӫҵ���
						int ptbl,				//TBL��,
						int pgrad,				//GRAD���,
						char (*parea)[50],		//����,
						char (*proomtyp)[50],	//̨λ����,
						int pleft,				//�м��,
						int ptop,				//�м��,
						int mwidth1,			//̨λ���,
						int mheight1,			//̨λ�߶�,
						bool y4);				//��4����

//�����������,Ŀ������ָ��,Դ����ָ��,��������,�ָ����ؼ��� ,����ֵΪת������������ //���ַ����е���������ת����������,�ַ���������ֻ��������
int GetNumbers(int limit,int* dst,char* src,int bt,char delim);

//��ȡ�ַ���,Ŀ��ָ��,Դָ��,����ȡ����,��������,�ָ����ؼ���,����ΪΪʵ��ȡ����
int GetStr(char (*dst)[50],char* src,int cnt,int len,char delim);

//��IP��PATH����
int GetIPAndPath(char *ip,char *path,char* src);