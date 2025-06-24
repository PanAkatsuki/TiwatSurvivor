#pragma once

enum class EGameStage
{
	End,
	Menu,
	Playing
};

enum class EDirection
{ 
	left,
	right
};

enum class ESpawnEdge
{
	Up,
	Down, 
	Left,
	Right
};

enum class EButtonStatus
{
	Idle,
	Hovered,
	Pushed
};
