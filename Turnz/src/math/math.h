#pragma once

namespace Math {

	float Lerp(float a, float b, float t);

	class Vector2 {

	public:

		float x;
		float y;

		Vector2(float _x, float _y);
		Vector2 Lerp(Vector2 a, Vector2 b, float t);
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

	class Vector2Int {

	public:

		int x;
		int y;

		Vector2Int(int _x, int _y);
		~Vector2Int();

		Vector2Int& operator+=(const Vector2Int& rhs) {

			this->x = this->x + rhs.x;
			this->y = this->y + rhs.y;
			return *this;

		}

	};
	inline Vector2Int operator+(const Vector2Int& lhs, const Vector2Int& rhs) {

		Vector2Int result = lhs;
		result += rhs;
		return result;

	}

	


}