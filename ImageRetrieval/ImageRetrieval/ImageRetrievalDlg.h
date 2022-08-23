
// ImageRetrievalDlg.h : 头文件
//

#pragma once


// CImageRetrievalDlg 对话框
class CImageRetrievalDlg : public CDialogEx
{
// 构造
public:
	CImageRetrievalDlg(CWnd* pParent = NULL);	// 标准构造函数
	void general(CString pathfile, int mode);
	void RGBToHSV(int r, int g, int b, double *h, double *s, double *v);
	int mymin(int, int, int);
	int mymax(int, int, int);
	void sort();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGERETRIEVAL_DIALOG };
#endif

	int	method;//图像特征提取模式
	int	c_method;//基于颜色特征模式下的方法选择

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
