#include "stdafx.h"
#include "Face.h"


CFace::CFace()
	: vN(0)
	, vI(NULL)
{
}


CFace::~CFace()
{
	if (vI != NULL)
	{
		delete[]vI;
		vI = NULL;
	}
}


void CFace::SetNum(int en)
{
	vN = en;
	vI = new int[vN];
}
