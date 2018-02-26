#include "camera.h"
#include <cmath>
#include <iostream>



// TODO
// devuelve los valores de distancia de los planos a partir del fov horizontal
FRUSTUM makeFrustum(double fovX, double aspectRatio, double nearValue, double farValue)
{
	const double DEG2RAD = 3.14159265 / 180;

	double tangent = tan((fovX / 2) * DEG2RAD); // tangent of half fovX
	double width = nearValue * tangent;   // half width of near plane
	double height = width * (1/aspectRatio); // half height of near plane

	FRUSTUM ret;

	ret.left = -width;
	ret.right = width;
	ret.bottom = -height;
	ret.top = height;
	ret.nearValue = nearValue;
	ret.farValue = farValue;
	// TODO : rellenar valores de ret
	return ret;
}

MATRIX4 lookAt(VECTOR3D eyePosition, VECTOR3D target, VECTOR3D upVector, VECTOR3D &newup, VECTOR3D &newside)
{

	//VECTOR3D forward = Substract(target, eyePosition);
	newside = CrossProduct(target, upVector);
	newup = CrossProduct(newside, target);


	VECTOR3D forward = Normalize(target);
	VECTOR3D side = Normalize(newside);
	VECTOR3D up = Normalize(newup);

	//printf("forward: %f , %f , %f \n", forward.x, forward.y, forward.z);
	//printf("side: %f , %f , %f \n", side.x, side.y, side.z);
	//printf("up: %i , %i , %i \n", up.x, up.y, up.z);

	//std::cout << "prueba:  " << up.x << "  prueba 2 :   " << forward.x << std::endl;


	MATRIX3 rot;
	rot.column0 = side;
	rot.column1 = up;
	rot.column2 = MultiplyWithScalar(-1, forward);

	MATRIX4 look = InverseOrthogonalMatrix(rot, eyePosition);

	return look;
}


void updateEulerOrientation(EULER& euler)
{
	QUATERNION qx, qy, qz;

	qx = QuaternionFromAngleAxis(euler.pitch, { 1,0,0 });
	qy = QuaternionFromAngleAxis(euler.yaw, { 0,1,0 });
	qz = QuaternionFromAngleAxis(euler.roll, { 0,0,1 });

	euler.orientation = Multiply(qz, Multiply(qy, qx));

}

VECTOR3D getForward(EULER euler)
{
	return RotateWithQuaternion({ 0,0,-1 }, euler.orientation);
}
