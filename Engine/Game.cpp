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
	food(rng, brd, snek)
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
			food.respawn(rng, brd, snek);
			eaten = true;
			score++;
		}
		if (updatesDun >= snekMovePeriod) {
			snek.setDirection(tempDirection);
			if (eaten) {
				snek.grow();
				if(snekMovePeriod > 0) snekMovePeriod--;
				eaten = false;
			}
			snek.update();
			ended = snek.isHeadEatingBody() || snek.hasBangedIntoWall();
			updatesDun = 0;
		}
		updatesDun++;
	}
	else if (!started && !ended) {
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
			started = true;
	}
}

void Game::ComposeFrame() {
	snek.draw(brd);
	food.draw(brd);
	drawBoundary();
	if (!started) {
		SpriteCodex::DrawTitle(200, 200, gfx);
	}
	else if (ended) {
		SpriteCodex::DrawGameOver(200, 200, gfx);
	}
}

void Game::drawBoundary() {
	gfx.DrawRectDim(0, 0, brd.getSide(), brd.getSide() * brd.getHeight(), Colors::Blue);
	gfx.DrawRectDim(brd.getSide() * (brd.getWidth() - 1), 0, brd.getSide(), brd.getSide() * brd.getHeight(), Colors::Blue);
	gfx.DrawRectDim(0, 0, brd.getSide() * brd.getWidth(), brd.getSide(), Colors::Blue);
	gfx.DrawRectDim(0, brd.getSide() * (brd.getHeight() - 1), brd.getSide() * brd.getWidth(), brd.getSide(), Colors::Blue);
}