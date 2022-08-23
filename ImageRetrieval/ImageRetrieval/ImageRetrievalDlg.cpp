
// ImageRetrievalDlg.cpp : ʵ���ļ�
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
bool color;//������ɫ�����Ƿ�ʹ�ù���־λ
int	counts;//������ͼ�������
int tempi;//��ʱ�ļ�����ͼ�������

CString* temp[100];//��������ͼ��·��
CString temp_1[100];//��ʱ��ż�������ͼ��·��

CString strfile;//������ͼ���·��
CString m_strPath;//������·��	

double feature_color[3][12];//������ͼ�����ɫ����
double feature_color_1[3][12]; //��ǰ����ͼ�����ɫ����

picture image;//������ɫ����
picture image_color_temp;
picture image_color_1;
picture image_color_2; 
picture image_color_3;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CImageRetrievalDlg �Ի���



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


// CImageRetrievalDlg ��Ϣ�������

BOOL CImageRetrievalDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CImageRetrievalDlg::OnPaint()
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
HCURSOR CImageRetrievalDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CImageRetrievalDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CImageRetrievalDlg::OnBnClickedOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	CFileDialog fileOpenDlg(TRUE, _T("bmp"), _T("*.bmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("bmp Files (*.bmp)|*.bmp|All File (*.*)|*.*||"), NULL);
	if (fileOpenDlg.DoModal() != IDOK)   return;
	POSITION pos = fileOpenDlg.GetStartPosition();	//����ѡ���˶���ļ�������õ���һ���ļ�λ��
	strfile = fileOpenDlg.GetNextPathName(pos);		//�õ�������ͼ���·��

	CString EntName = fileOpenDlg.GetFileExt();     //��ȡ�ļ���չ��
	EntName.MakeLower();							//���ļ���չ��ת��Ϊһ��Сд�ַ�
	if (EntName.Compare(_T("bmp")) == 0)
	{
		open_flag = true;							//��־λ����Ϊtrue����ʾ������ͼ��������
		ShowPic(strfile, IDC_VIEW);					//��ʾ������ͼ��
	}
	else
	{
		AfxMessageBox(_T("��ѡ��.bmp��ʽͼƬ"), MB_ICONINFORMATION | MB_OK);
	}
}
/************************************************************************************
��ʾ������ͼ��
pathfileΪ����ʾ���ļ�·����idcΪͼ����ʾ�ؼ���ID��
************************************************************************************/
void CImageRetrievalDlg::ShowPic(CString pathfile, int idc)
{
	//��������洢ͼƬ��Ϣ
	BITMAPINFO *pBmpInfo;       //��¼ͼ��ϸ��
	BYTE *pBmpData;             //ͼ������
	BITMAPFILEHEADER bmpHeader; //�ļ�ͷ
	BITMAPINFOHEADER bmpInfo;   //��Ϣͷ
	CFile bmpFile;              //��¼���ļ�

	if (!bmpFile.Open(pathfile, CFile::modeRead | CFile::typeBinary))
		return;
	if (bmpFile.Read(&bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
		return;
	if (bmpFile.Read(&bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
		return;
	pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];
	//Ϊͼ����������ռ�
	memcpy(pBmpInfo, &bmpInfo, sizeof(BITMAPINFOHEADER));
	DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
	pBmpData = (BYTE*)new char[dataBytes];
	bmpFile.Read(pBmpData, dataBytes);
	bmpFile.Close();
	//��ʾͼ��
	CWnd *pWnd = GetDlgItem(idc); //���pictrue�ؼ����ڵľ��
	CRect rect;
	pWnd->GetClientRect(&rect); //���pictrue�ؼ����ڵľ�������
	CDC *pDC = pWnd->GetDC(); //���pictrue�ؼ���DC
	pDC->SetStretchBltMode(COLORONCOLOR);
	StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0,
		bmpInfo.biWidth, bmpInfo.biHeight, pBmpData, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
}

void CImageRetrievalDlg::OnBnClickedPath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ͨ�öԻ���BROWSEINFO�ṹ�а������û�ѡ��Ŀ¼����Ҫ��Ϣ
	BROWSEINFO browse;
	ZeroMemory(&browse, sizeof(browse));//fills a block of memory with zeros.
	browse.hwndOwner = NULL;
	browse.pszDisplayName = m_strPath.GetBuffer(MAX_PATH);
	browse.lpszTitle = _T("��ѡ��һ��ͼ��Ŀ¼");
	//SHBrowseForFolder��������һ��ITEMIDLIST�ṹ��ָ�룬�������û�ѡ���ļ��е���Ϣ
	LPITEMIDLIST lpItem = SHBrowseForFolder(&browse);
	if (lpItem == NULL) return;
	m_strPath.ReleaseBuffer();
	//SHGetPathFromIDList����Ŀ��־���б�ת��Ϊ�ĵ�ϵͳ·��
	if (SHGetPathFromIDList(lpItem, m_strPath.GetBuffer(MAX_PATH)) == false) return;
	m_strPath.ReleaseBuffer();
	library_flag = true; //��־λ����Ϊtrue����ʾ������ͼ��������
	AfxMessageBox(_T("��ѡ���Ŀ¼Ϊ:") + m_strPath, MB_ICONINFORMATION | MB_OK);
	//ɨ������⣬�õ�ͼ��Ŀ¼���ļ���·��
	CString tempath;
	CString temps;
	tempath = m_strPath;
	tempath.TrimRight(); tempath.TrimLeft(); //ȥ��ǰ�����
	CString strfilepath = tempath;
	//tempi = 0;
	counts = 0;//����������
			   //��������ͼ���������counts�У���·������temp[100]��
	StartDir(strfilepath);
	temps.Format(_T("��Ŀ¼�¹���%d��ͼ��!"), counts);
	AfxMessageBox(temps, MB_ICONINFORMATION | MB_OK);
}
/***********************************************************************************
ɨ��������е�ͼ�����
**********************************************************************************/
void CImageRetrievalDlg::StartDir(const CString &strfile1)
{
	BOOL yesno;
	CFileFind find;
	char tempFileFind[200];
	sprintf_s(tempFileFind, "%s\\*.*", strfile1);
	//printf("%s\n", tempFileFind);
	RunDir(strfile1);//�ڵ�ǰĿ¼�в���ͼ�񣬲�������Ŀ¼
	yesno = (BOOL)find.FindFile(strfile1+_T("\\*.*"));
	//���ҵ�ǰĿ¼����Ŀ¼�е��ļ�
	while (yesno)
	{
		yesno = find.FindNextFile();
		if (find.IsDots() != TRUE)//����ȱʡĿ¼
		{
			//char foundFileName[200];
			TCHAR foundFileName[200];//��ʱ�洢���ҵ���ͼ����
			wcscpy(foundFileName, find.GetFileName().GetBuffer(200));//��ȡͼ����
			//strcpy_s(foundFileName, find.GetFileName().GetBuffer(200));
			if ((find.IsDirectory() == TRUE)) //�ж��Ƿ�ΪĿ¼
			{
				//char tempDir[200];
				//sprintf_s(tempDir, "%s\\%s", strfile1, foundFileName);//�����Ŀ¼·��
				StartDir(strfile1+_T("\\")+ foundFileName); 	// �ݹ���ã�������Ŀ¼��ͼ��
			}
		}
	}
	find.Close();
	return;
}
/***********************************************************************************
ɨ�赱ǰĿ¼�е�ͼ�����
**********************************************************************************/
void CImageRetrievalDlg::RunDir(const CString &strfile2)
{
	BOOL IsFinded;
	CFileFind find;
	//char tempFileFind[200];
	//sprintf_s(tempFileFind, "%s\\*.bmp", strfile2);
	//yesno = find.FindFile(CString(tempFileFind)); //�ڵ�ǰĿ¼�²���BMP�ļ�
	IsFinded = find.FindFile(strfile2+_T("\\*.bmp")); //�ڵ�ǰĿ¼�²���BMP�ļ�
	while (IsFinded)
	{
		IsFinded = find.FindNextFile();

		TCHAR foundFileName[200];//��ʱ�洢���ҵ���ͼ����
		wcscpy(foundFileName, find.GetFileName().GetBuffer(200));//��ȡͼ����
		//strcpy_s(foundFileName, find.GetFileName().GetBuffer(200));//��ȡͼ����
		if (!find.IsDots()) //����ȱʡĿ¼
		{
			//char tempFileName[200];
			//sprintf_s(tempFileName, "%s\\%s", strfile2, foundFileName);
			CString strfilepath1;

			//strfilepath1.Format(_T("%s"), tempFileName);//��ȡͼ������·��
			
			strfilepath1 = strfile2+_T("\\")+ foundFileName;

			counts++;
			temp[tempi] = new CString(strfilepath1);//����ͼ������·��
			tempi++;
		}
	}
	find.Close();
	return;
}




void CImageRetrievalDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����Ƿ������˴�����ͼ��ͼ�����·��
	if (open_flag == false)
	{
		AfxMessageBox(_T("�������ô�����ͼ��"));
		return;
	}
	if (library_flag == false)
	{
		AfxMessageBox(_T("�����ü�����·��"));
		return;
	}
	general(strfile, 1);//��ȡ������ͼ����ɫֱ��ͼ
	Color_SeekImage();//������ɫ���������ƶȼ��㺯��
}
/***********************************************************************************
������ɫֱ��ͼ
pathfileΪͼ���·����modeΪģʽ״̬λ��Ϊ1ʱ����ʾ������Ǵ�����ͼ��
Ϊ2ʱ����ʾ������Ǽ������е�ͼ��
************************************************************************************/
void CImageRetrievalDlg::general(CString pathfile, int mode)
{
	CBitmap hbmp;
	HBITMAP hbitmap;
	//װ����Դ
	hbitmap = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), pathfile, IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	hbmp.Attach(hbitmap);
	//��ȡͼ���ʽ
	BITMAP bm;
	hbmp.GetBitmap(&bm);
	//������ʱ���ڴ�DC����
	CDC dcMem;
	dcMem.CreateCompatibleDC(GetDC());
	dcMem.SelectObject(hbmp);
	int width = bm.bmWidth;
	int height = bm.bmHeight;
	int totalnum = height *width;
	//��ʼ��
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
	//������ɫֱ��ͼ
	for (long y = 0; y<height; y++)
	{
		for (long x = 0; x<width; x++)
		{
			color = dcMem.GetPixel(x, y);
			//��ɫ�ռ�ת��
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
	//������ɫֱ��ͼ
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
	//AfxMessageBox(_T("��ɫֱ��ͼ�������"));
}

/*******************************************************************************
RGB�ռ���HSV�ռ��ת��
*********************************************************************************/
void CImageRetrievalDlg::RGBToHSV(int r, int g, int b, double *h, double *s, double *v)
{
	*h = acos((r - g + r - b) / (2.0*sqrtf((float)(r - g)*(r - g) + (float)(r - b)*(g - b))));
	if (b>g)
		*h = 2 * PI - *h;
	*s = (mymax(r, g, b) - mymin(r, g, b)) / (float)mymax(r, g, b);
	*v = mymax(r, g, b) / 255.0;
}

int CImageRetrievalDlg::mymax(int a, int b, int c)//Ѱ�����
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

int CImageRetrievalDlg::mymin(int a, int b, int c)//Ѱ����С
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
������ɫ���������ƶȼ��㺯��
***************************************************************************************/
void CImageRetrievalDlg::Color_SeekImage()
{
	for (int count = 0; count<counts; count++)
		temp_1[count] = *temp[count];
	if (image_color_1.strfile_old == strfile&&image_color_1.m_strPath_old == m_strPath)
		color = 1;//�˼������µĴ˼���ͼ���Ѿ��ô˷��������
	else
		color = 0;
	for (int pic = 0; pic<counts; pic++)//���������������ͼ��
	{
		if (color == 0)
		{
			general(temp_1[pic], 2);//��ȡ�����ĵ�N��ͼ����ɫֱ��ͼ

			double dis = 0;//��N��ͼ�������ͼ��ľ���
			double dis_temp = 0;
			//�������ڼ����ĵ�N��ͼ�������ͼ��ľ���
			for (int i = 0; i<3; i++)
			{
				for (int j = 0; j<12; j++)
					dis_temp += (feature_color_1[i][j] - feature_color[i][j])*(feature_color_1[i][j] - feature_color[i][j]);
				dis += sqrt((double)dis_temp);
				dis_temp = 0;
			}
			image_color_temp.tp[pic] = temp_1[pic];//�����N��ͼ·��
			image_color_temp.num[pic] = dis;//�����N��ͼ�������ͼ��ľ���
		}
		ShowPic(temp_1[pic], IDC_VIEW2);
	}

		if (color == 0)//��������Ϊ��һ�μ��㣬�򱣴����ƶȼ�����
		{
			image_color_1 = image_color_temp;
			sort();
		}
		else//���������Ѿ�����������ȡ���ƶȼ�����
		{
			image_color_temp = image_color_1;
			sort();
		}
		//�������Ĵ�����ͼ�񼰼�����·������
		image_color_1.m_strPath_old = image_color_temp.m_strPath_old = m_strPath;
		image_color_1.strfile_old = image_color_temp.strfile_old = strfile;

}


/*******************************************************************************
���������ʾ
*********************************************************************************/
void CImageRetrievalDlg::sort()
{
	int  picnum = 5001;//ͼ����ʾ�ؼ���ID��
		CString tp;//ͼ��·��
		double  num;//ͼ���������ͼ��ľ���
					//ͼ�����ƶ�����
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
		//��ʾǰʮ�����ƶ���ߵ�ͼ��
		for (int i = 0; i<10 && picnum <= 5009; i++)
		{
			ShowPic(image_color_temp.tp[i], picnum);
			picnum++;
		}
}



void CImageRetrievalDlg::OnStnClickedView2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CImageRetrievalDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
