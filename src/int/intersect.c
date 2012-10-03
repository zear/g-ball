#include "intersect.h"

float tolerance = 0.2;
int inLine(float *p, float x1, float y1, float x2, float y2)
{
	
}

int circleLineIntersect(float x1, float y1, float x2, float y2, float cx, float cy, float r, float *f) {
	float dx = x2 - x1;
	float dy = y2 - y1;
	
	float a = dx * dx + dy * dy;
	float b = 2 * (dx * (x1 - cx) + dy * (y1 - cy));
	float c = cx * cx + cy * cy;
	
	c += x1 * x1 + y1 * y1;
	c -= 2 * (cx * x1 + cy * y1);
	c -= r * r;
	
	float delta = b * b - 4 * a * c;
	
	if (delta < 0) {  // Not intersecting
    return 0;
	}
	else {
		
		float mu = (-b + sqrt( delta )) / (2*a);
		f[0] = x1 + mu*(dx);
		f[1] = y1 + mu*(dy);
		mu = (-b - sqrt( delta )) / (2*a);
		f[2] = x1 + mu*(dx);
		f[3] = y1 + mu*(dy);
		
		//TODO: Check if point is inside line, in order not to have anything outside our segment.
		
		
		return (delta == 0) ? 1 : 2;
		// Figure out which point is closer to the circle
	}
}