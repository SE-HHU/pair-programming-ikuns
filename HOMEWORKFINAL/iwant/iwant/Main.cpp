#include <conio.h>
#include <stdio.h>
#include <windows.h>	//用到了定时函数sleep()
#include<iostream>
#include <math.h>
#include<fstream>
#include<string>
#include<vector>
#include"tools.h"



using namespace std;

//全局变量
EasyTextBox txtName;//用户名输入框
EasyTextBox txtPwd;//密码输入框
EasyTextBox txtSec;//密保输入框
EasyButton btnOK;//OK按钮
EasyButton regis;//注册按钮
EasyButton back;//返回按钮
EasyButton start;//开始按钮
EasyButton fb;//找回按钮
vector<string> qName;//用户名
vector<string> qPwd;//密码
vector<string> qSec;//密保


//调用函数
void Start_game();//开始游戏事件
void On_btnOk_Click1();
void Regis_OK();//注册页面OK的事件
void regis_Click();//点击注册后的事件
void find_back();//点击找回后的事件
void find_back_check();//检查输入的用户名及其密保对不对
string wide_Char_To_Multi_Byte();//转化
wchar_t* multi_Byte_To_Wide_Char(const string& pKey);//转化
void txt_to_vector();//读取文件内容
void initialization();//回到主界面

int vector_find(string s,vector<string> vec) {
	for (int i = 0; i < vec.size(); ++i) {
		if (vec[i] == s) {
			return i;
		}
	}
	return -1;
}
void txt_to_vector() {
	ifstream f1("usersName.txt");
	ifstream f2("usersPwd.txt");
	ifstream f3("usersSec.txt");
	string temp1;
	string temp2;
	string temp3;

	while (getline(f1, temp1))
	{
		qName.push_back(temp1);
	}
	while (getline(f2, temp2))
	{
		qPwd.push_back(temp2);
	}
	while (getline(f3, temp3))
	{
		qSec.push_back(temp3);
	}
	
}
wchar_t* multi_Byte_To_Wide_Char(const string& pKey)
{
	//string 转 char*
	const char* pCStrKey = pKey.c_str();
	//第一次调用返回转换后的字符串长度，用于确认为wchar_t*开辟多大的内存空间
	int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
	wchar_t* pWCStrKey = new wchar_t[pSize];
	//第二次调用将单字节字符串转换成双字节字符串
	MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
	return pWCStrKey;
}
string wide_Char_To_Multi_Byte(wchar_t* pWCStrKey)
{
	//第一次调用确认转换后单字节字符串的长度，用于开辟空间
	int pSize = WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), NULL, 0, NULL, NULL);
	char* pCStrKey = new char[pSize + 1];
	//第二次调用将双字节字符串转换成单字节字符串
	WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), pCStrKey, pSize, NULL, NULL);
	pCStrKey[pSize] = '\0';
	string pKey = pCStrKey;
	return 	pKey;

}

void initialization() {
	initgraph(640, 480);
	IMAGE pic;
	loadimage(&pic, L"bk.jpg", 640, 480);
	putimage(0, 0, &pic);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(50, 55, L"用户名：");
	txtName.Create(120, 50, 400, 75, 10);						// 创建用户名文本框控件
	outtextxy(50, 105, L"密　码：");
	txtPwd.Create(120, 100, 400, 125, 10);						// 创建密码文本框控件
	regis.Create(120, 150, 200, 175, L"注册", regis_Click);
	fb.Create(320, 150, 400, 175, L"找回", find_back);
	start.Create(420, 350, 600, 400, L"开始游戏", Start_game);
	ExMessage msg;
	while (true)
	{
		msg = getmessage(EM_MOUSE);			// 获取消息输入

		if (msg.message == WM_LBUTTONDOWN)
		{
			// 判断控件
			if (txtName.Check(msg.x, msg.y))	txtName.OnMessage();

			// 判断控件
			if (txtPwd.Check(msg.x, msg.y))		txtPwd.OnMessage();

			// 判断控件
			//if (btnOK.Check(msg.x, msg.y))		btnOK.OnMessage();

			if (regis.Check(msg.x, msg.y))       regis.OnMessage();

			if (start.Check(msg.x, msg.y))     start.OnMessage();

			if (fb.Check(msg.x, msg.y))     fb.OnMessage();


			FlushMouseMsgBuffer();//清空鼠标消息缓存区
		}
	}
	// 关闭绘图窗口
	closegraph();
}
void find_back_check() {
	string name, pwd, sec;
	name = wide_Char_To_Multi_Byte(txtName.Text());
	pwd = wide_Char_To_Multi_Byte(txtPwd.Text());
	sec = wide_Char_To_Multi_Byte(txtSec.Text());
	int index = vector_find(name,qName);
	if (index == -1||name == "" || sec == "") {
		MessageBox(GetHWnd(), L"请检查你的用户名是否正确", L"错误！", MB_OK);
	}
	else {
		if (qSec[index] == sec) {
			MessageBox(GetHWnd(), multi_Byte_To_Wide_Char(qPwd[index]), L"你的密码是", MB_OK);
		}
		else {
			MessageBox(GetHWnd(), L"请检查你的密保是否正确", L"错误！", MB_OK);
		}
	}
	
	//重新输入
	cleardevice();
	initgraph(640, 480);
	IMAGE pic;
	loadimage(&pic, L"bk.jpg", 640, 480);
	putimage(0, 0, &pic);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(50, 55, L"用户名：");
	txtName.Create(120, 50, 400, 75, 10);						// 创建用户名文本框控件
	outtextxy(50, 105, L"密 保：");
	txtSec.Create(120, 100, 400, 125, 10);						// 创建密保文本框控件
	btnOK.Create(320, 150, 400, 175, L"OK", find_back_check);
	back.Create(120, 150, 200, 175, L"取消", initialization);
	ExMessage msg;
	while (true)
	{
		msg = getmessage(EM_MOUSE);			// 获取消息输入

		if (msg.message == WM_LBUTTONDOWN)
		{
			if (txtSec.Check(msg.x, msg.y))	   txtSec.OnMessage();

			// 判断控件
			if (txtName.Check(msg.x, msg.y))	txtName.OnMessage();

			// 判断控件
			if (btnOK.Check(msg.x, msg.y))		btnOK.OnMessage();

			if (back.Check(msg.x, msg.y))		back.OnMessage();

			FlushMouseMsgBuffer();//清空鼠标消息缓存区
		}
	}

	// 关闭绘图窗口
	closegraph();
}

