#pragma once
#include "Character.h"


class APlayerController;
class UBullet;


class APimon : public ACharacter
{
public:
	APimon(const FAtlasSet& InAtlasSet);
	~APimon();

private:
	int Score = 0;

	std::shared_ptr<APlayerController> Controller;

	std::vector<std::shared_ptr<UBullet>> BulletList;

protected:
	std::shared_ptr<APlayerController> CreatePlayerController();

	virtual void OnDamage() override;

public:
	void Update();
	virtual void Move() override;
	void UpdateBullet();

	void RendAnimationAndBullet();

	virtual POINT CalculateShadowPosition() override { return { Position.x + 35, Position.y + 65 }; }

	inline int GetScore() const { return Score; }
	inline void SetScore(int InScore) { Score = InScore; }
	inline std::shared_ptr<APlayerController> GetPlayerController() { return Controller; }
	inline std::vector<std::shared_ptr<UBullet>> GetBulletList() const { return BulletList; }
};