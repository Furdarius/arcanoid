#include <stdlib.h>
#include <GL/glut.h>
#include <string>
#include <iostream>
#include <string>
#include "CCircle.h"
#include "CVector2D.h"
#include "GameInstance.h"

/*
CCircle::CCircle(float x, float y,
				float radius,
				int r, int g, int b, int a) : CDrawObject(x, y, r, g, b, a)
{
	setRadius(radius);
};
*/
void CCircle::draw()
{
	checkCollision();
	std::vector<int> color = getColor();
	CPoint2D<float> position = getPosition();
	float radius = getRadius();

	int posX = position.x;
	int posY = position.y;

	glColor3f(color[0], color[1], color[2]);

	double _tmpPoint;
    glBegin(GL_TRIANGLE_FAN);
		glVertex2f(posX, posY);
		for( int i = 0; i <= radius + 1; i++ ) 
		{
			_tmpPoint = (float)i / radius * 3.1415f * 2.0f;
			glVertex2f(posX + cos(_tmpPoint) * radius, 
				posY + sin(_tmpPoint) * radius);
		}
    glEnd();
}

void CCircle::setRadius(float radius)
{
	fRadius = radius;
}

float CCircle::getRadius()
{
	return fRadius;
}

void CCircle::checkCollision()
{
	float radius = getRadius();

	if ((this->position.x + radius) > CGameHudInstance->fWindowWidth)
	{
		this->position.x = CGameHudInstance->fWindowWidth - radius;
		this->velocity.reflect(CVector2D<float>(-1.0f, 0.0f));
		//this->velocity *= 0.8f;
	}
	else if ((this->position.x - radius) < 0)
	{
		this->position.x = radius;
		this->velocity.reflect(CVector2D<float>(1.0f, 0.0f));
		//this->velocity *= 0.8f;
	}
	/*
	if ((this->position.y + radius) > CGameHudInstance->fWindowHeigth)
	{
		this->position.y = CGameHudInstance->fWindowHeigth - radius;
		this->velocity.reflect(CVector2D<float>(0.0f, -1.0f));
		//this->velocity *= 0.8f;
	}
	else if ((this->position.y - radius) < 0)
	{
		this->position.y = radius;
		this->velocity.reflect(CVector2D<float>(0.0f, 1.0f));
		//this->velocity *= 0.8f;
		//this->velocity.x *= 0.9999f; // friction
	}
	*/
	if ((this->position.y - radius) > CGameHudInstance->fWindowHeigth
		|| (this->position.y + radius) < 0)
	{
		this->setPosition(CGameHudInstance->fWindowWidth / 2, CGameHudInstance->fWindowHeigth / 2);
		this->setVelocity(getRandom(-0.3f, 0.3f), getRandom(-0.3f, 0.3f));
	}

	CPoint2D<float> batBottomPos = CGameHudInstance->batBottom->getPosition();
	std::vector<float> batBottomSize = CGameHudInstance->batBottom->getSize();
	

	this->CollideCircleVsRectangle(CGameHudInstance->batBottom);
	this->CollideCircleVsRectangle(CGameHudInstance->batTop);
}

// NEXT METODS INCLUDE COLLISION DETECTION
// SHOULD BE REFACTORED!!!

void CCircle::CollideCircleVsRectangle(CRectangle* pTileObject)
{	
	CPoint2D<float> pos = this->position;
	float r = getRadius();

	CPoint2D<float> tilePos = pTileObject->getPosition();
	std::vector<float> tileSize = pTileObject->getSize();
	float tx = tilePos.x;
	float ty = tilePos.y;
	float txw = tileSize[0];
	float tyw = tileSize[1];

	float dx = pos.x - (tx); // tile->obj delta
	float px = (txw / 2 + r) - std::abs(dx - txw / 2); // penetration depth in x
	if(px > 0)
	{
		float dy = pos.y - (ty); // tile->obj delta
		float py = (tyw / 2 + r) - std::abs(dy - tyw / 2); // penetration depth in y
		if(py >= 0)
		{
			this->velocity *= 1.1;
			//object may be colliding with tile
						
			//determine grid/voronoi region of circle center
			int oH = 0;
			int oV = 0;
			//std::cout << "dx=" << dx << " dy=" << dy << std::endl;
			if(dx < 0)
			{
				//circle is on left side of tile
				oH = -1;
			}
			else if(txw < dx)
			{
				//circle is on right side of tile
				oH = 1;
			}
		
			if(dy < 0)
			{
				//circle is on top side of tile
				oV = -1;
			}
			else if(tyw < dy)
			{
				//circle is on bottom side of tile
				oV = 1;
			}			
			//std::cout << "oH=" << oH << " oV=" << oV << std::endl;
			ResolveCircleTile(px, py, oH, oV, pTileObject);
		}
	}
}