// 按钮 btnOK 的点击事件
void find_back() {
	initgraph(640, 480);
	IMAGE pic;
	loadimage(&pic, L"bk.jpg", 640, 480);
	putimage(0, 0, &pic);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(50, 55, L"用户名：");
	txtName.Create(120, 50, 400, 75, 10);						// 创建用户名文本框控件
	outtextxy(50, 105, L"密 保：");
	txtSec.Create(120, 100, 400, 125, 10);						// 创建密保文本框控件
	btnOK.Create(320, 150, 400, 175, L"OK", find_back_check);
	back.Create(120, 150, 200, 175, L"取消", initialization);
	ExMessage msg;
	while (true)
	{
		msg = getmessage(EM_MOUSE);			// 获取消息输入

		if (msg.message == WM_LBUTTONDOWN)
		{
			if (txtSec.Check(msg.x, msg.y))	   txtSec.OnMessage();

			// 判断控件
			if (txtName.Check(msg.x, msg.y))	txtName.OnMessage();

			// 判断控件
			if (btnOK.Check(msg.x, msg.y))		btnOK.OnMessage();

			if (back.Check(msg.x, msg.y))		back.OnMessage();

			FlushMouseMsgBuffer();//清空鼠标消息缓存区
		}
	}

	// 关闭绘图窗口
	closegraph();
}
void Start_game() { 
	string name = wide_Char_To_Multi_Byte(txtName.Text());
	string pwd = wide_Char_To_Multi_Byte(txtPwd.Text());
	int index = vector_find(name, qName);
	if (index == -1) {
		MessageBox(GetHWnd(), L"请检查用户名是否正确！", L"错误！", MB_OK);
	}
	else {
		if (pwd != qPwd[index])
			MessageBox(GetHWnd(), L"请检查密码是否正确！", L"错误！", MB_OK);
		else
		{
			wchar_t s[100] = L"Hello！";
			wcscat_s(s, 100, txtName.Text());
			/*if (wcscmp(L"Hello！", s)) MessageBox(GetHWnd(), L"请检查你的用户名！", L"错误！", MB_OK);
			else*/ MessageBox(GetHWnd(), s, L"游戏已开始", MB_OK);
		}
	}
}
void On_btnOk_Click1()
{

	if (wcscmp(L"123", txtPwd.Text()))
		MessageBox(GetHWnd(), L"密码错误", L"错误", MB_OK);
	else
	{
		wchar_t s[100] = L"Hello, ";
		wcscat_s(s, 100, txtName.Text());
		MessageBox(GetHWnd(), s,L"Hello", MB_OK);
	}
}
void Regis_OK() {
	
	string name = wide_Char_To_Multi_Byte(txtName.Text());
	string pwd = wide_Char_To_Multi_Byte(txtPwd.Text());
	string sec = wide_Char_To_Multi_Byte(txtSec.Text());
	if(vector_find(name, qName)!=-1||name=="")
	{
		MessageBox(GetHWnd(), L"该用户名已被注册或不符合规范！", L"错误！", MB_OK);
	}
	else if (pwd == "") {
		MessageBox(GetHWnd(), L"请输入密码！", L"错误！", MB_OK);
	}

	else if (vector_find(sec, qSec) != -1||sec == "")
	{
		MessageBox(GetHWnd(), L"该密保不安全或不符合规范！", L"错误！", MB_OK);
	}
	else {
		ofstream f1("usersName.txt", ios::out | ios::app | ios::binary, _SH_DENYNO);
		ofstream f2("usersPwd.txt", ios::out | ios::app | ios::binary, _SH_DENYNO);
		ofstream f3("usersSec.txt", ios::out | ios::app | ios::binary, _SH_DENYNO);
		f1 << name << endl;
		f2 << pwd << endl;
		f3 << sec << endl;
		f1.close();
		f2.close();
		f3.close();
		qName.push_back(name);
		qPwd.push_back(pwd);
		qSec.push_back(sec);

		initgraph(640, 480);
		IMAGE pic;
		loadimage(&pic, L"bk.jpg", 640, 480);
		putimage(0, 0, &pic);
		setbkmode(TRANSPARENT);
		settextcolor(BLACK);
		outtextxy(50, 55, L"用户名：");
		txtName.Create(120, 50, 400, 75, 10);						// 创建用户名文本框控件
		outtextxy(50, 105, L"密　码：");
		txtPwd.Create(120, 100, 400, 125, 10);						// 创建密码文本框控件
		regis.Create(120, 150, 200, 175, L"注册", regis_Click);
		fb.Create(320, 150, 400, 175, L"找回", find_back);
		start.Create(420, 350, 600, 400, L"开始游戏", Start_game);
		ExMessage msg;
		while (true)
		{
			msg = getmessage(EM_MOUSE);			// 获取消息输入

			if (msg.message == WM_LBUTTONDOWN)
			{
				// 判断控件
				if (txtName.Check(msg.x, msg.y))	txtName.OnMessage();

				if (txtPwd.Check(msg.x, msg.y))		txtPwd.OnMessage();

				if (regis.Check(msg.x, msg.y))       regis.OnMessage();

				if (start.Check(msg.x, msg.y))     start.OnMessage();

				if (fb.Check(msg.x, msg.y))     fb.OnMessage();

				FlushMouseMsgBuffer();//清空鼠标消息缓存区
			}
		}

		// 关闭绘图窗口
		closegraph();
	}
	initgraph(640, 480);
	IMAGE pic;
	loadimage(&pic, L"bk.jpg", 640, 480);
	putimage(0, 0, &pic);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(50, 55, L"用户名：");
	txtName.Create(120, 50, 400, 75, 10);						// 创建用户名文本框控件
	outtextxy(50, 105, L"密　码：");
	txtPwd.Create(120, 100, 400, 125, 10);						// 创建密码文本框控件
	outtextxy(50, 155, L"密　保：");
	txtSec.Create(120, 150, 400, 175, 10);        //创建密保串
	btnOK.Create(320, 200, 400, 225, L"OK", Regis_OK);	// 创建按钮控件
	back.Create(120, 200, 200, 225, L"取消", initialization);
	ExMessage msg;
	while (true)
	{
		msg = getmessage(EM_MOUSE);			// 获取消息输入
		if (msg.message == WM_LBUTTONDOWN)
		{
			// 判断控件
			if (txtName.Check(msg.x, msg.y))	txtName.OnMessage();

			// 判断控件
			if (txtPwd.Check(msg.x, msg.y))		txtPwd.OnMessage();

			// 判断控件
			if (btnOK.Check(msg.x, msg.y))		btnOK.OnMessage();

			//判断密保事件
			if (txtSec.Check(msg.x, msg.y))		txtSec.OnMessage();

			if (back.Check(msg.x, msg.y))  back.OnMessage();

			FlushMouseMsgBuffer();//清空鼠标消息缓存区
		}
	}
}
void regis_Click() {
	cleardevice();
	initgraph(640, 480);
	IMAGE pic;
	loadimage(&pic, L"bk.jpg", 640, 480);
	putimage(0, 0, &pic);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(50, 55, L"用户名：");
	txtName.Create(120, 50, 400, 75, 10);						// 创建用户名文本框控件
	outtextxy(50, 105, L"密　码：");
	txtPwd.Create(120, 100, 400, 125, 10);						// 创建密码文本框控件
	outtextxy(50, 155, L"密　保：");								
	txtSec.Create(120, 150, 400, 175, 10);        //创建密保串
	btnOK.Create(320, 200, 400, 225, L"OK", Regis_OK);	// 创建按钮控件
	back.Create(120, 200, 200, 225, L"取消", initialization);	// 创建返回按钮控件
	ExMessage msg;
	while (true)
	{
		msg = getmessage(EM_MOUSE);			// 获取消息输入

		if (msg.message == WM_LBUTTONDOWN)
		{
			
			// 判断控件
			if (txtName.Check(msg.x, msg.y))	txtName.OnMessage();

			if (txtPwd.Check(msg.x, msg.y))		txtPwd.OnMessage();

			if (btnOK.Check(msg.x, msg.y))		btnOK.OnMessage();

			//判断密保事件
			if (txtSec.Check(msg.x, msg.y))		txtSec.OnMessage();

			if (back.Check(msg.x, msg.y))			back.OnMessage();

			FlushMouseMsgBuffer();//清空鼠标消息缓存区
		}
	}
}

// 主函数
int main()
{
	//先把文件中的内容读入到vector
	txt_to_vector();
	//画出主界面窗口
	initialization();
	return 0;
}