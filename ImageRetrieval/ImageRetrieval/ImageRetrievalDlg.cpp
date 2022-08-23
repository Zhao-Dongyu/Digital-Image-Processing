
// ImageRetrievalDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageRetrieval.h"
#include "ImageRetrievalDlg.h"
#include "afxdialogex.h"
#include "picture.h"
#include "math.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PI 3.1415926

bool open_flag;
bool library_flag;
bool color;//各种颜色方法是否使用过标志位
int	counts;//检索库图像计数器
int tempi;//临时的检索库图像计数器

CString* temp[100];//检索库中图像路径
CString temp_1[100];//临时存放检索库中图像路径

CString strfile;//待检索图像的路径
CString m_strPath;//检索库路径	

double feature_color[3][12];//待检索图像的颜色特征
double feature_color_1[3][12]; //当前分析图像的颜色特征

picture image;//基于颜色特征
picture image_color_temp;
picture image_color_1;
picture image_color_2; 
picture image_color_3;
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


// CImageRetrievalDlg 对话框



CImageRetrievalDlg::CImageRetrievalDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IMAGERETRIEVAL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageRetrievalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImageRetrievalDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CImageRetrievalDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_OPEN, &CImageRetrievalDlg::OnBnClickedOpen)
//	ON_BN_CLICKED(IDC_BUTTON1, &CImageRetrievalDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_PATH, &CImageRetrievalDlg::OnBnClickedPath)
	ON_BN_CLICKED(IDC_BUTTON2, &CImageRetrievalDlg::OnBnClickedButton2)
	ON_STN_CLICKED(IDC_VIEW2, &CImageRetrievalDlg::OnStnClickedView2)
	ON_BN_CLICKED(IDC_BUTTON1, &CImageRetrievalDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CImageRetrievalDlg 消息处理程序

BOOL CImageRetrievalDlg::OnInitDialog()
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

void CImageRetrievalDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CImageRetrievalDlg::OnPaint()
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
HCURSOR CImageRetrievalDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CImageRetrievalDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CImageRetrievalDlg::OnBnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码	
	CFileDialog fileOpenDlg(TRUE, _T("bmp"), _T("*.bmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("bmp Files (*.bmp)|*.bmp|All File (*.*)|*.*||"), NULL);
	if (fileOpenDlg.DoModal() != IDOK)   return;
	POSITION pos = fileOpenDlg.GetStartPosition();	//对于选择了多个文件的情况得到第一个文件位置
	strfile = fileOpenDlg.GetNextPathName(pos);		//得到待检索图像的路径

	CString EntName = fileOpenDlg.GetFileExt();     //获取文件扩展名
	EntName.MakeLower();							//将文件扩展名转换为一个小写字符
	if (EntName.Compare(_T("bmp")) == 0)
	{
		open_flag = true;							//标志位设置为true，表示待检索图像已设置
		ShowPic(strfile, IDC_VIEW);					//显示待检索图像
	}
	else
	{
		AfxMessageBox(_T("请选择.bmp格式图片"), MB_ICONINFORMATION | MB_OK);
	}
}
/************************************************************************************
显示待检索图像
pathfile为待显示的文件路径，idc为图像显示控件的ID号
************************************************************************************/
void CImageRetrievalDlg::ShowPic(CString pathfile, int idc)
{
	//定义变量存储图片信息
	BITMAPINFO *pBmpInfo;       //记录图像细节
	BYTE *pBmpData;             //图像数据
	BITMAPFILEHEADER bmpHeader; //文件头
	BITMAPINFOHEADER bmpInfo;   //信息头
	CFile bmpFile;              //记录打开文件

	if (!bmpFile.Open(pathfile, CFile::modeRead | CFile::typeBinary))
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
	CWnd *pWnd = GetDlgItem(idc); //获得pictrue控件窗口的句柄
	CRect rect;
	pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域
	CDC *pDC = pWnd->GetDC(); //获得pictrue控件的DC
	pDC->SetStretchBltMode(COLORONCOLOR);
	StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0,
		bmpInfo.biWidth, bmpInfo.biHeight, pBmpData, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
}

void CImageRetrievalDlg::OnBnClickedPath()
{
	// TODO: 在此添加控件通知处理程序代码
	//打开通用对话框，BROWSEINFO结构中包含有用户选中目录的重要信息
	BROWSEINFO browse;
	ZeroMemory(&browse, sizeof(browse));//fills a block of memory with zeros.
	browse.hwndOwner = NULL;
	browse.pszDisplayName = m_strPath.GetBuffer(MAX_PATH);
	browse.lpszTitle = _T("请选择一个图像目录");
	//SHBrowseForFolder函数返回一个ITEMIDLIST结构的指针，包含了用户选择文件夹的信息
	LPITEMIDLIST lpItem = SHBrowseForFolder(&browse);
	if (lpItem == NULL) return;
	m_strPath.ReleaseBuffer();
	//SHGetPathFromIDList把项目标志符列表转换为文档系统路径
	if (SHGetPathFromIDList(lpItem, m_strPath.GetBuffer(MAX_PATH)) == false) return;
	m_strPath.ReleaseBuffer();
	library_flag = true; //标志位设置为true，表示待检索图像已设置
	AfxMessageBox(_T("您选择的目录为:") + m_strPath, MB_ICONINFORMATION | MB_OK);
	//扫描检索库，得到图像目录下文件的路径
	CString tempath;
	CString temps;
	tempath = m_strPath;
	tempath.TrimRight(); tempath.TrimLeft(); //去除前后多余
	CString strfilepath = tempath;
	//tempi = 0;
	counts = 0;//计数器清零
			   //检索库中图像个数放入counts中，其路径放入temp[100]中
	StartDir(strfilepath);
	temps.Format(_T("该目录下共有%d幅图像!"), counts);
	AfxMessageBox(temps, MB_ICONINFORMATION | MB_OK);
}
/***********************************************************************************
扫描检索库中的图像个数
**********************************************************************************/
void CImageRetrievalDlg::StartDir(const CString &strfile1)
{
	BOOL yesno;
	CFileFind find;
	char tempFileFind[200];
	sprintf_s(tempFileFind, "%s\\*.*", strfile1);
	//printf("%s\n", tempFileFind);
	RunDir(strfile1);//在当前目录中查找图像，不搜索子目录
	yesno = (BOOL)find.FindFile(strfile1+_T("\\*.*"));
	//查找当前目录下子目录中的文件
	while (yesno)
	{
		yesno = find.FindNextFile();
		if (find.IsDots() != TRUE)//过滤缺省目录
		{
			//char foundFileName[200];
			TCHAR foundFileName[200];//临时存储查找到的图像名
			wcscpy(foundFileName, find.GetFileName().GetBuffer(200));//获取图像名
			//strcpy_s(foundFileName, find.GetFileName().GetBuffer(200));
			if ((find.IsDirectory() == TRUE)) //判断是否为目录
			{
				//char tempDir[200];
				//sprintf_s(tempDir, "%s\\%s", strfile1, foundFileName);//获得子目录路径
				StartDir(strfile1+_T("\\")+ foundFileName); 	// 递归调用，查找子目录中图像
			}
		}
	}
	find.Close();
	return;
}
/***********************************************************************************
扫描当前目录中的图像个数
**********************************************************************************/
void CImageRetrievalDlg::RunDir(const CString &strfile2)
{
	BOOL IsFinded;
	CFileFind find;
	//char tempFileFind[200];
	//sprintf_s(tempFileFind, "%s\\*.bmp", strfile2);
	//yesno = find.FindFile(CString(tempFileFind)); //在当前目录下查找BMP文件
	IsFinded = find.FindFile(strfile2+_T("\\*.bmp")); //在当前目录下查找BMP文件
	while (IsFinded)
	{
		IsFinded = find.FindNextFile();

		TCHAR foundFileName[200];//临时存储查找到的图像名
		wcscpy(foundFileName, find.GetFileName().GetBuffer(200));//获取图像名
		//strcpy_s(foundFileName, find.GetFileName().GetBuffer(200));//获取图像名
		if (!find.IsDots()) //过滤缺省目录
		{
			//char tempFileName[200];
			//sprintf_s(tempFileName, "%s\\%s", strfile2, foundFileName);
			CString strfilepath1;

			//strfilepath1.Format(_T("%s"), tempFileName);//获取图像完整路径
			
			strfilepath1 = strfile2+_T("\\")+ foundFileName;

			counts++;
			temp[tempi] = new CString(strfilepath1);//保存图像完整路径
			tempi++;
		}
	}
	find.Close();
	return;
}




void CImageRetrievalDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//检查是否设置了待检索图像和检索库路径
	if (open_flag == false)
	{
		AfxMessageBox(_T("请先设置待检索图像"));
		return;
	}
	if (library_flag == false)
	{
		AfxMessageBox(_T("请设置检索库路径"));
		return;
	}
	general(strfile, 1);//提取待检索图像颜色直方图
	Color_SeekImage();//基于颜色特征的相似度计算函数
}
/***********************************************************************************
计算颜色直方图
pathfile为图像的路径，mode为模式状态位，为1时，表示计算的是待检索图像，
为2时，表示计算的是检索库中的图像
************************************************************************************/
void CImageRetrievalDlg::general(CString pathfile, int mode)
{
	CBitmap hbmp;
	HBITMAP hbitmap;
	//装载资源
	hbitmap = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), pathfile, IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	hbmp.Attach(hbitmap);
	//获取图像格式
	BITMAP bm;
	hbmp.GetBitmap(&bm);
	//创建临时的内存DC对象
	CDC dcMem;
	dcMem.CreateCompatibleDC(GetDC());
	dcMem.SelectObject(hbmp);
	int width = bm.bmWidth;
	int height = bm.bmHeight;
	int totalnum = height *width;
	//初始化
	long m_graph[3][12];
	for (int i = 0; i<3; i++)
		for (int j = 0; j<12; j++)
		{
			m_graph[i][j] = 0;
			if (mode == 1)
				feature_color[i][j] = 0.0;
			else
				feature_color_1[i][j] = 0.0;
		}
	COLORREF color;
	double h = 0, s = 0, v = 0;
	//计算颜色直方图
	for (long y = 0; y<height; y++)
	{
		for (long x = 0; x<width; x++)
		{
			color = dcMem.GetPixel(x, y);
			//颜色空间转换
			RGBToHSV(GetRValue(color), GetGValue(color), GetBValue(color), &h, &s, &v);
			int result_h = (int)(6 * h / PI);
			if (result_h == 12)
				m_graph[0][11]++;
			else
				m_graph[0][result_h]++;
			int result_s = (int)(s * 12);
			if (result_s == 12)
				m_graph[1][11]++;
			else
				m_graph[1][result_s]++;
			int result_v = (int)(v * 12);
			if (result_v == 12)
				m_graph[2][11]++;
			else
				m_graph[2][result_v]++;
		}
	}
	//保存颜色直方图
	if (mode == 1)
	{
		for (int i = 0; i<3; i++)
			for (int j = 0; j<12; j++)
				feature_color[i][j] = ((float)m_graph[i][j]) / ((float)totalnum);
	}
	else
	{
		for (int i = 0; i<3; i++)
			for (int j = 0; j<12; j++)
				feature_color_1[i][j] = ((float)m_graph[i][j]) / ((float)totalnum);
	}
	//AfxMessageBox(_T("颜色直方图保存完成"));
}

