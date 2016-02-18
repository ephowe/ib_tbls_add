
#include "stdafx.h"

#include "ibpp_core\all_in_one.cpp"

using namespace std;


int GetIPAndPath(char *ip,char *path,char* src)
{

	bool isip = false,retip = false;

	int iplmt[4] = {-1},ipfull = 0;

	char *oip = ip;

	if ( *src >= '1' && *src <= '9') retip = isip = true;
	
	do{
		if (*src == ':' && isip) 
		{
			isip = false;
			src++;
		}else if (*src == '.' && isip ) ipfull++;
			
		if (isip) *ip++ = *src;
		else *path++ = *src;


	}while (*src++);

	if (retip)
	{
		if (ipfull != 3 ) return -1;	//IP地址是否完整

		if ( GetNumbers(255,iplmt,oip,4,'.') == -1) return -2;	//IP地址数值是否有超过255
	}
	return int(retip);	//有IP返回1,无IP返回0
}

int GetNumbers(int limit,int* dst,char* src,int bt,char delim)
{
	//dt为dst数据index
	int dt=0, i=0;

	bool isnum = false;

	char numtmp[10]= {'\0'};
	
	do{
		if ( *src >= '0' && *src <= '9')
		{
			if (i < 10) numtmp[i++] = *src;

			isnum = true;
			
		}
		else if ((*src == delim || *src == '\0' ) && isnum )	//检查是否到分隔符或最后一个数字,是否存在数字
		{
			numtmp[i] = '\0';

			if (dt < bt) 
			{
				if ( ( dst[dt++] = atoi(numtmp) ) > limit ) return  -1;       //-dt;则返回过大的数值的位置的负数;
			}
			else return -2;

			if (*src == delim) isnum = false;

			i = 0;
		}
		else if (*src == '-') {	//负数
			//项中第一个字符是负号
			if (i == 0) numtmp[i++] = *src; else return -2;
		}
	}while (*src++);

	if (!isnum) return -3;

	return dt;
}

int GetStr(char (*dst)[50],char* src,int cnt,int len,char delim)
{
	//dst[ct][ln]
	int ct = 0,ln = 0;

	bool err = false;

	do{
		if ( *src == delim || *src == '\0' )	//检测字母楼层号
		{			
			if (ct < cnt && ln < len) dst[ct++][ln] = '\0'; //(*dst + ct++)[ln] = '\0'; 

			ln =0;

			if (*src == delim) err = true;
		}
		else
		{
			if (ct < cnt && ln < len) dst[ct][ln++] = *src; //(*dst + ct)[ln++] = *src;

			err = false;
		}
	}while (*src++);

	if (err) return -1;

	return ct;
}


void Add_Tables(IBPP::Statement mst,int REST,int TBL,int GRAD,char* PAREA,char* PROOMTYP,string PDES,string PINIT,int CPX,int PAX,int TOP1,int LEFT1,int WIDTH1,int HEIGHT1)
{
	string msql;
	char mtmp[50];

	msql = "INSERT INTO TABLES (TBL,REST,DES,INIT,STATUS,CPX,PAX,ROOMTYP,TOPX,TOP1,LEFTY,LEFT1,WIDTH1,HEIGHT1,ROOMCONNECT,SHAPE1,SVC,DISC,MINCONSUM,AREA,LOCKED,GRAD) VALUES(";

	sprintf_s(mtmp,50,"%d",TBL);
	msql += string(mtmp);

	msql += ",";

	sprintf_s(mtmp,50,"%d", REST);
	msql += string(mtmp);

	msql += ",'" + PDES+"','"+ PINIT +"','C',";
	
	sprintf_s(mtmp,50,"%d", CPX);
	msql += string(mtmp) + ",";

	sprintf_s(mtmp,50,"%d", PAX);
	msql += string(mtmp);

	msql += ",'" + string(PROOMTYP) + "',";

	sprintf_s(mtmp,50,"%d",TOP1);
	msql += string(mtmp) + "," + string(mtmp) + ",";

	sprintf_s(mtmp,50,"%d",LEFT1);
	msql += string(mtmp) + ","+ string(mtmp) + ",";

	sprintf_s(mtmp,50,"%d",WIDTH1);
	msql += string(mtmp) + ",";

	sprintf_s(mtmp,50,"%d",HEIGHT1);
	msql += string(mtmp) + ",'N',1,0,0,0.00,'" + string(PAREA) + "',1,";

	sprintf_s(mtmp,50,"%d",GRAD);
	msql += string(mtmp) + ")";

	//"INSERT INTO TABLES (TBL,REST,DES,INIT,STATUS,CPX,ROOMTYP,TOP1,LEFT1,WIDTH1,HEIGHT1,ROOMCONNECT,SHAPE1,SVC,DISC,MINCONSUM,AREA,LOCKED,GRAD)"
	//"VALUES(159,2,'310','','C',2,'散座',500,500,60,60,'N',1,0,0,0.00,'B区',1,TBL)"

	mst->Execute(msql);
}


