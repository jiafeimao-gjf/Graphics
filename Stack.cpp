#include "stdafx.h"
#include "Stack.h"


CStack::CStack()
{
	p = new CPoint[10];
	length = 0;
	size = 10;
}


CStack::~CStack()
{
	delete p;
}

void CStack::Push(CPoint q)
{
	if (length == size) {
		CPoint *_p = new CPoint[size + 10];
		for (int i = 0; i < size; i++) {
			_p[i] = p[i];
		}
		size += 10;
		p = _p;
		delete _p;
	}
	p[length] = q;
	length++;
}

CPoint CStack::Pop()
{
	length--;
	return p[length];
}

bool CStack::empty()
{
	if (length == 0) return false;
	else return true;
}

int CStack::Getlength()
{
	return length;
}
