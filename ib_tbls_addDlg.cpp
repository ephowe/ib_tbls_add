
// ib_tbls_addDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ib_tbls_add.h"
#include "ib_tbls_addDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// Cib_tbls_addDlg �Ի���




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


// Cib_tbls_addDlg ��Ϣ�������

BOOL Cib_tbls_addDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cib_tbls_addDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cib_tbls_addDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cib_tbls_addDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();

	//temp var
	char g_szDBName[100] = {'\0'};	//"F:\\Development\\Database\\ib\\data\\FOODBEV.GDB";
	//������������Է������汾������Ƕ��ʽ����Ӧ����""
	char g_szServerName[50] = {'\0'};

	//������û�����������FireBirdĬ��ֵ�����ڷ������棬�����Լ�������
	//����Ƕ��ʽ�����������FireBirdǶ��ʽ��û�м��ܹ��ܣ���
	const char* g_szUserName = "SYSDBA";
	const char* g_szPassword = "masterkey";


	//char numtmp[10]= {'\0'};
	

	if (!is_run)
	{
		bool berr = false;

		int len,lct = m_edit_in.GetLineCount();	//���������
		
		if (lct != 11) ///////
		{
			MessageBox("������д������","ERROR", MB_ICONEXCLAMATION );
			return;
		}


		/////////////////////////////////////////////
		//̨λǰ׺,��Ӧ̨λ��ʼ-β�� 2
		char (*twqzs)[50];
		int twqz_cnt =0;

		//̨λ����,��Ӧ̨λ��ʼ-β�� 3
		char (*twbms)[50];
		int twbm_cnt =0;

		//̨λ��ʼ�� 4
		int *twqshs,twqsh_cnt=0;

		//̨λβ�� 5
		int *twwhs,twwh_cnt = 0;
		
		//¥��� 6
		int *cpxs,cpx_cnt=0;

		//���� 7
		char (*areas)[50];
		int area_cnt=0;

		//̨λ���� 8
		char (*roomtyps)[50];
		int roomtyp_cnt=0;

		//̨λ������� 9
		int *paxs,pax_cnt=0;

		//̨λ��Ϣ,��ʾ����,��ʼ��,��ʼ��,�Ƿ�������ʾ,�м��,�м��,̨λ��,̨λ��,����8������ 10
		int twone[8] = {0},tw_cnt =0;

		//Ӫҵ��,̨λ����TBL,̨λ���GRAD,�Ƿ�����β��Ϊ4��̨��,����4������ 11
		int tbl[4],tbl_cnt=0;

		//��ʱָ��,���ݻ�����
		char *pb,**mBuf = new char*[lct];


		for(int i = 0;i < lct ; i++ )
		{ 
			len = m_edit_in.LineLength(m_edit_in.LineIndex(i));	//��������ַ����� ///////////////////////

			mBuf[i] = new char[len+1];		//����+1���λ���'\0'�����������
			
			m_edit_in.GetLine(i,LPTSTR(mBuf[i]),len);	//���������

			mBuf[i][len] = '\0';	//
	
		}


		///////////////////////////////////////////////////////////////////////////////

		switch(GetIPAndPath(g_szServerName,g_szDBName,mBuf[0]))
		{
		case -2:  berr = true; MessageBox("IP��ַ����ֵ����","ERROR", MB_ICONEXCLAMATION ); break;
		case -1:  berr = true; MessageBox("IP��ַ������","ERROR", MB_ICONEXCLAMATION ); break;
		//case 0: g_szServerName = "localhost"; break;
		}

		if (!berr)
		{

			//�����ַ��������������

			pb = mBuf[1];
			do{ if (*pb == ',') twqz_cnt++; }while (*pb++);

			pb = mBuf[2];
			do{ if (*pb == ',') twbm_cnt++; }while (*pb++);


			//twbm_cnt =0;

			//twqsh_cnt=0;twwh_cnt cpx_cnt

			//ͨ���ָ���,������ĸ����������Ƿ����
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
										MessageBox("��8,9�������������,����","ERROR", MB_ICONEXCLAMATION );	
									}
								}else { berr = true; MessageBox("��7,8�������������,����","ERROR", MB_ICONEXCLAMATION );}
							}else { berr = true; MessageBox("��6,7�������������,����","ERROR", MB_ICONEXCLAMATION );}				
						}else { berr = true; MessageBox("��5,6�������������,����","ERROR", MB_ICONEXCLAMATION );}
					}else { berr = true; MessageBox("��4,5�������������,����","ERROR", MB_ICONEXCLAMATION );}
				}else { berr = true; MessageBox("��3,4�������������,����","ERROR", MB_ICONEXCLAMATION );}
			}else { berr = true; MessageBox("��2,3�������������,����","ERROR", MB_ICONEXCLAMATION );}


			pb = mBuf[9];

			do{ if (*pb == ',') tw_cnt++; }while (*pb++);
		
			//���̨�Ų�����Ϊ8��,�����
			if (++tw_cnt != 8) { berr = true; MessageBox("̨λ����ȱ�ٻ����,����","ERROR", MB_ICONEXCLAMATION );}


			pb = mBuf[10];

			do{ if (*pb == ',') tbl_cnt++; }while (*pb++);

			if (++tbl_cnt != 4) { berr = true; MessageBox("��������Ų���ȱ�ٻ����,����","ERROR", MB_ICONEXCLAMATION );}

			///////////////////////////////////////////////////////////////////////////////////////////////


			if (!berr)	//����Ƿ����
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
				if ( GetStr(twqzs,mBuf[1],twqz_cnt,50,',') != twqz_cnt ) { berr = true; MessageBox("̨λǰ׺�����쳣�ַ�������,����","ERROR", MB_ICONEXCLAMATION );}
				if ( GetStr(twbms,mBuf[2],twbm_cnt,50,',') != twbm_cnt ) { berr = true; MessageBox("̨λ���������쳣�ַ�������,����","ERROR", MB_ICONEXCLAMATION );}
				if ( GetNumbers(10000,twqshs,mBuf[3],twqsh_cnt,',') != twqsh_cnt ) { berr = true; MessageBox("̨λ��ʼ�������쳣�ַ����������,����","ERROR", MB_ICONEXCLAMATION );}
				if ( GetNumbers(10000,twwhs,mBuf[4],twwh_cnt,',') != twwh_cnt ) { berr = true; MessageBox("̨λβ�������쳣�ַ����������,����","ERROR", MB_ICONEXCLAMATION );}
				if ( GetNumbers(1000,cpxs,mBuf[5],cpx_cnt,',') != cpx_cnt ) { berr = true; MessageBox("¥��������쳣�ַ����������,����","ERROR", MB_ICONEXCLAMATION );}
				if ( GetStr(areas,mBuf[6],area_cnt,50,',') != area_cnt ) { berr = true; MessageBox("���������쳣�ַ�������,����","ERROR", MB_ICONEXCLAMATION );}
				if ( GetStr(roomtyps,mBuf[7],roomtyp_cnt,50,',') != roomtyp_cnt ) { berr = true; MessageBox("���������쳣�ַ�������,����","ERROR", MB_ICONEXCLAMATION );}
				if ( GetNumbers(40,paxs,mBuf[8],pax_cnt,',') != cpx_cnt ) { berr = true; MessageBox("̨λ������������쳣�ַ����������,����","ERROR", MB_ICONEXCLAMATION );}
				if ( GetNumbers(1500,twone,mBuf[9],8,',') != 8 ) { berr = true; MessageBox("̨λ���������쳣�ַ����������,����","ERROR", MB_ICONEXCLAMATION );}
				if ( GetNumbers(1000,tbl,mBuf[10],4,',') != 4 ) { berr = true; MessageBox("��������Ų��������쳣�ַ����������,����","ERROR", MB_ICONEXCLAMATION );}



				if (!berr)	//����Ƿ����
				{
					IBPP::Database db = IBPP::DatabaseFactory(g_szServerName,g_szDBName,g_szUserName,g_szPassword);

					db->Connect();     //�������ݿ�

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

							MessageBox("̨λ����ӳɹ�");
							is_run = true;
						}
						else
						{
							MessageBox("̨λ���ʧ��,��ʼ�Ŵ���β��,����","ERROR", MB_ICONEXCLAMATION );
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
	else MessageBox("���޸����ݺ���ȷ��","WARNING", MB_ICONEXCLAMATION );

}


void Cib_tbls_addDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	is_run = false;
}
