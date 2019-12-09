#pragma once
#include <Windows.h>
#include "Defines.h"
#include "Mathlib.h"

interface IRunnable {
public:
	virtual void Render(const HDC& hdc) = 0;
	virtual void Update(const _m_d_float& dt) = 0;
};
//void Render(const HDC& hdc) {} void Update(const _m_d_float& dt) {}

class Collider {
public:
	enum COLLIDER_TYPE {
		COLTYPE_DEFAULT,
		COLTYPE_ATOM,
		COLTYPE_IGNORE
	};
protected:
	COLLIDER_TYPE colType;
	
public:
	Collider() { colType = COLLIDER_TYPE::COLTYPE_DEFAULT; }
	Collider(COLLIDER_TYPE type);
	inline COLLIDER_TYPE getColType() const {
		return colType;
	}
	virtual bool CheckCollision(Collider* other, _m_d_float* overlapped) = 0;
};
//bool CheckCollision(Collider* other)

class CObject : public IRunnable, public Collider
{
public:
	_m_d_float mass;
	_m_d_float charge;
	Vector2 position;
	Vector2 velocity;

	CObject();
	virtual ~CObject() {}
};


class Atom : public CObject {
protected:
	_m_d_int radius;
public:
	Atom(_m_d_int _radius);
	void Render(const HDC& hdc);
	void Update(const _m_d_float& dt);
	bool CheckCollision(Collider* other, _m_d_float* overlapped);
};

class KineticObject : public Atom {
public:
	KineticObject(const Vector2& _position, _m_d_float _mass);
	void Update(const _m_d_float& dt) override {}
};