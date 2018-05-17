
// EducationDlg.h : 头文件
//
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "AddMessage.h"
#include "Student.h"
using namespace std;


// CEducationDlg 对话框
class CEducationDlg : public CDialogEx
{
// 构造
public:
	CEducationDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDUCATION_DIALOG };
#endif

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

	void showMessage(string text, string title);
	bool cmp(student &first, student &second);

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	void sortStudent(char *fileName, char *outFileName);
	// 如：姓名，学号
	CString nameOrNumber;
};
