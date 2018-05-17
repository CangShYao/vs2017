#pragma once
#include "Student.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
// AddMessage �Ի���

class AddMessage : public CDialog
{
	DECLARE_DYNAMIC(AddMessage)

public:
	AddMessage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AddMessage();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
	void showMessage(string text, string title);
	void sortFile(char *fileName, char *outFileName);
public:
	// ѧ��
	CString stuNumber;
	// ����
	CString stuName;
	// �༶
	CString stuClass;
	// ��ѧ
	CString stuMath;
	// Ӣ��
	CString stuEnglish;
	// ����
	CString stuWuli;
	afx_msg void OnBnClickedButton1();
};
