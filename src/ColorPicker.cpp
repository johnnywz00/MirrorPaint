//
//  ColorPicker.cpp
//  MirrorDraw
//
//  Created by John Ziegler on 2/21/26.
//  Copyright © 2026 John Ziegler. All rights reserved.
//

#include "mirrorpaint.hpp"

void ColorPicker::setup (vecF pos)
{
	anchorPos = pos;
	
	pane.setSize({360 * 3 + 39, 306});
	pane.setFillColor(Color(245, 245, 255));
	pane.setOutlineColor(Color(220, 220, 255));
	pane.setOutlineThickness(2);
	pane.sP(pos);
	
	brightnessSpectrum.appendPt(pos + vecf(3, 303));
	brightnessSpectrum.appendPtC(pos + vecf(3, 3), Color::White);
	brightnessSpectrum.appendPt(pos + vecf(33, 303));
	brightnessSpectrum.appendPtC(pos + vecf(33, 3), Color::White);
	
	zimg.create(360 * 3, 300, Color::Transparent);
	tx.loadFromImage(zimg);
	refreshImage(100);
	colorsSprite.setTexture(tx);
	colorsSprite.sP(pos + vecf(brightnessSpectrum.getBounds().width + 6, 3));
	
	slider = Sprite(gTexture("sliderHandle"));
	centerOrigin(slider);
	slider.setRotation(90);
	slider.sP(brightnessSpectrum.getBounds().left + brightnessSpectrum.getBounds().width / 2,
			  brightnessSpectrum.getBounds().top);
	
	deactivate();
}

void ColorPicker::refreshImage (float brightness)
{
	if (brightness < 0)
		return;
	
	forNum (360) {
		forNumJ (100)  {
			Color c = hsbToRgb(i, j, clamp(brightness, 0.f, 100.f));
			zimg.setPixel(i * 3, j * 3, c);
			zimg.setPixel(i * 3, j * 3 + 1, c);
			zimg.setPixel(i * 3, j * 3 + 2, c);
			zimg.setPixel(i * 3 + 1, j * 3, c);
			zimg.setPixel(i * 3 + 1, j * 3 + 1, c);
			zimg.setPixel(i * 3 + 1, j * 3 + 2, c);
			zimg.setPixel(i * 3 + 2, j * 3, c);
			zimg.setPixel(i * 3 + 2, j * 3 + 1, c);
			zimg.setPixel(i * 3 + 2, j * 3 + 2, c);
		}
	}
	tx.update(zimg);
}

float ColorPicker::recalcBrightness (int x, int y, vecf cofs)
{
	auto val = min(updateSlider(x, y, cofs), 100.f);
	refreshImage(val);
	return val;
}

void ColorPicker::draw (RenderTarget &target, RenderStates states) const
{
	if (!isActive)
		return;
	target.draw(pane);
	target.draw(brightnessSpectrum);
	target.draw(colorsSprite);
	target.draw(slider);
}

void ColorPicker::moveAll (vecf newPos)
{
	vecf sliderDif = slider.gP() - pane.gP();
	vecf paletteDif = colorsSprite.gP() - pane.gP();
	pane.sP(newPos);
	slider.sP(newPos + sliderDif);
	colorsSprite.sP(newPos + paletteDif);
}

float ColorPicker::updateSlider (int x, int y, vecf cofs)
{
	float ret = -1.f;	// default return value means don't redraw palette
	auto oldPos = slider.gP();
	vecf newPos (oldPos.x, clamp(y + cofs.y, brightnessSpectrum.getBounds().top,
								 brightnessSpectrum.getBounds().top + brightnessSpectrum.getBounds().height));
	if (round(oldPos.y) != round(newPos.y)) {
		const auto& bs = brightnessSpectrum.getBounds();
		ret = ((bs.top + bs.height - newPos.y) / bs.height) * 100;
	}
	slider.sP(oldPos.x, newPos.y);
	return ret;
}

