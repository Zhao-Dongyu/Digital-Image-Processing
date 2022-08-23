
// ImageRetrievalDlg.h : ͷ�ļ�
//

#pragma once


// CImageRetrievalDlg �Ի���
class CImageRetrievalDlg : public CDialogEx
{
// ����
public:
	CImageRetrievalDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void general(CString pathfile, int mode);
	void RGBToHSV(int r, int g, int b, double *h, double *s, double *v);
	int mymin(int, int, int);
	int mymax(int, int, int);
	void sort();
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGERETRIEVAL_DIALOG };
#endif

	int	method;//ͼ��������ȡģʽ
	int	c_method;//������ɫ����ģʽ�µķ���ѡ��

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()

private:
	void RunDir(const CString &strfile2);
	void StartDir(const CString &strfile1);
	void ShowPic(CString pathfile, int idc);
	void Color_SeekImage();

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedPath();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnStnClickedView2();
	afx_msg void OnBnClickedButton1();
};
