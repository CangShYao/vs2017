
// EducationDlg.h : ͷ�ļ�
//
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "AddMessage.h"
#include "Student.h"
using namespace std;


// CEducationDlg �Ի���
class CEducationDlg : public CDialogEx
{
// ����
public:
	CEducationDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDUCATION_DIALOG };
#endif

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

	void showMessage(string text, string title);
	bool cmp(student &first, student &second);

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	void sortStudent(char *fileName, char *outFileName);
	// �磺������ѧ��
	CString nameOrNumber;
};
