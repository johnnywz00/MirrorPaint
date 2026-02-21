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
	ColorPicker () { }
	
	ColorPicker (vecf pos, const Texture& tx);
	
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
	VertexArray		brightnessSpectrum {TriangleStrip};
	Texture			tx;
	Image			img;
	vecf			anchorPos;
	bool			isActive = false;
};

#endif /* ColorPicker_hpp */
