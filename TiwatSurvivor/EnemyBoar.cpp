#include "EnemyBoar.h"

#include <random>


AEnemyBoar::AEnemyBoar(const FAtlasSet& InAtlasSet)
	: AEnemy(InAtlasSet)
{
	Speed = 2;

	// Random Spawn Position
	static std::random_device rd;
	static std::mt19937 gen(rd());

	static std::uniform_int_distribution<int> DistEdge(0, 3);
	static std::uniform_int_distribution<int> DistX(-FrameData.FrameLength, WINDOW_WIDTH);
	static std::uniform_int_distribution<int> DistY(-FrameData.FrameHeight, WINDOW_HEIGHT);

	ESpawnEdge Edge = static_cast<ESpawnEdge>(DistEdge(gen));

	switch (Edge)
	{
	case ESpawnEdge::Up:
		Position.x = DistX(gen);
		Position.y = 0 - FrameData.FrameHeight;
		break;
	case ESpawnEdge::Down:
		Position.x = DistX(gen);
		Position.y = WINDOW_HEIGHT;
		break;
	case ESpawnEdge::Left:
		Position.x = -FrameData.FrameLength;
		Position.y = DistY(gen);
		break;
	case ESpawnEdge::Right:
		Position.x = WINDOW_WIDTH;
		Position.y = DistY(gen);
		break;
	default:
		break;
	}
}

AEnemyBoar::~AEnemyBoar()
{
}


