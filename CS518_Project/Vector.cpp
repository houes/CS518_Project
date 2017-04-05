#include "Vector.h"

double Vector::computeAngle_wrt(const Vector& v0)
{
	// return angle in rad
	// the current vector v's angle w.r.t its previous vector v0
	// if from v0->v turn left, 
	//    angle >0
	// else 
	//    angle <0

	bool leftTurn = false;

	double crossp = v0.cross_product(*this);

	if (crossp > 0)
		leftTurn = true;
	else
		leftTurn = false;

	double angle = asin(abs(crossp / this->length() / v0.length())); //>0

	if (leftTurn)
		angle = abs(angle);
	else
		angle = -abs(angle);

	return angle;
}