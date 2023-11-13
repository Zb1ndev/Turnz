#pragma once

namespace Math {

	class Vector2 {

	public:

		float x;
		float y;

		Vector2(float _x, float _y);
		~Vector2();

		Vector2& operator+=(const Vector2& rhs) {

			this->x = this->x + rhs.x;
			this->y = this->y + rhs.y;
			return *this;

		}

	};
	inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs) {

		Vector2 result = lhs;
		result += rhs;
		return result;

	}

}