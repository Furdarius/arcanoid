#pragma once

#include <math.h>

template<typename _T>
class CPoint2D 
{
public:

	_T x;
	_T y;

	CPoint2D (void)
	{
		x = 0;
		y = 0;
	}

	CPoint2D (const _T& _x, const _T& _y)
	{
		x = _x;
		y = _y;
	}

	CPoint2D (const _T& num)
	{
		x = num;
		y = num;
	}

	CPoint2D (const CPoint2D& source)
	{
		x = source.x;
		y = source.y;
	}

	void operator = (const CPoint2D& source)
	{
		x = source.x;
		y = source.y;
	}

	void operator = (const _T& num)
	{
		x = num;
		y = num;
	}

	void setup(const _T& _x, const _T& _y)
	{
		x = _x;
		y = _y;
	}
};