//批量添加台号,支持跳过4台位
int Add_Tables_Format(IBPP::Statement mst,char (*des_lay)[50],char (*pinit)[50],
	int *des_each_start,int *des_each_end,int *cpx,int *pax,int cnt,int cols,int colx,int coly,int offsetx,
	int prest,int ptbl,int pgrad,char (*parea)[50],char (*proomtyp)[50],int pleft,int ptop,int mwidth1,int mheight1,bool y4)
{
	int des_total = 0 , rows, n = 0, dcode = des_each_start[n]; //var = 0  dcode = 台位起始号[n]

	///////////////////////////////

	int mtbl = ptbl, mgrd = pgrad, mtop1 = ptop, mleft1 = pleft;
	int xleft = 0;
	//char mdes[20];	//,mroomtyp[10]="散座",marea[10]="A区";
	string mdes,minit;
	char tmp[10];

	//////////////////////////////////

	if (colx <= 0 || coly <= 0) return 0;
	int clx = 1;
	//if (colx <= cols) 
	clx = colx;// % cols;
	//if (clx == 0) clx = 1;

	xleft = mleft1 = pleft +( pleft + mwidth1 ) * (clx-1);
	mtop1  = ptop + ( ptop + mheight1 ) * --coly;

	for (int i=0; i < cnt;i++) 
	{
		if (des_each_end[i] >= des_each_start[i]) 
		{
			des_total += ( des_each_end[i] - des_each_start[i] + 1); //获得台位总数例 (5 ~ 8) = 8 - 5 + 1
		}
		else return 0;
	}


	rows =  int(float(des_total + clx - 1 ) / cols + 0.9999); //除于每行显示台位数,得到行数,超出一行一个以上就增加一行


	clx = (clx <= cols ? clx : 1) - (offsetx < 1 ? offsetx : 0);

	

	for(int y =1; y <= rows; y++)
	{
		///////////////////////
		/////////////////////
		for(int x= clx; x <= cols; x++ ,dcode++)
		{

			if (y4) if ( dcode % 10 == 4 ) dcode++; //des_each_start[n]++

			if ( dcode > des_each_end[n] ) 
			{
				//dcode=1;			//dcode = 台位起始号[n+1]
				if ( ++n < cnt ) 
				{
					dcode = des_each_start[n];
				}
				else return 1;
			}



			if ( dcode == 0 )
			{
				mdes = string(des_lay[n]);
				minit = string(pinit[n]);						
			}
			else if ( dcode < 10 && dcode > 0 )
			{
				sprintf_s(tmp,10,"%d",dcode);
				mdes = string(des_lay[n]) + '0' + string(tmp);
				minit = string(pinit[n]) + '0' + string(tmp);
			}
			else
			{
				sprintf_s(tmp,10,"%d",dcode);
				mdes = string(des_lay[n]) + string(tmp);
				minit = string(pinit[n]) + string(tmp);
			}

			//插入数据库记录 

			Add_Tables(mst, prest, mtbl++, mgrd++, parea[n],proomtyp[n], mdes ,minit, cpx[n],pax[n], mtop1, mleft1, mwidth1, mheight1);

			mleft1 = (pleft + mwidth1) * (x + (offsetx < 1 ? offsetx : 0) );// +pleft;
			//if (isx) mleft1 += xleft >= pleft ? xleft - pleft : pleft;

			//if (colx >= abs(offsetx) && cols >= abs(offsetx) ){
				mleft1 += offsetx < 1 ? xleft : 0;
			//}

		}
		clx =1;

		//if (isx) mleft1 = xleft; else mleft1 = pleft;		//重置left
		mleft1 = offsetx < 1 ? ( xleft + offsetx * (pleft + mwidth1) ) : pleft;

		/*
		if (colx >= abs(offsetx) && cols >= abs(offsetx) ) {
			mleft1 = xleft + offsetx * (pleft + mwidth1);
		}
		*/

		mtop1  = ptop + ( ptop + mheight1 ) * (y+coly);
	}

	return 1;
}