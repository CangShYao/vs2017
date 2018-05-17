#pragma once
#include "Student.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
// AddMessage 对话框

class AddMessage : public CDialog
{
	DECLARE_DYNAMIC(AddMessage)

public:
	AddMessage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddMessage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	void showMessage(string text, string title);
	void sortFile(char *fileName, char *outFileName);
public:
	// 学号
	CString stuNumber;
	// 姓名
	CString stuName;
	// 班级
	CString stuClass;
	// 数学
	CString stuMath;
	// 英语
	CString stuEnglish;
	// 物理
	CString stuWuli;
	afx_msg void OnBnClickedButton1();
};
