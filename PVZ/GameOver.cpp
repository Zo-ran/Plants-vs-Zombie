#include "AllZombie.h"
#include "GameOver.h"
#include "GameInit.h"
#include <fstream>
#include <codecvt>
#include <string>
#include <list>
#include <iostream>

extern uint32_t TOTAL_SCORE;
std::list<int> buf;

bool GameOver() {
	return zombielist.Over() || flyzombielist.Over() || firezombielist.Over() || ffzombielist.Over();
}

inline std::wstring to_wide_string(const std::string& input) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(input);
}

void FILE_EVENT() {
	int idx = 0;
	bool in = false;
	std::ifstream numfile("E:\\Advanced Programming\\PvZ\\PVZ\\score.txt", std::ios::in);
	int a;
	numfile >> a;
	while (!numfile.eof()) {
		buf.push_back(a);
		numfile >> a;
	}
	for (auto i = buf.begin(); i != buf.end(); i++, idx++) {
		if (*i <= TOTAL_SCORE) {
			buf.insert(i, TOTAL_SCORE);
			in = true;
			break;
		}
	}
	if (buf.size() < 8 && !in) {
		buf.push_back(TOTAL_SCORE);
		in = true;
	}
	size_t cnt = 0;
	std::ofstream outfile("E:\\Advanced Programming\\PvZ\\PVZ\\score.txt", std::ios::out);
	for (auto i = buf.begin(); i != buf.end() && cnt < 8; i++, cnt++)
		outfile << *i << std::endl;
}


bool OVER_UI() {
	BeginBatchDraw();
	IMAGE img;
	std::string res = "\n\n\n\n";

	loadimage(NULL, _T("F:\\Downloads\\bkd.png"), ScreenWidth, ScreenHight);

	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("Ethnocentric"));
	settextcolor(WHITE);
	//输出计分板的分数
	RECT rect = { 200, 80, 400, 380 };
	drawtext(_T("SCOREBOARD"), &rect, DT_CENTER | DT_NOCLIP);

	int cnt = 0;
	for (auto i = buf.begin(); i != buf.end() && cnt < 8; i++) {
		std::string s;
		s = to_string(*i);
		res += "NO.";
		res += std::to_string(cnt++);
		res += "\t";
		res += s;
		res += "\n\n";
	}
	
	settextstyle(15, 0, _T("Ethnocentric"));
	std::wstring temp = to_wide_string(res);
	drawtext(temp.c_str(), &rect, DT_LEFT | DT_EXPANDTABS | DT_NOCLIP);
	//infile.close();
	//画返回的菜单栏
	bool dim_menu = false;
	ExMessage msg = getmessage(EM_MOUSE);
	if (msg.x >= 250 && msg.x <= 330 && msg.y >= 400 && msg.y <= 428)
		dim_menu = true;
	if (dim_menu)
		loadimage(&img, _T("F:\\Downloads\\okl.png"), 80, 28);
	else
		loadimage(&img, _T("F:\\Downloads\\ok.png"));
	putimage(250, 400, &img);

	IMAGE panel;
	loadimage(&panel, _T("F:\\Downloads\\panel.png"), 200, 100);
	drawAlpha(&panel, 390, 150);
	std::string score = to_string(TOTAL_SCORE);
	std::wstring out = to_wide_string(score);
	settextstyle(10, 0, _T("Ethnocentric"));
	rect = { 538, 182, 568, 202 };
	drawtext(out.c_str(), &rect, DT_CENTER | DT_NOCLIP);
	score = to_string(buf.front());
	out = to_wide_string(score);
	rect = { 543, 215, 563, 235 };
	drawtext(out.c_str(), &rect, DT_CENTER | DT_NOCLIP);

	IMAGE medal;
	if (TOTAL_SCORE > 2000) 
		loadimage(&medal, _T("F:\\Downloads\\gold.png"));
	else if (TOTAL_SCORE > 1000) 
		loadimage(&medal, _T("F:\\Downloads\\silver.png"));
	else 
		loadimage(&medal, _T("F:\\Downloads\\copper.png"));
	drawAlpha(&medal, 414, 185);

	EndBatchDraw();
	if (msg.message == WM_LBUTTONDOWN && dim_menu)
		return false;

	return true;
}