/*******************************************************************************
RGB空间至HSV空间的转换
*********************************************************************************/
void CImageRetrievalDlg::RGBToHSV(int r, int g, int b, double *h, double *s, double *v)
{
	*h = acos((r - g + r - b) / (2.0*sqrtf((float)(r - g)*(r - g) + (float)(r - b)*(g - b))));
	if (b>g)
		*h = 2 * PI - *h;
	*s = (mymax(r, g, b) - mymin(r, g, b)) / (float)mymax(r, g, b);
	*v = mymax(r, g, b) / 255.0;
}

int CImageRetrievalDlg::mymax(int a, int b, int c)//寻找最大
{
	int m;
	if (a>b)
		m = a;
	else
		m = b;
	if (m<c)
		m = c;
	return m;
}

int CImageRetrievalDlg::mymin(int a, int b, int c)//寻找最小
{
	int m;
	if (a<b)
		m = a;
	else
		m = b;
	if (m>c)
		m = c;
	return m;
}
/**************************************************************************************
基于颜色特征的相似度计算函数
***************************************************************************************/
void CImageRetrievalDlg::Color_SeekImage()
{
	for (int count = 0; count<counts; count++)
		temp_1[count] = *temp[count];
	if (image_color_1.strfile_old == strfile&&image_color_1.m_strPath_old == m_strPath)
		color = 1;//此检索库下的此检索图像已经用此方法计算过
	else
		color = 0;
	for (int pic = 0; pic<counts; pic++)//逐个分析检索库中图像
	{
		if (color == 0)
		{
			general(temp_1[pic], 2);//提取检索的第N幅图的颜色直方图

			double dis = 0;//第N幅图与待检索图像的距离
			double dis_temp = 0;
			//计算正在检索的第N幅图与待检索图像的距离
			for (int i = 0; i<3; i++)
			{
				for (int j = 0; j<12; j++)
					dis_temp += (feature_color_1[i][j] - feature_color[i][j])*(feature_color_1[i][j] - feature_color[i][j]);
				dis += sqrt((double)dis_temp);
				dis_temp = 0;
			}
			image_color_temp.tp[pic] = temp_1[pic];//保存第N幅图路径
			image_color_temp.num[pic] = dis;//保存第N幅图与待检索图像的距离
		}
		ShowPic(temp_1[pic], IDC_VIEW2);
	}

		if (color == 0)//若本方法为第一次计算，则保存相似度计算结果
		{
			image_color_1 = image_color_temp;
			sort();
		}
		else//若本方法已经计算过，则读取相似度计算结果
		{
			image_color_temp = image_color_1;
			sort();
		}
		//检索过的待检索图像及检索库路径更新
		image_color_1.m_strPath_old = image_color_temp.m_strPath_old = m_strPath;
		image_color_1.strfile_old = image_color_temp.strfile_old = strfile;

}


/*******************************************************************************
结果处理及显示
*********************************************************************************/
void CImageRetrievalDlg::sort()
{
	int  picnum = 5001;//图像显示控件的ID号
		CString tp;//图像路径
		double  num;//图像与待检索图像的距离
					//图像相似度排序
		for (int i = 0; i<counts; i++)
		{
			for (int j = i + 1; j<counts; j++)
			{
				if (image_color_temp.num[i]>image_color_temp.num[j])
				{
					tp = image_color_temp.tp[i];
					num = image_color_temp.num[i];
					image_color_temp.tp[i] = image_color_temp.tp[j];
					image_color_temp.num[i] = image_color_temp.num[j];
					image_color_temp.tp[j] = tp;
					image_color_temp.num[j] = num;
				}
			}
		}
		//显示前十个相似度最高的图像
		for (int i = 0; i<10 && picnum <= 5009; i++)
		{
			ShowPic(image_color_temp.tp[i], picnum);
			picnum++;
		}
}



void CImageRetrievalDlg::OnStnClickedView2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CImageRetrievalDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}
