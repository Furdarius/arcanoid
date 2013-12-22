#include "CVector2D.h"

template<typename _T> 
CVector2D::CVector2D(void)
{
	x = 0;
	y = 0;
}

//template<typename _T>
//CVector2D::CVector2D (const _T& _x, const _T& _y)
//{
//	x = _x;
//	y = _y;
//}
//
//template<typename _T>
//CVector2D::CVector2D (const _T& num)
//{
//	x = num;
//	y = num;
//}
//
//template<typename _T>
//CVector2D::CVector2D (const CVector2D& source)
//{
//	x = source.x;
//	y = source.y;
//}
//
//template<typename _T>
//void CVector2D::operator = (const CVector2D& source)
//{
//	x = source.x;
//	y = source.y;
//}
//
//template<typename _T>
//void CVector2D::operator = (const _T& num)
//{
//	x = num;
//	y = num;
//}
//
//template<typename _T>
//void CVector2D::operator += (const CVector2D& source)
//{
//	x += source.x;
//	y += source.y;
//}
//
//template<typename _T>
//void CVector2D::operator += (const _T& num)
//{
//	x += num;
//	y += num;
//}
//
//template<typename _T>
//void CVector2D::operator -= (const CVector2D& source)
//{
//	x -= source.x;
//	y -= source.y;
//}
//
//template<typename _T>
//void CVector2D::operator -= (const _T& num)
//{
//	x -= num;
//	y -= num;
//}
//
//template<typename _T>
//void CVector2D::operator *= (const CVector2D& source)
//{
//	x *= source.x;
//	y *= source.y;
//}
//
//template<typename _T>
//void CVector2D::operator *= (const _T& num)
//{
//	x *= num;
//	y *= num;
//}
//
//template<typename _T>
//void CVector2D::operator /= (const CVector2D& source)
//{
//	x /= source.x;
//	y /= source.y;
//}
//
//template<typename _T>
//void CVector2D::operator /= (const _T& num)
//{
//	x /= num;
//	y /= num;
//}
//
//template<typename _T>
//CVector2D::CVector2D operator + (const CVector2D& source)
//{
//	return CVector2D::CVector2D(x + source.x, y + source.y);
//}
//
//template<typename _T>
//CVector2D::CVector2D operator + (const _T& num)
//{
//	return CVector2D(x + num, y + num);
//}
//
//template<typename _T>
//CVector2D::CVector2D operator - (const CVector2D& source)
//{
//	return CVector2D(x - source.x, y - source.y);
//}
//
//template<typename _T>
//CVector2D::CVector2D operator - (const _T& num)
//{
//	return CVector2D(x - num, y - num);
//}
//
//template<typename _T>
//CVector2D::CVector2D operator * (const CVector2D& source)
//{
//	return CVector2D(x * source.x, y * source.y);
//}
//
//template<typename _T>
//CVector2D::CVector2D operator * (const _T& num)
//{
//	return CVector2D(x * num, y * num);
//}
//
//template<typename _T>
//CVector2D::CVector2D operator / (const CVector2D& source)
//{
//	return CVector2D(x / source.x, y / source.y);
//}
//
//template<typename _T>
//CVector2D::CVector2D operator / (const _T& num)
//{
//	return CVector2D(x / num, y / num);
//}
//
//template<typename _T>
//void CVector2D::setup(const _T& _x, const _T& _y)
//{
//	x = _x;
//	y = _y;
//}
//
//template<typename _T>
//_T CVector2D::dot(const CVector2D& source)
//{
//	return x * source.x + y * source.y;
//}
//
//template<typename _T>
//_T CVector2D::length(void)
//{
//	return sqrtf(dot(*this));
//}
//
//template<typename _T>
//void CVector2D::normalize(void)
//{
//	*this /= length();
//}
//
//template<typename _T>
//void CVector2D::reflect(const CVector2D& normal)
//{
//	_T dotVal = dot(normal);
//	setup(x - (_T)2 * dotVal * normal.x, y - (_T)2 * dotVal * normal.y);
//}