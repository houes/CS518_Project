#include "Vector.h"

double Vector::computeAngle_wrt(const Vector& v0)
{
	// return angle in rad
	// the current vector v's angle w.r.t its previous vector v0
	// if from v0->v turn left, 
	//    angle >0
	// else 
	//    angle <0
	double TOL = 1e-7;

	bool leftTurn = false;

	double crossp = v0.cross_product(*this);

	if (crossp > 0)
		leftTurn = true;
	else
		leftTurn = false;

	double angle = acos(v0.dot_product(*this) / v0.length() / this->length()); //[0,PI]

	if (leftTurn)
		angle = abs(angle);
	else
		angle = -abs(angle);

	if (abs(angle) < TOL)
		angle = 0;

	return angle;
}