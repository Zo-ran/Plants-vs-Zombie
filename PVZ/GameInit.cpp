#include "GameInit.h"
#include <fstream>
#include <string>
#include <codecvt>

static ExMessage msg;
static bool dim_begin = false;
static bool dim_board = false;

inline std::wstring to_wide_string(const std::string& input) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(input);
}

void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //xΪ����ͼƬ��X���꣬yΪY����
{

	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++) {
		for (int ix = 0; ix < picture_width; ix++) {
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight) {
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}

void Draw_UI() {
	BeginBatchDraw();
	msg = getmessage(EM_MOUSE);
	IMAGE img;
	loadimage(NULL, _T("F:\\Downloads\\bkd.png"), ScreenWidth, ScreenHight);

	if (msg.x >= 250 && msg.x <= 354) {
		if (msg.y >= 180 && msg.y <= 238)
			dim_begin = true;
		else if (msg.y >= 250 && msg.y <= 308)
			dim_board = true;
		else {
			dim_begin = false;
			dim_board = false;
		}
	} else {
		dim_begin = false;
		dim_board = false;
	}

	if(dim_begin)
		loadimage(&img, _T("E:\\Advanced Programming\\PvZ\\PVZ\\beginl.png"), 104, 58);
	else
		loadimage(&img, _T("E:\\Advanced Programming\\PvZ\\PVZ\\begin.png"));
	drawAlpha(&img, 250, 180);

	if (dim_board)
		loadimage(&img, _T("E:\\Advanced Programming\\PvZ\\PVZ\\boardl.png"), 104, 58);
	else
		loadimage(&img, _T("F:\\Downloads\\board.png"));
	drawAlpha(&img, 250, 250);

	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("Ethnocentric"));
	settextcolor(RGB(84, 255, 159));
	outtextxy(65, 100, _T("ZZR's    PVZ"));

	EndBatchDraw();
}

EVENT GameInit() {
	Draw_UI();
	if (msg.message == WM_LBUTTONDOWN) {
		if (dim_begin)
			return GAME_START;
		else if (dim_board)
			return SHOW_SCOREBOARD;
	}

	return NONE;
}

bool ScoreBoard() {
	BeginBatchDraw();

	IMAGE img;
	std::ifstream infile("E:\\Advanced Programming\\PvZ\\PVZ\\score.txt", std::ios::in);
	int cnt = 0;
	std::string res = "\n\n\n\n";

	loadimage(NULL, _T("F:\\Downloads\\bkd.png"), ScreenWidth, ScreenHight);
	putimage(300, 100, &img);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("Ethnocentric"));
	settextcolor(WHITE);
	//����Ʒְ�ķ���
	RECT rect = { 200, 80, 400, 380 };
	drawtext(_T("SCOREBOARD"), &rect, DT_CENTER | DT_NOCLIP);
	std::string s;
	infile >> s;
	while (!infile.eof()) {
		res += "NO.";
		res += std::to_string(cnt++);
		res += "\t";
		res += s;
		res += "\n\n";
		infile >> s;
	}
	settextstyle(15, 0, _T("Ethnocentric"));
	std::wstring temp = to_wide_string(res);
	drawtext(temp.c_str(), &rect, DT_LEFT | DT_EXPANDTABS | DT_NOCLIP);
	infile.close();
	//�����صĲ˵���
	bool dim_menu = false;
	msg = getmessage(EM_MOUSE);
	if (msg.x >= 250 && msg.x <= 330 && msg.y >= 400 && msg.y <= 428)
		dim_menu = true;
	if(dim_menu)
		loadimage(&img, _T("F:\\Downloads\\menul.png"), 80, 28);
	else
		loadimage(&img, _T("F:\\Downloads\\menu.png"));
	drawAlpha(&img, 250, 400);
	

	EndBatchDraw();
	if (msg.message == WM_LBUTTONDOWN && dim_menu)
		return false;

	return true;
}