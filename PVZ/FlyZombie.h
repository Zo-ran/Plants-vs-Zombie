#pragma once
#include<list>
using namespace std;
class FlyZombie 
{
	friend class FlyZombieList;

protected:
	double x, y;

	int blood;

	bool fly;    //�����жϸý�ʬ�Ƿ񱻻���

public:
	FlyZombie();
};

class FlyZombieList
{
protected:
	list<FlyZombie *> l;

	virtual void setcolor();

	virtual void d(FlyZombie *t) { };
public:
	virtual void Add();
	
	FlyZombieList();

	void Move();   //��ʬ����ǰ�ƶ�
		
	bool RowJudge(int row);

	void Draw(); //�ڵ�ͼ�ϻ��ƽ�ʬ

	bool BeHit(double x, double y);

	bool Over();
};

