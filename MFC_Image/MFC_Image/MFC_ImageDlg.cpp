
// MFC_ImageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_Image.h"
#include "MFC_ImageDlg.h"
#include "afxdialogex.h"

#include "windows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//全局变量
CString gReadFilePathName;
CString filename;

int height = 600;
int width = 800;
FILE *fp = NULL;
unsigned char *process_image = NULL;

//定义变量存储图片信息
BITMAPINFO *pBmpInfo;       //记录图像细节
BYTE *pBmpData;             //图像数据
BITMAPFILEHEADER bmpHeader; //文件头
BITMAPINFOHEADER bmpInfo;   //信息头
CFile bmpFile;              //记录打开文件

//幂次变换
float v = 0.6;

//打开图片标志
char open_flag = 0;



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_ImageDlg 对话框



CMFC_ImageDlg::CMFC_ImageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_IMAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_ImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_EDIT1, input_v);
//	DDX_Control(pDX, IDC_EDIT2, input_vv);
}

BEGIN_MESSAGE_MAP(CMFC_ImageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFC_ImageDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC_ImageDlg::OnBnClickedButton1)
//	ON_BN_CLICKED(IDC_COMMAND1, &CMFC_ImageDlg::OnBnClickedCommand1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC_ImageDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFC_ImageDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFC_ImageDlg::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_EDIT1, &CMFC_ImageDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMFC_ImageDlg::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CMFC_ImageDlg 消息处理程序

