
// MFC_ImageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_Image.h"
#include "MFC_ImageDlg.h"
#include "afxdialogex.h"

#include "windows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//ȫ�ֱ���
CString gReadFilePathName;
CString filename;

int height = 600;
int width = 800;
FILE *fp = NULL;
unsigned char *process_image = NULL;

//��������洢ͼƬ��Ϣ
BITMAPINFO *pBmpInfo;       //��¼ͼ��ϸ��
BYTE *pBmpData;             //ͼ������
BITMAPFILEHEADER bmpHeader; //�ļ�ͷ
BITMAPINFOHEADER bmpInfo;   //��Ϣͷ
CFile bmpFile;              //��¼���ļ�

//�ݴα任
float v = 0.6;

//��ͼƬ��־
char open_flag = 0;



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


// CMFC_ImageDlg �Ի���



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


// CMFC_ImageDlg ��Ϣ�������

BOOL CMFC_ImageDlg::OnInitDialog()
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFC_ImageDlg::OnPaint()
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
HCURSOR CMFC_ImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_ImageDlg::OnBnClickedOk()
{
	//MessageBox(_T("Hello World!"));
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}

//���ļ�
void CMFC_ImageDlg::OnBnClickedButton1()
{

	CFileDialog fileDlg(true, _T("bmp"), _T("*.bmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("bmp Files (*.bmp)|*.bmp|All File (*.*)|*.*||"), NULL); 
	//TRUEΪ���ļ��Ի���FALSEΪ�����ļ��Ի���
	//ȱʡ����չ��
	//ȱʡ��ʾ���ļ�����Ͽ�ı༭����ļ�����һ���ѡNULL
	//�Ի�����һ��ΪOFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, ������ֻ��ѡ��͸��������ļ�ǰ��ʾ��
	//�ļ�ɸѡ���ͣ���ָ���ɹ�ѡ����ļ����ͺ���Ӧ����չ����
	//������ָ�룬һ���ѡNULL.

	if (fileDlg.DoModal() == IDOK) //�����Ի��� 
	{
		gReadFilePathName = fileDlg.GetPathName();//�õ��������ļ�����Ŀ¼����չ�� 
		filename = fileDlg.GetFileName(); 
	}
	//�򿪶Ի����ȡͼ����Ϣ
	CString BmpName = gReadFilePathName;     //��ȡ�ļ�·����   ��D:\pic\abc.bmp
	CString EntName = fileDlg.GetFileExt();      //��ȡ�ļ���չ��
	EntName.MakeLower();                     //���ļ���չ��ת��Ϊһ��Сд�ַ�
	if (EntName.Compare(_T("bmp")) == 0)
	{
		//��������洢ͼƬ��Ϣ
//		BITMAPINFO *pBmpInfo;       //��¼ͼ��ϸ��
//		BYTE *pBmpData;             //ͼ������
//		BITMAPFILEHEADER bmpHeader; //�ļ�ͷ
//		BITMAPINFOHEADER bmpInfo;   //��Ϣͷ
//		CFile bmpFile;              //��¼���ļ�
									//��ֻ���ķ�ʽ���ļ� ��ȡbmpͼƬ������ bmp�ļ�ͷ ��Ϣ ����
		if (!bmpFile.Open(BmpName, CFile::modeRead | CFile::typeBinary))
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
		CWnd *pWnd = GetDlgItem(IDC_STATIC); //���pictrue�ؼ����ڵľ��
		CRect rect;
		pWnd->GetClientRect(&rect); //���pictrue�ؼ����ڵľ�������
		CDC *pDC = pWnd->GetDC(); //���pictrue�ؼ���DC
		pDC->SetStretchBltMode(COLORONCOLOR);
		StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0,
			bmpInfo.biWidth, bmpInfo.biHeight, pBmpData, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
		
		//���ļ���־
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

		CWnd *pWnd = GetDlgItem(IDOK); //���pictrue�ؼ����ڵľ��
		CRect rect;
		pWnd->GetClientRect(&rect); //���pictrue�ؼ����ڵľ�������
		CDC *pDC = pWnd->GetDC(); //���pictrue�ؼ���DC
		pDC->SetStretchBltMode(COLORONCOLOR);
		StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0,
			bmpInfo.biWidth, bmpInfo.biHeight, process_image, pBmpInfo, DIB_RGB_COLORS, SRCCOPY); \
		
		free(process_image);
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//ֱ��ͼ���⻯
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
		
		for (i = 0; i < bmpInfo.biWidth * bmpInfo.biHeight *3; i+=3) //�����־���ֱ��ͼ  ֱ��ͼ  ͳ��ÿ���Ҷȼ����ص�ĸ���
		{
				unsigned char GrayIndex = pBmpData[i];
				hist[GrayIndex] ++;
		}
		for (i = 0; i< 256; i++)   // ����Ҷȷֲ��ܶ�
		{
			fpHist[i] = (float)hist[i] / (float)size;
		}
		for (i = 0; i< 256; i++)   // �����ۼ�ֱ��ͼ�ֲ�
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

		//�ۼƷֲ�ȡ���������������ĻҶ�ӳ���ϵ
		for (i = 0; i< 256; i++)
		{
			eqHist[i] = (int)(255.0 * eqHistTemp[i] + 0.5);
		}
		for (i = 0; i < bmpInfo.biWidth * bmpInfo.biHeight *3; i+=3) //���лҶ�ӳ�� ���⻯
		{
				unsigned char GrayIndex = pBmpData[i];
				process_image[i] = eqHist[GrayIndex];
		}
		//2st
		memset(&hist, 0x00, sizeof(int) * 256);
		memset(&fpHist, 0x00, sizeof(float) * 256);
		memset(&eqHistTemp, 0x00, sizeof(float) * 256);

		for (i = 1; i < bmpInfo.biWidth * bmpInfo.biHeight * 3; i += 3) //�����־���ֱ��ͼ  ֱ��ͼ  ͳ��ÿ���Ҷȼ����ص�ĸ���
		{
			unsigned char GrayIndex = pBmpData[i];
			hist[GrayIndex] ++;
		}
		for (i = 0; i< 256; i++)   // ����Ҷȷֲ��ܶ�
		{
			fpHist[i] = (float)hist[i] / (float)size;
		}
		for (i = 0; i< 256; i++)   // �����ۼ�ֱ��ͼ�ֲ�
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

		//�ۼƷֲ�ȡ���������������ĻҶ�ӳ���ϵ
		for (i = 0; i< 256; i++)
		{
			eqHist[i] = (int)(255.0 * eqHistTemp[i] + 0.5);
		}
		for (i = 1; i < bmpInfo.biWidth * bmpInfo.biHeight * 3; i += 3) //���лҶ�ӳ�� ���⻯
		{
			unsigned char GrayIndex = pBmpData[i];
			process_image[i] = eqHist[GrayIndex];
		}
		//3st
		memset(&hist, 0x00, sizeof(int) * 256);
		memset(&fpHist, 0x00, sizeof(float) * 256);
		memset(&eqHistTemp, 0x00, sizeof(float) * 256);

		for (i = 2; i < bmpInfo.biWidth * bmpInfo.biHeight * 3; i += 3) //�����־���ֱ��ͼ  ֱ��ͼ  ͳ��ÿ���Ҷȼ����ص�ĸ���
		{
			unsigned char GrayIndex = pBmpData[i];
			hist[GrayIndex] ++;
		}
		for (i = 0; i< 256; i++)   // ����Ҷȷֲ��ܶ�
		{
			fpHist[i] = (float)hist[i] / (float)size;
		}
		for (i = 0; i< 256; i++)   // �����ۼ�ֱ��ͼ�ֲ�
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

		//�ۼƷֲ�ȡ���������������ĻҶ�ӳ���ϵ
		for (i = 0; i< 256; i++)
		{
			eqHist[i] = (int)(255.0 * eqHistTemp[i] + 0.5);
		}
		for (i = 2; i < bmpInfo.biWidth * bmpInfo.biHeight * 3; i += 3) //���лҶ�ӳ�� ���⻯
		{
			unsigned char GrayIndex = pBmpData[i];
			process_image[i] = eqHist[GrayIndex];
		}



		CWnd *pWnd = GetDlgItem(IDOK); //���pictrue�ؼ����ڵľ��
		CRect rect;
		pWnd->GetClientRect(&rect); //���pictrue�ؼ����ڵľ�������
		CDC *pDC = pWnd->GetDC(); //���pictrue�ؼ���DC
		pDC->SetStretchBltMode(COLORONCOLOR);
		StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0,
			bmpInfo.biWidth, bmpInfo.biHeight, process_image, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
		free(process_image);
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//�ݴα任
void CMFC_ImageDlg::OnBnClickedButton4()
{
	CString num1;
	char num[256] = { '\0' };
	GetDlgItemText(IDC_EDIT2, num1);//��ȡ����ĸ�����1
	v = _ttoi(num1);//���ַ���ת��Ϊ�����������
	//v = atoi(num1);
	if (open_flag == 1)
	{
		process_image = (unsigned char*)malloc(height*width * 3 * sizeof(unsigned char));
		for (int i = 0; i < bmpInfo.biWidth * bmpInfo.biHeight * 3; i++)
		{
			process_image[i] = pow(pBmpData[i] / 255.0, v / 10) * 255;
		}


		CWnd *pWnd = GetDlgItem(IDOK); //���pictrue�ؼ����ڵľ��
		CRect rect;
		pWnd->GetClientRect(&rect); //���pictrue�ؼ����ڵľ�������
		CDC *pDC = pWnd->GetDC(); //���pictrue�ؼ���DC
		pDC->SetStretchBltMode(COLORONCOLOR);
		StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0,
			bmpInfo.biWidth, bmpInfo.biHeight, process_image, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
		free(process_image);
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFC_ImageDlg::OnEnChangeEdit1()
{
		//v = atof(input_v);

	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFC_ImageDlg::OnEnChangeEdit2()
{
	//v = atof(input_vv);
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
