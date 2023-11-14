#include "math.h"

namespace Math {

	// Linear Interpolation
	float Lerp(float a, float b, float t) {
		return (1.0f - t) * a + b * t;
	}

	// Vector2 Inplementation
	Vector2::Vector2(float _x, float _y) {
		x = _x;
		y = _y;
	}
	Vector2 Vector2::Lerp(Vector2 a, Vector2 b, float t) {
		return Vector2(Math::Lerp(a.x, b.x, t), Math::Lerp(a.y, b.y, t));
	}
	Vector2::~Vector2(){}

	// Vector2Int Inplementation
	Vector2Int::Vector2Int(int _x, int _y) {
		x = _x;
		y = _y;
	}
	Vector2Int::~Vector2Int() {}

	

}