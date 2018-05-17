
// EducationDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "Education.h"
#include "EducationDlg.h"
#include "afxdialogex.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CEducationDlg 对话框



CEducationDlg::CEducationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EDUCATION_DIALOG, pParent)
	, nameOrNumber(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEducationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, nameOrNumber);
	DDV_MaxChars(pDX, nameOrNumber, 20);
}

BEGIN_MESSAGE_MAP(CEducationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CEducationDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CEducationDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CEducationDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CEducationDlg 消息处理程序

BOOL CEducationDlg::OnInitDialog()
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
	sortStudent("a.txt", "b.txt");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CEducationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEducationDlg::OnPaint()
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
HCURSOR CEducationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CEducationDlg::showMessage(string text, string title)
{
	CString Text1(text.c_str());
	CString Title1(title.c_str());
	MessageBox(Text1, Title1, MB_OK);
}

void CEducationDlg::sortStudent(char * fileName, char * outFileName)
{
	if (fileName == "") return;
	ifstream fin;
	fin.open(fileName);
	if (!fin.is_open())
	{
		showMessage("File open failed!", "Information");
		return;
	}
	char buffer[1024] = { 0 };
	fin.getline(buffer, 1024);
	stringstream stuMessage(buffer);
	vector<student> students;
	while (!fin.eof())
	{
		fin.getline(buffer, 1024);
		stringstream temp(buffer);
		string stuNumber, stuName, stuProfess, stuMath, stuEnglish, stuPhysical;
		temp >> stuNumber >> stuName >> stuProfess >> stuMath >> stuEnglish >> stuPhysical;
		student stu(stuNumber, stuName, stuProfess, stuMath, stuEnglish, stuPhysical);
		students.push_back(stu);
	}
	fin.close();
	for (int i = 0; i < students.size(); i++)
	{
		for (int j = i + 1; j < students.size(); j++)
		{
			if (students[i].getTotal() < students[j].getTotal())
			{
				student temp = students[i];
				students[i] = students[j];
				students[j] = temp;
			}
			if (students[i].getTotal() == students[j].getTotal())
			{
				if (students[i].getDMath() > students[j].getDMath())
				{
					student temp = students[i];
					students[i] = students[j];
					students[j] = temp;
				}
			}
		}
	}
	ofstream fout;
	fout.open(outFileName, ios::out | ios::trunc);
	if (!fout.is_open())
	{
		showMessage("File open failed!", "Information");
		return;
	}
	fout << "学号" << "\t\t" << "姓名" << "  " << "\t\t" << "专业" << "\t" << "数学" << "\t" << "外语" << "\t" << "物理" << "\n";
	for (int i = 0; i < students.size(); i++)
	{
		fout << students[i].getNumber() << "\t" << students[i].getName() << "\t\t" << students[i].getProfess() << "\t"
			<< students[i].getMath() << "\t" << students[i].getEnglish() << "\t" << students[i].getPhysical() << "\n";
	}
	fout.close();
}

bool CEducationDlg::cmp(student & first, student & second)
{
	return first.getTotal() > second.getTotal();
}

void CEducationDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (nameOrNumber == "")
		return;
	ifstream fin;
	fin.open("b.txt");
	if (!fin.is_open())
	{
		showMessage("File open failed!", "Information");
		return;
	}
	char buffer[1024] = { 0 };
	fin.getline(buffer, 1024);
	stringstream stuMessage(buffer);
	while (!fin.eof())
	{
		fin.getline(buffer, 1024);
		stringstream temp(buffer);
		string stuNumber, stuName, stuProfess, stuMath, stuEnglish, stuWuli;
		temp >> stuNumber >> stuName >> stuProfess >> stuMath >> stuEnglish >> stuWuli;
		USES_CONVERSION;
		string s(W2A(nameOrNumber));
		if (s == stuName)
		{
			string outPut = stuNumber + "-" + stuName + "-" + stuProfess + "-" + stuMath + "-" + stuEnglish + "-" + stuWuli;
			string t = "Information";
			showMessage(outPut, t);
			return;
		}
	}
	fin.close();
	string s = "No such person!";
	string t = "Information";
	showMessage(s, t);
}


void CEducationDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (nameOrNumber == "") return;
	ifstream fin;
	fin.open("a.txt");
	char buffer[1024] = { 0 };
	fin.getline(buffer, 1024);
	stringstream stuMessage(buffer);
	vector<student> students;
	int count = 0;
	while (!fin.eof())
	{
		fin.getline(buffer, 1024);
		stringstream temp(buffer);
		string stuNumber, stuName, stuProfess, stuMath, stuEnglish, stuPhysical;
		temp >> stuNumber >> stuName >> stuProfess >> stuMath >> stuEnglish >> stuPhysical;
		USES_CONVERSION;
		string s(W2A(nameOrNumber));
		if (stuNumber != s)
		{
			student stu(stuNumber, stuName, stuProfess, stuMath, stuEnglish, stuPhysical);
			students.push_back(stu);
		}
		count++;
	}
	if (count == students.size())
	{
		showMessage("No such person!", "Information");
		return;
	}
	fin.close();
	ofstream fout;
	fout.open("a.txt", ios::out | ios::trunc);
	if (!fout.is_open())
	{
		showMessage("File open failed!", "Information");
		return;
	}
	fout << "学号" << "\t\t" << "姓名" << "  " << "\t\t" << "专业" << "\t" << "数学" << "\t" << "外语" << "\t" << "物理" << "\n";
	for (int i = 0; i < students.size(); i++)
	{
		fout << students[i].getNumber() << "\t" << students[i].getName() << "\t\t" << students[i].getProfess() << "\t"
			<< students[i].getMath() << "\t" << students[i].getEnglish() << "\t" << students[i].getPhysical() << "\n";
	}
	fout.close();
	sortStudent("a.txt", "b.txt");
	showMessage("Remove successful!", "Information");
}


void CEducationDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	AddMessage dalog;
	dalog.DoModal();
}