// AddMessage.cpp : 实现文件
//

#include "stdafx.h"
#include "Education.h"
#include "AddMessage.h"
#include "afxdialogex.h"


// AddMessage 对话框

IMPLEMENT_DYNAMIC(AddMessage, CDialog)

AddMessage::AddMessage(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
	, stuNumber(_T(""))
	, stuName(_T(""))
	, stuClass(_T(""))
	, stuMath(_T(""))
	, stuEnglish(_T(""))
	, stuWuli(_T(""))
{

}

AddMessage::~AddMessage()
{
}

void AddMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, stuNumber);
	DDV_MaxChars(pDX, stuNumber, 20);
	DDX_Text(pDX, IDC_EDIT2, stuName);
	DDV_MaxChars(pDX, stuName, 20);
	DDX_Text(pDX, IDC_EDIT3, stuClass);
	DDV_MaxChars(pDX, stuClass, 10);
	DDX_Text(pDX, IDC_EDIT4, stuMath);
	DDV_MaxChars(pDX, stuMath, 5);
	DDX_Text(pDX, IDC_EDIT5, stuEnglish);
	DDV_MaxChars(pDX, stuEnglish, 5);
	DDX_Text(pDX, IDC_EDIT6, stuWuli);
	DDV_MaxChars(pDX, stuWuli, 5);
}

void AddMessage::showMessage(string text, string title)
{
	CString Text1(text.c_str());
	CString Title1(title.c_str());
	MessageBox(Text1, Title1, MB_OK);
}

void AddMessage::sortFile(char * fileName, char * outFileName)
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


BEGIN_MESSAGE_MAP(AddMessage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &AddMessage::OnBnClickedButton1)
END_MESSAGE_MAP()


// AddMessage 消息处理程序


void AddMessage::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (stuNumber == "" || stuName == "" || stuClass == "")
		return;
	ofstream fout;
	fout.open("a.txt", ios::out | ios::app);
	USES_CONVERSION;
	string s1(W2A(stuNumber));
	string s2(W2A(stuName));
	string s3(W2A(stuClass));
	string s4(W2A(stuMath));
	string s5(W2A(stuEnglish));
	string s6(W2A(stuWuli));
	fout << s1 << "\t" << s2 << "\t\t" << s3 << "\t"
		<< s4 << "\t" << s5 << "\t" << s6 << "\n";
	fout.close();
	sortFile("a.txt", "b.txt");
	showMessage("Add successful!", "Information");
}
