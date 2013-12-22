#pragma once

#include <math.h>

template<typename _T>
class CVector2D 
{

	public:

		_T x;
		_T y;

		CVector2D (void)
		{
			x = 0;
			y = 0;
		}

		CVector2D (const _T& _x, const _T& _y)
		{
			x = _x;
			y = _y;
		}

		CVector2D (const _T& num)
		{
			x = num;
			y = num;
		}

		CVector2D (const CVector2D& source)
		{
			x = source.x;
			y = source.y;
		}

		void operator = (const CVector2D& source)
		{
			x = source.x;
			y = source.y;
		}

		void operator = (const _T& num)
		{
			x = num;
			y = num;
		}

		void operator += (const CVector2D& source)
		{
			x += source.x;
			y += source.y;
		}

		void operator += (const _T& num)
		{
			x += num;
			y += num;
		}

		void operator -= (const CVector2D& source)
		{
			x -= source.x;
			y -= source.y;
		}

		void operator -= (const _T& num)
		{
			x -= num;
			y -= num;
		}

		void operator *= (const CVector2D& source)
		{
			x *= source.x;
			y *= source.y;
		}

		void operator *= (const _T& num)
		{
			x *= num;
			y *= num;
		}

		void operator /= (const CVector2D& source)
		{
			x /= source.x;
			y /= source.y;
		}

		void operator /= (const _T& num)
		{
			x /= num;
			y /= num;
		}

		CVector2D operator + (const CVector2D& source)
		{
			return CVector2D(x + source.x, y + source.y);
		}


		CVector2D operator + (const _T& num)
		{
			return CVector2D(x + num, y + num);
		}

		CVector2D operator - (const CVector2D& source)
		{
			return CVector2D(x - source.x, y - source.y);
		}


		CVector2D operator - (const _T& num)
		{
			return CVector2D(x - num, y - num);
		}

		CVector2D operator * (const CVector2D& source)
		{
			return CVector2D(x * source.x, y * source.y);
		}


		CVector2D operator * (const _T& num)
		{
			return CVector2D(x * num, y * num);
		}

		CVector2D operator / (const CVector2D& source)
		{
			return CVector2D(x / source.x, y / source.y);
		}


		CVector2D operator / (const _T& num)
		{
			return CVector2D(x / num, y / num);
		}

		void setup(const _T& _x, const _T& _y)
		{
			x = _x;
			y = _y;
		}

		_T dot(const CVector2D& source)
		{
			return x * source.x + y * source.y;
		}

		_T length(void)
		{
			return sqrtf(dot(*this));
		}

		void normalize(void)
		{
			*this /= length();
		}

		void reflect(const CVector2D& normal)
		{
			_T dotVal = dot(normal);
			setup(x - (_T)2 * dotVal * normal.x, y - (_T)2 * dotVal * normal.y);
		}
};