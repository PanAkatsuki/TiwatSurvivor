#pragma once
#include <graphics.h>

class APimon;

class UBullet
{
public:
	UBullet();
	~UBullet();

private:
	APimon* Owner = nullptr;

private:
	int Radius = 10;
	POINT Position = { 0, 0 };

	double RadialSpeed = 0.0045;
	double TangentSpeed = 0.0055;

public:
	void Update(int InID);

	void Rend();

public:
	inline void SetOwner(APimon* InOwner) { Owner = InOwner; }

	inline POINT GetPosition() const { return Position; }
};