BOOL CMFC_ImageDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC_ImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC_ImageDlg::OnPaint()
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
HCURSOR CMFC_ImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_ImageDlg::OnBnClickedOk()
{
	//MessageBox(_T("Hello World!"));
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

//打开文件
void CMFC_ImageDlg::OnBnClickedButton1()
{

	CFileDialog fileDlg(true, _T("bmp"), _T("*.bmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("bmp Files (*.bmp)|*.bmp|All File (*.*)|*.*||"), NULL); 
	//TRUE为打开文件对话框；FALSE为保存文件对话框
	//缺省的扩展名
	//缺省显示在文件名组合框的编辑框的文件名，一般可选NULL
	//对话框风格，一般为OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 即隐藏只读选项和覆盖已有文件前提示。
	//文件筛选类型，它指明可供选择的文件类型和相应的扩展名。
	//父窗口指针，一般可选NULL.

	if (fileDlg.DoModal() == IDOK) //弹出对话框 
	{
		gReadFilePathName = fileDlg.GetPathName();//得到完整的文件名和目录名拓展名 
		filename = fileDlg.GetFileName(); 
	}
	//打开对话框获取图像信息
	CString BmpName = gReadFilePathName;     //获取文件路径名   如D:\pic\abc.bmp
	CString EntName = fileDlg.GetFileExt();      //获取文件扩展名
	EntName.MakeLower();                     //将文件扩展名转换为一个小写字符
	if (EntName.Compare(_T("bmp")) == 0)
	{
		//定义变量存储图片信息
//		BITMAPINFO *pBmpInfo;       //记录图像细节
//		BYTE *pBmpData;             //图像数据
//		BITMAPFILEHEADER bmpHeader; //文件头
//		BITMAPINFOHEADER bmpInfo;   //信息头
//		CFile bmpFile;              //记录打开文件
									//以只读的方式打开文件 读取bmp图片各部分 bmp文件头 信息 数据
		if (!bmpFile.Open(BmpName, CFile::modeRead | CFile::typeBinary))
			return;
		if (bmpFile.Read(&bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
			return;
		if (bmpFile.Read(&bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
			return;
		pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];
		//为图像数据申请空间
		memcpy(pBmpInfo, &bmpInfo, sizeof(BITMAPINFOHEADER));
		DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
		pBmpData = (BYTE*)new char[dataBytes];
		bmpFile.Read(pBmpData, dataBytes);
		bmpFile.Close();
		//显示图像
		CWnd *pWnd = GetDlgItem(IDC_STATIC); //获得pictrue控件窗口的句柄
		CRect rect;
		pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域
		CDC *pDC = pWnd->GetDC(); //获得pictrue控件的DC
		pDC->SetStretchBltMode(COLORONCOLOR);
		StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0,
			bmpInfo.biWidth, bmpInfo.biHeight, pBmpData, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
		
		//打开文件标志
		open_flag = 1;
		fp = fopen("output.raw", "wb");
		for (int i = 0; i < 800*600*3; i++)
		{
			fwrite(&pBmpData[i], 1, 1, fp);
		}
		fclose(fp);
	}
}


void CMFC_ImageDlg::OnBnClickedCommand1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFC_ImageDlg::OnBnClickedButton2()
{
	if (open_flag == 1)
	{
		process_image = (unsigned char*)malloc(bmpInfo.biWidth * bmpInfo.biHeight * 3 * sizeof(unsigned char));
		for (int i = 0; i < bmpInfo.biWidth * bmpInfo.biHeight * 3; i++)
		{
			process_image[i] = 255 - pBmpData[i];
		}

		CWnd *pWnd = GetDlgItem(IDOK); //获得pictrue控件窗口的句柄
		CRect rect;
		pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域
		CDC *pDC = pWnd->GetDC(); //获得pictrue控件的DC
		pDC->SetStretchBltMode(COLORONCOLOR);
		StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0,
			bmpInfo.biWidth, bmpInfo.biHeight, process_image, pBmpInfo, DIB_RGB_COLORS, SRCCOPY); \
		
		free(process_image);
	}
	// TODO: 在此添加控件通知处理程序代码
}

//直方图均衡化
void CMFC_ImageDlg::OnBnClickedButton3()
{
	int hist[256];
	float  fpHist[256];
	float eqHistTemp[256];
	int eqHist[256];
	int size = height *width;
	int i;
	if (open_flag == 1)
	{
		process_image = (unsigned char*)malloc(bmpInfo.biWidth * bmpInfo.biHeight * 3 * sizeof(unsigned char));
		//1st
		memset(&hist, 0x00, sizeof(int) * 256);
		memset(&fpHist, 0x00, sizeof(float) * 256);
		memset(&eqHistTemp, 0x00, sizeof(float) * 256);
		
		for (i = 0; i < bmpInfo.biWidth * bmpInfo.biHeight *3; i+=3) //计算差分矩阵直方图  直方图  统计每个灰度级像素点的个数
		{
				unsigned char GrayIndex = pBmpData[i];
				hist[GrayIndex] ++;
		}
		for (i = 0; i< 256; i++)   // 计算灰度分布密度
		{
			fpHist[i] = (float)hist[i] / (float)size;
		}
		for (i = 0; i< 256; i++)   // 计算累计直方图分布
		{
			if (i == 0)
			{
				eqHistTemp[i] = fpHist[i];
			}
			else
			{
				eqHistTemp[i] = eqHistTemp[i - 1] + fpHist[i];
			}
		}

		//累计分布取整，保存计算出来的灰度映射关系
		for (i = 0; i< 256; i++)
		{
			eqHist[i] = (int)(255.0 * eqHistTemp[i] + 0.5);
		}
		for (i = 0; i < bmpInfo.biWidth * bmpInfo.biHeight *3; i+=3) //进行灰度映射 均衡化
		{
				unsigned char GrayIndex = pBmpData[i];
				process_image[i] = eqHist[GrayIndex];
		}
		//2st
		memset(&hist, 0x00, sizeof(int) * 256);
		memset(&fpHist, 0x00, sizeof(float) * 256);
		memset(&eqHistTemp, 0x00, sizeof(float) * 256);

		for (i = 1; i < bmpInfo.biWidth * bmpInfo.biHeight * 3; i += 3) //计算差分矩阵直方图  直方图  统计每个灰度级像素点的个数
		{
			unsigned char GrayIndex = pBmpData[i];
			hist[GrayIndex] ++;
		}
		for (i = 0; i< 256; i++)   // 计算灰度分布密度
		{
			fpHist[i] = (float)hist[i] / (float)size;
		}
		for (i = 0; i< 256; i++)   // 计算累计直方图分布
		{
			if (i == 0)
			{
				eqHistTemp[i] = fpHist[i];
			}
			else
			{
				eqHistTemp[i] = eqHistTemp[i - 1] + fpHist[i];
			}
		}

		//累计分布取整，保存计算出来的灰度映射关系
		for (i = 0; i< 256; i++)
		{
			eqHist[i] = (int)(255.0 * eqHistTemp[i] + 0.5);
		}
		for (i = 1; i < bmpInfo.biWidth * bmpInfo.biHeight * 3; i += 3) //进行灰度映射 均衡化
		{
			unsigned char GrayIndex = pBmpData[i];
			process_image[i] = eqHist[GrayIndex];
		}
		//3st
		memset(&hist, 0x00, sizeof(int) * 256);
		memset(&fpHist, 0x00, sizeof(float) * 256);
		memset(&eqHistTemp, 0x00, sizeof(float) * 256);

		for (i = 2; i < bmpInfo.biWidth * bmpInfo.biHeight * 3; i += 3) //计算差分矩阵直方图  直方图  统计每个灰度级像素点的个数
		{
			unsigned char GrayIndex = pBmpData[i];
			hist[GrayIndex] ++;
		}
		for (i = 0; i< 256; i++)   // 计算灰度分布密度
		{
			fpHist[i] = (float)hist[i] / (float)size;
		}
		for (i = 0; i< 256; i++)   // 计算累计直方图分布
		{
			if (i == 0)
			{
				eqHistTemp[i] = fpHist[i];
			}
			else
			{
				eqHistTemp[i] = eqHistTemp[i - 1] + fpHist[i];
			}
		}

		//累计分布取整，保存计算出来的灰度映射关系
		for (i = 0; i< 256; i++)
		{
			eqHist[i] = (int)(255.0 * eqHistTemp[i] + 0.5);
		}
		for (i = 2; i < bmpInfo.biWidth * bmpInfo.biHeight * 3; i += 3) //进行灰度映射 均衡化
		{
			unsigned char GrayIndex = pBmpData[i];
			process_image[i] = eqHist[GrayIndex];
		}



		CWnd *pWnd = GetDlgItem(IDOK); //获得pictrue控件窗口的句柄
		CRect rect;
		pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域
		CDC *pDC = pWnd->GetDC(); //获得pictrue控件的DC
		pDC->SetStretchBltMode(COLORONCOLOR);
		StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0,
			bmpInfo.biWidth, bmpInfo.biHeight, process_image, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
		free(process_image);
	}
	// TODO: 在此添加控件通知处理程序代码
}

//幂次变换
void CMFC_ImageDlg::OnBnClickedButton4()
{
	CString num1;
	char num[256] = { '\0' };
	GetDlgItemText(IDC_EDIT2, num1);//获取输入的浮点数1
	v = _ttoi(num1);//将字符串转换为浮点数并求和
	//v = atoi(num1);
	if (open_flag == 1)
	{
		process_image = (unsigned char*)malloc(height*width * 3 * sizeof(unsigned char));
		for (int i = 0; i < bmpInfo.biWidth * bmpInfo.biHeight * 3; i++)
		{
			process_image[i] = pow(pBmpData[i] / 255.0, v / 10) * 255;
		}


		CWnd *pWnd = GetDlgItem(IDOK); //获得pictrue控件窗口的句柄
		CRect rect;
		pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域
		CDC *pDC = pWnd->GetDC(); //获得pictrue控件的DC
		pDC->SetStretchBltMode(COLORONCOLOR);
		StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0,
			bmpInfo.biWidth, bmpInfo.biHeight, process_image, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
		free(process_image);
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CMFC_ImageDlg::OnEnChangeEdit1()
{
		//v = atof(input_v);

	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFC_ImageDlg::OnEnChangeEdit2()
{
	//v = atof(input_vv);
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