void CCircle::ResolveCircleTile(float px, float py, int oH, int oV, CRectangle* c)
{
	this->ProjCircle_Full(px, py, oH, oV, c);
}

void CCircle::ProjCircle_Full(float x, float y, int oH, int oV, CRectangle* t)
{
	//if we're colliding vs. the current cell, we need to project along the
	//smallest penetration vector.
	//if we're colliding vs. horiz. or vert. neighb, we simply project horiz/vert
	//if we're colliding diagonally, we need to collide vs. tile corner
	//std::cout << "oH=" << oH << " oV=" << oV << std::endl;
	if (oH == 0)
	{
		if(oV == 0)
		{
			//collision with current cell
			if(x < y)
			{
				//penetration in x is smaller; project in x
				CPoint2D<float> tilePos = t->getPosition();
				float dx = this->position.x - tilePos.x;//get sign for projection along x-axis
				//NOTE: should we handle the delta == 0 case?! and how? (project towards oldpos?)
				if(dx < 0)
				{
					this->ReportCollisionVsWorld(-x, 0, -1, 0, t);
				}
				else
				{
					this->ReportCollisionVsWorld(x, 0, 1, 0, t);
				}
			}
			else
			{
				CPoint2D<float> tilePos = t->getPosition();
				//penetration in y is smaller; project in y		
				float dy = this->position.y - tilePos.y;//get sign for projection along y-axis

				//NOTE: should we handle the delta == 0 case?! and how? (project towards oldpos?)					
				if(dy < 0)
				{
					this->ReportCollisionVsWorld(0, -y, 0, -1, t);
				}
				else
				{
					this->ReportCollisionVsWorld(0, y, 0, 1, t);
				}				
			}
		}
		else
		{
			//collision with vertical neighbor
			this->ReportCollisionVsWorld(0, y * oV, 0, oV, t);
		}
	}
	else if(oV == 0)
	{
		//collision with horizontal neighbor
		this->ReportCollisionVsWorld(x * oH, 0, oH, 0, t);
	}
	else
	{
		//std::cout << "oH=" << oH << " oV=" << oV << std::endl;
		oH = std::max(oH, 0);
		oV = std::max(oV, 0);
		//diagonal collision
		CPoint2D<float> tilePos = t->getPosition();
		std::vector<float> tileSize = t->getSize();
		float r = this->getRadius();
		//get diag vertex position
		float vx = tilePos.x + (oH * tileSize[0]);
		float vy = tilePos.y + (oV * tileSize[1]);
			
		float dx = this->position.x - vx;//calc vert->circle vector		
		float dy =  this->position.y - vy;
			
		float len = std::sqrt(dx*dx + dy*dy);
		float pen = r - len;
		if(0 < pen)
		{
			//vertex is in the circle; project outward
			if(len == 0)
			{
				//project out by 45deg
				dx = oH / 1.4142135623731;
				dy = oV / 1.4142135623731;
			}
			else
			{
				dx /= len;
				dy /= len;
			}
			
			this->ReportCollisionVsWorld(dx * pen, dy * pen, dx, dy, t);

		}
	}
}

void CCircle::ReportCollisionVsWorld(float px, float py, int dx, int dy, CRectangle* t)
{
	//std::cout << "CCircle::ReportCollisionVsWorld("<< px << ", " << py << ", " << dx << ", " << dy << ")"<< std::endl;
	CPoint2D<float> pos = this->getPosition();
	//std::cout << "dx=" << dx << " dy=" << dy << std::endl;
	CVector2D<float> vel = this->getVelocity();
	float dp = (vel.x * dx + vel.y * dy);
	//std::cout << "dp=" << dp << std::endl;
	//float nx = dp * dx; // project velocity onto collision normal
	//float ny = dp * dy; // nx,ny is normal velocity
	float nx = dx; // project velocity onto collision normal
	float ny = dy; // nx,ny is normal velocity
	//std::cout << nx << " " << ny << std::endl;
	//std::cout << "nx=" << nx << " ny=" << ny << std::endl;
	float tx = vel.x - nx; // px,py is tangent velocity
	float ty = vel.y - ny;

	//we only want to apply collision response forces if the object is travelling into, and not out of, the collision
	float b,bx,by,f,fx,fy;
	if(dp < 0)
	{
		f = 1; // FRICTION
		fx = tx*f;
		fy = ty*f;		
		
		b = 1;// BOUNCE. this bounce constant should be elsewhere, i.e inside the object/tile/etc..
		
		bx = (nx*b);
		by = (ny*b);
	
	}
	else
	{
		//moving out of collision, do not apply forces
		bx = by = fx = fy = 0;
	}
	this->position.x += px + bx + fx;//project object out of collision
	this->position.y += py + by + fy;

	this->velocity.reflect(CVector2D<float>(nx, ny));
	//this->velocity *= 0.8f;
}
