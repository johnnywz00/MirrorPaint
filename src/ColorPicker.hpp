//
//  ColorPicker.hpp
//  MirrorDraw
//
//  Created by John Ziegler on 2/21/26.
//  Copyright © 2026 John Ziegler. All rights reserved.
//

#ifndef ColorPicker_hpp
#define ColorPicker_hpp

#include "mirrorpaint.hpp"

class ColorPicker : public Drawable
{
public:
	void setup (vecf pos);
	
	void refreshImage (float brightness);
	
	float recalcBrightness (int x, int y, vecf cofs);
	
	void draw (RenderTarget &target, RenderStates states) const;
	
	void moveAll (vecf newPos);
	
	float updateSlider (int x, int y, vecf cofs);
	
	Color getColorAt (int x, int y, float brightness)
	{
		return hsbToRgb((x - colorsSprite.gP().x) / 3, (y - colorsSprite.gP().y) / 3, brightness);
	}
	
	void deactivate ()
	{
		isActive = false;
		moveAll({-2000, -2000});
	}
	
	void activate ()
	{
		isActive = true;
		moveAll(anchorPos);
	}
	
	Sprite			colorsSprite
					, slider
	;
	RectangleShape	pane;
	Text			txt;
	VertexArray		brightnessSpectrum {TriangleStrip};
	Texture			tx;
	ZImage			zimg;
	vecf			anchorPos;
	bool			isActive = false;
};

#endif /* ColorPicker_hpp */
