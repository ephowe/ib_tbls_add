
#define IBPP_WINDOWS

#include "ibpp_core\_ibpp.h"

//ibpp,台位前缀,台位别名,台位[起始号],台位[尾号],楼层数,台位人数限制,总参数数量,每行显示台位数,台位位置x,y,营业点号,TBL号,GRAD序号,区域,X坐标,Y坐标,宽,高,逢4跳号 ,返回值1成功,0失败
int Add_Tables_Format(IBPP::Statement mst,		//ibpp,
						char (*des_lay)[50],	//台位前缀,
						char (*pinit)[50],		//台位缩写,
						int *des_each_start,	//台位[起始号],
						int *des_each_end,		//台位[尾号],
						int *cpx,				//楼层数,
						int *pax,				//台位人数限制,
						int cnt,				//总参数数量,
						int cols,				//每行显示台位数,
						int colx,				//起始列
						int coly,				//起始行
						int offsetx,			//是否在余下行数中以起始列开始
						int prest,				//营业点号
						int ptbl,				//TBL号,
						int pgrad,				//GRAD序号,
						char (*parea)[50],		//区域,
						char (*proomtyp)[50],	//台位类型,
						int pleft,				//列间距,
						int ptop,				//行间距,
						int mwidth1,			//台位宽度,
						int mheight1,			//台位高度,
						bool y4);				//逢4跳号

//最大数字限制,目标数组指针,源数组指针,几个数字,分隔符关键字 ,返回值为转换的数字数量 //将字符串中的所有数字转入整数数组,字符串中数字只能是整数
int GetNumbers(int limit,int* dst,char* src,int bt,char delim);

//获取字符串,目标指针,源指针,待犾取个数,长度限制,分隔符关键字,返回为为实获取数量
int GetStr(char (*dst)[50],char* src,int cnt,int len,char delim);

//将IP与PATH分离
int GetIPAndPath(char *ip,char *path,char* src);