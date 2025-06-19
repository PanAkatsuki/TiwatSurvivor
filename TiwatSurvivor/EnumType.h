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

enum EButtonStatus
{
	Idle,
	Hovered,
	Pushed
};