/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snek(Location{ brd.getWidth()/2, brd.getHeight()/2 }, brd),
	food(rng, brd, snek, obstacles, currentObstacles)
{}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (started && !ended) {
		char direction = snek.getDirection();
		if (direction == 0 || direction == 2) {
			if (wnd.kbd.KeyIsPressed(VK_UP))
				tempDirection = 1;
			if (wnd.kbd.KeyIsPressed(VK_DOWN))
				tempDirection = 3;
		}
		else if (direction == 1 || direction == 3) {
			if (wnd.kbd.KeyIsPressed(VK_RIGHT))
				tempDirection = 2;
			if (wnd.kbd.KeyIsPressed(VK_LEFT))
				tempDirection = 0;
		}
		if (snek.getHeadLocation() == food.getLocation()) {
			food.respawn(rng, brd, snek, obstacles, currentObstacles);
			eaten = true;
			score++;
		}
		if (snekMoveCounter >= snekMovePeriod) {
			snek.setDirection(tempDirection);
			if (eaten) {
				snek.grow();
				if (snekMovePeriod > 0) snekMovePeriod--;
				eaten = false;
			}
			snek.update(obstacles, currentObstacles);
			ended = snek.isHeadEatingBody() || snek.hasBangedIntoWall() || snek.hasBangedIntoObstacle();
			snekMoveCounter = 0;
		}
		snekMoveCounter++;
		if (spawnObstacleCounter >= spawnObstacleTime) {
			obstacles[currentObstacles++].init(rng, brd, obstacles, currentObstacles, snek);
			spawnObstacleCounter = 0;
		}
		spawnObstacleCounter++;
	}
	else if (!started && !ended) {
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
			started = true;
	}
}

void Game::ComposeFrame() {
	
	if (!started) {
		SpriteCodex::DrawTitle(200, 200, gfx);
	}
	else {
		snek.draw(brd);
		food.draw(brd);

		for (int i = 0; i < currentObstacles; i++)
			obstacles[i].draw(brd);

		brd.drawBoundary();
		if (ended)
			SpriteCodex::DrawGameOver(200, 200, gfx);
	}
}