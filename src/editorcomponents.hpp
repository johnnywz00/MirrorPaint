//
//  DrawRegion.hpp
//  MirrorDraw
//
//  Created by John Ziegler on 2/11/25.
//  Copyright © 2025 John Ziegler. All rights reserved.
//

#ifndef EDITORCOMPONENTS_HPP
#define EDITORCOMPONENTS_HPP

#include "mirrorpaint.hpp"

enum ClockDir { clockwise, counterclockwise };

enum DrawingModeType
{
	regular
	, calligraphy
	, doubleOutline
	, inky
	, circleRoll
	, triangleRoll
	, hexagonRoll
	, starRoll
	, fill
	, gradientSpline
};



struct DrawRegion
{
	DrawRegion (float axAng, ClockDir dir=counterclockwise)
		: axisAngle(axAng)
		, dirFromAxis(dir)
	{
		ghost.setRadius(3);
		centerOrigin(ghost);
		ghost.setFillColor(Color(40, 40, 40, 40));
	}
	
	vecf derivePt (float mag, float degsToRotate)
	{
		if (dirFromAxis != clockwise)
			degsToRotate *= -1;
		return toRect(mag, axisAngle + degsToRotate);
	}
		
	CircleShape	ghost;
	ClockDir	dirFromAxis = clockwise;
	float 		axisAngle;
};



struct DrawingMode
{
	DrawingMode (DrawingModeType typ, bool periodic)
		: type(typ)
		, isPeriodic(periodic)
	{ }
	
	DrawingModeType type;
	bool isPeriodic;
};



class BrushButton
{
public:
	BrushButton (const Texture& t, DrawingMode mode_, vecf pos = vecf(0, 0))
		: spr(t)
		, mode(mode_)
	{
		centerOrigin(spr);
		spr.sP(pos);
	}
	
	Sprite spr;
	DrawingMode mode;
};



class Slider : public Drawable
{
public:
	Slider (string nam, vecf pos, float mn, float mx, float defval, const function<void(float)>& f)
		: handle(gTexture("sliderHandle"))
		, name(nam)
		, minVal(mn)
		, maxVal(mx)
		, defaultVal(defval)
		, func(f)
	{
		track.setSize({300, 3});
		track.setOrigin(0, track.gLB().height / 2);
		track.sP(pos);
		track.setFillColor(Color::Black);
		track.setScale(1, max(.333f, defaultVal / 3));
		centerOrigin(handle);
		handle.sP((((defaultVal - minVal) / (maxVal - minVal)) * track.getSize().x) + track.gP().x, track.gP().y);
		handle.setScale(.66, .66);
		
		label = Text(nam, gFont("slider"), 14);
		label.setPosition(track.gP() + vecF(0, 3));
		label.setFillColor(Color(0, 0, 0, 150));
	}
	
	void draw (RenderTarget& target, RenderStates states) const
	{
		target.draw(track);
		target.draw(label);
		target.draw(handle);
	}
	
	Sprite					handle;
	RectangleShape			track;
	Text					label;
	function<void(float)> 	func;
	string 					name;
	float					minVal
							, maxVal
							, defaultVal
							, curVal
	;
};

#endif /* DrawRegion_hpp */
