
// ib_tbls_addDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ib_tbls_add.h"
#include "ib_tbls_addDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cib_tbls_addDlg 对话框




Cib_tbls_addDlg::Cib_tbls_addDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cib_tbls_addDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	is_run = false;
}

void Cib_tbls_addDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit_in);
}

BEGIN_MESSAGE_MAP(Cib_tbls_addDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Cib_tbls_addDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &Cib_tbls_addDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// Cib_tbls_addDlg 消息处理程序

BOOL Cib_tbls_addDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cib_tbls_addDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cib_tbls_addDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cib_tbls_addDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cib_tbls_addDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();

	//temp var
	char g_szDBName[100] = {'\0'};	//"F:\\Development\\Database\\ib\\data\\FOODBEV.GDB";
	//服务器名，针对服务器版本。对于嵌入式，它应该是""
	char g_szServerName[50] = {'\0'};

	//这里的用户名和密码是FireBird默认值，对于服务器版，用你自己的密码
	//对于嵌入式，就是这个（FireBird嵌入式版没有加密功能）。
	const char* g_szUserName = "SYSDBA";
	const char* g_szPassword = "masterkey";


	//char numtmp[10]= {'\0'};
	

	if (!is_run)
	{
		bool berr = false;

		int len,lct = m_edit_in.GetLineCount();	//获得总行数
		
		if (lct != 11) ///////
		{
			MessageBox("参数填写不完整","ERROR", MB_ICONEXCLAMATION );
			return;
		}


		/////////////////////////////////////////////
		//台位前缀,对应台位起始-尾号 2
		char (*twqzs)[50];
		int twqz_cnt =0;

		//台位别名,对应台位起始-尾号 3
		char (*twbms)[50];
		int twbm_cnt =0;

		//台位起始号 4
		int *twqshs,twqsh_cnt=0;

		//台位尾号 5
		int *twwhs,twwh_cnt = 0;
		
		//楼层号 6
		int *cpxs,cpx_cnt=0;

		//区域 7
		char (*areas)[50];
		int area_cnt=0;

		//台位类型 8
		char (*roomtyps)[50];
		int roomtyp_cnt=0;

		//台位最大人数 9
		int *paxs,pax_cnt=0;

		//台位信息,显示列数,起始列,起始行,是否区域显示,列间距,行间距,台位宽,台位长,共计8个参数 10
		int twone[8] = {0},tw_cnt =0;

		//营业点,台位内码TBL,台位序号GRAD,是否跳过尾号为4的台号,共计4个参数 11
		int tbl[4],tbl_cnt=0;

		//临时指针,数据缓冲区
		char *pb,**mBuf = new char*[lct];


		for(int i = 0;i < lct ; i++ )
		{ 
			len = m_edit_in.LineLength(m_edit_in.LineIndex(i));	//获得行数字符长度 ///////////////////////

			mBuf[i] = new char[len+1];		//长度+1最后位存放'\0'以免数据溢出
			
			m_edit_in.GetLine(i,LPTSTR(mBuf[i]),len);	//获得行内容

			mBuf[i][len] = '\0';	//
	
		}


		///////////////////////////////////////////////////////////////////////////////

		switch(GetIPAndPath(g_szServerName,g_szDBName,mBuf[0]))
		{
		case -2:  berr = true; MessageBox("IP地址有数值过大","ERROR", MB_ICONEXCLAMATION ); break;
		case -1:  berr = true; MessageBox("IP地址不完整","ERROR", MB_ICONEXCLAMATION ); break;
		//case 0: g_szServerName = "localhost"; break;
		}

		if (!berr)
		{

			//遍历字符串获得数字数量

			pb = mBuf[1];
			do{ if (*pb == ',') twqz_cnt++; }while (*pb++);

			pb = mBuf[2];
			do{ if (*pb == ',') twbm_cnt++; }while (*pb++);


			//twbm_cnt =0;

			//twqsh_cnt=0;twwh_cnt cpx_cnt

			//通过分隔符,初检查四个参数数量是否相等
			////////////////////----------------------------
			if (++twqz_cnt == ++twbm_cnt ) 
			{
				pb = mBuf[3];
				do{ if (*pb == ',') twqsh_cnt++; }while (*pb++);

				if (twbm_cnt == ++twqsh_cnt)
				{
					pb = mBuf[4];
					do{ if (*pb == ',') twwh_cnt++; }while (*pb++);

					if (twqsh_cnt == ++twwh_cnt)
					{
						pb = mBuf[5];
						do{ if (*pb == ',') cpx_cnt++; }while (*pb++);

						if (twwh_cnt == ++cpx_cnt )
						{
							pb = mBuf[6];
							do{ if (*pb == ',') area_cnt++; }while (*pb++);

							if (cpx_cnt == ++area_cnt)
							{
								pb = mBuf[7];
								do{ if (*pb == ',') roomtyp_cnt++; }while (*pb++);

								if (area_cnt == ++roomtyp_cnt)
								{
									pb = mBuf[8];
									do{ if (*pb == ',') pax_cnt++; }while (*pb++);

									if (roomtyp_cnt != ++pax_cnt)
									{
										berr = true; 
										MessageBox("第8,9参数数量不相等,请检查","ERROR", MB_ICONEXCLAMATION );	
									}
								}else { berr = true; MessageBox("第7,8参数数量不相等,请检查","ERROR", MB_ICONEXCLAMATION );}
							}else { berr = true; MessageBox("第6,7参数数量不相等,请检查","ERROR", MB_ICONEXCLAMATION );}				
						}else { berr = true; MessageBox("第5,6参数数量不相等,请检查","ERROR", MB_ICONEXCLAMATION );}
					}else { berr = true; MessageBox("第4,5参数数量不相等,请检查","ERROR", MB_ICONEXCLAMATION );}
				}else { berr = true; MessageBox("第3,4参数数量不相等,请检查","ERROR", MB_ICONEXCLAMATION );}
			}else { berr = true; MessageBox("第2,3参数数量不相等,请检查","ERROR", MB_ICONEXCLAMATION );}


			pb = mBuf[9];

			do{ if (*pb == ',') tw_cnt++; }while (*pb++);
		
			//如果台号参数不为8个,则出错
			if (++tw_cnt != 8) { berr = true; MessageBox("台位参数缺少或过多,请检查","ERROR", MB_ICONEXCLAMATION );}


			pb = mBuf[10];

			do{ if (*pb == ',') tbl_cnt++; }while (*pb++);

			if (++tbl_cnt != 4) { berr = true; MessageBox("内码与序号参数缺少或过多,请检查","ERROR", MB_ICONEXCLAMATION );}

			///////////////////////////////////////////////////////////////////////////////////////////////


			if (!berr)	//检查是否出错
			{
				////////////////-------------
				twqzs = new char[twqz_cnt][50];
				twbms = new char[twbm_cnt][50];
				twqshs= new int[twqsh_cnt];
				twwhs = new int[twwh_cnt];
				cpxs  = new int[cpx_cnt];
				areas = new char[area_cnt][50];
				roomtyps = new char[roomtyp_cnt][50];
				paxs  = new int[pax_cnt];


				//////////////////--------------
				if ( GetStr(twqzs,mBuf[1],twqz_cnt,50,',') != twqz_cnt ) { berr = true; MessageBox("台位前缀中有异常字符或数字,请检查","ERROR", MB_ICONEXCLAMATION );}
				if ( GetStr(twbms,mBuf[2],twbm_cnt,50,',') != twbm_cnt ) { berr = true; MessageBox("台位别名中有异常字符或数字,请检查","ERROR", MB_ICONEXCLAMATION );}
				if ( GetNumbers(10000,twqshs,mBuf[3],twqsh_cnt,',') != twqsh_cnt ) { berr = true; MessageBox("台位起始号中有异常字符或过大数字,请检查","ERROR", MB_ICONEXCLAMATION );}
				if ( GetNumbers(10000,twwhs,mBuf[4],twwh_cnt,',') != twwh_cnt ) { berr = true; MessageBox("台位尾号中有异常字符或过大数字,请检查","ERROR", MB_ICONEXCLAMATION );}
				if ( GetNumbers(1000,cpxs,mBuf[5],cpx_cnt,',') != cpx_cnt ) { berr = true; MessageBox("楼层号中有异常字符或过大数字,请检查","ERROR", MB_ICONEXCLAMATION );}
				if ( GetStr(areas,mBuf[6],area_cnt,50,',') != area_cnt ) { berr = true; MessageBox("区域中有异常字符或数字,请检查","ERROR", MB_ICONEXCLAMATION );}
				if ( GetStr(roomtyps,mBuf[7],roomtyp_cnt,50,',') != roomtyp_cnt ) { berr = true; MessageBox("区域中有异常字符或数字,请检查","ERROR", MB_ICONEXCLAMATION );}
				if ( GetNumbers(40,paxs,mBuf[8],pax_cnt,',') != cpx_cnt ) { berr = true; MessageBox("台位最大人数中有异常字符或过大数字,请检查","ERROR", MB_ICONEXCLAMATION );}
				if ( GetNumbers(1500,twone,mBuf[9],8,',') != 8 ) { berr = true; MessageBox("台位参数中有异常字符或过大数字,请检查","ERROR", MB_ICONEXCLAMATION );}
				if ( GetNumbers(1000,tbl,mBuf[10],4,',') != 4 ) { berr = true; MessageBox("内码与序号参数中有异常字符或过大数字,请检查","ERROR", MB_ICONEXCLAMATION );}



				if (!berr)	//检查是否出错
				{
					IBPP::Database db = IBPP::DatabaseFactory(g_szServerName,g_szDBName,g_szUserName,g_szPassword);

					db->Connect();     //连接数据库

					//db->Disconnect();

					IBPP::Transaction tr = IBPP::TransactionFactory(db);

					tr->Start();

					try{
						IBPP::Statement st = IBPP::StatementFactory(db,tr);

						int test = Add_Tables_Format(st,twqzs,twbms,twqshs,twwhs,cpxs,paxs,twqz_cnt,twone[0],twone[1],twone[2], twone[3],
													tbl[0],tbl[1],tbl[2],areas,roomtyps,twone[4],twone[5],twone[6],twone[7],bool(tbl[3]));

						if (test != 0) 
						{
							tr->CommitRetain();
							tr->Commit();

							MessageBox("台位已添加成功");
							is_run = true;
						}
						else
						{
							MessageBox("台位添加失败,起始号大于尾号,请检查","ERROR", MB_ICONEXCLAMATION );
						}

					}
					catch(IBPP::SQLException &e){
						//cerr << e.what() << endl;

						MessageBox(e.what(),"ERROR", MB_ICONEXCLAMATION ); 

						tr->Rollback();
					}
				}

				//////////////------------
				delete[] paxs;
				delete[] roomtyps;
				delete[] areas;
				delete[] cpxs;
				delete[] twwhs;
				delete[] twqshs;
				delete[] twbms;
				delete[] twqzs;
			}
		}

		for (int i= 0; i< lct;i++ ) delete[] mBuf[i];
		delete[] mBuf;


		
	}
	else MessageBox("请修改数据后再确定","WARNING", MB_ICONEXCLAMATION );

}


void Cib_tbls_addDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	is_run = false;
}
