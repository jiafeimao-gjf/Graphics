#pragma once

class CStack
{
public:
	CStack();
	~CStack();
private:
	CPoint *p;
	int length;
	int size;
public:
	void Push(CPoint q);
	CPoint Pop();
	bool empty();
	int Getlength();
};

