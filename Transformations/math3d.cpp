#include "math3d.h"
#include <cmath>

VECTOR3D Add(VECTOR3D a, VECTOR3D b) //Ya implementado como ejemplo.
{
	VECTOR3D ret;
	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return ret;
}

VECTOR3D Substract(VECTOR3D a, VECTOR3D b)
{
	VECTOR3D sol;
	sol.x = a.x - b.x;
	sol.y = a.y - b.y;
	sol.z = a.z - b.z;
	return sol;
}

VECTOR3D Multiply(VECTOR3D a, VECTOR3D b)
{
	VECTOR3D sol;
	sol.x = a.x * b.x;
	sol.y = a.y * b.y;
	sol.z = a.z * b.z;
	return sol;
}

VECTOR3D MultiplyWithScalar(float scalar, VECTOR3D a)
{
	VECTOR3D sol;
	sol.x = a.x * scalar;
	sol.y = a.y * scalar;
	sol.z = a.z * scalar;
	return sol;
}

double Magnitude(VECTOR3D a)
{
	double sol = sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));

	return sol;
}

VECTOR3D Normalize(VECTOR3D a)
{
	double m = Magnitude(a);

	VECTOR3D sol = MultiplyWithScalar(1/m, a);

	return sol;
}

VECTOR3D CrossProduct(VECTOR3D a, VECTOR3D b)
{
	VECTOR3D sol;
	sol.x = a.y * b.z - a.z * b.y;
	sol.y = a.z * b.x - a.x * b.z;
	sol.z = a.x * b.y - a.y * b.x;
	return sol;
}

double DotProduct(VECTOR3D a, VECTOR3D b)
{
	double sol = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);

	return sol;
}

MATRIX3 Transpose(MATRIX3 m)
{
	MATRIX3 sol;

	sol.column0 = { m.column0.x, m.column1.x, m.column2.x };
	sol.column1 = { m.column0.y, m.column1.y, m.column2.y };
	sol.column2 = { m.column0.z, m.column1.z, m.column2.z };

	return sol;
}

VECTOR3D Transform(MATRIX3 m, VECTOR3D a)
{
	VECTOR3D sol;
	sol.x = DotProduct(m.column0, a);
	sol.y = DotProduct(m.column1, a);
	sol.z = DotProduct(m.column2, a);
	return sol;
}

MATRIX4 InverseOrthogonalMatrix(MATRIX3 A, VECTOR3D t)
{
	MATRIX4 sol;
	VECTOR3D tr = MultiplyWithScalar(-1,Transform(A, t));
	MATRIX3 At = Transpose(A);
	
		sol.m[0] = At.column0.x;
		sol.m[1] = At.column0.y;
		sol.m[2] = At.column0.z;
		sol.m[3] = 0;

		sol.m[4] = At.column1.x;
		sol.m[5] = At.column1.y;
		sol.m[6] = At.column1.z;
		sol.m[7] = 0;

		sol.m[8] = At.column2.x;
		sol.m[9] = At.column2.y;
		sol.m[10] = At.column2.z;
		sol.m[11] = 0;

		sol.m[12] = tr.x;
		sol.m[13] = tr.y;
		sol.m[14] = tr.z;
		sol.m[15] = 1;

	return sol;


}

QUATERNION QuaternionFromAngleAxis(float angle, VECTOR3D axis)
{
	QUATERNION sol;

	sol.v = MultiplyWithScalar(sin(angle/2), axis);
	sol.s = cos(angle / 2);

	return sol;
	
}

//QUATERNION QuaternionFromToVectors(VECTOR3D from, VECTOR3D to)
//{
//		
//}

QUATERNION Multiply(QUATERNION a, QUATERNION b)
{
	QUATERNION sol;

	sol.s = a.s*b.s - a.v.x*b.v.x - a.v.y*b.v.y - a.v.z*b.v.z;
	sol.v.x = a.s*b.v.x + a.v.x*b.s + a.v.y*b.v.z - a.v.z*b.v.y;
	sol.v.y = a.s*b.v.y - a.v.x*b.v.z + a.v.y*b.s + a.v.z*b.v.x;
	sol.v.z = a.s*b.v.z + a.v.x*b.v.y - a.v.y*b.v.x + a.v.z*b.s;

	return sol;
}

QUATERNION Conjugate(QUATERNION a)
{
	QUATERNION sol;

	sol.s = a.s;
	sol.v = MultiplyWithScalar(-1, a.v);

	return sol;
}

VECTOR3D RotateWithQuaternion(VECTOR3D a, QUATERNION q)
{
	QUATERNION p;
	p.s = 0;
	p.v = a;

	QUATERNION q_i = Conjugate(q);

	QUATERNION sol = Multiply(Multiply(q, p), q_i);

	return sol.v;
}