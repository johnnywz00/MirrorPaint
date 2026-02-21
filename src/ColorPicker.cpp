//
//  ColorPicker.cpp
//  MirrorDraw
//
//  Created by John Ziegler on 2/21/26.
//  Copyright © 2026 John Ziegler. All rights reserved.
//

#include "mirrorpaint.hpp"

ColorPicker::ColorPicker (vecf pos, const Texture& tx)
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
	
	// inexplicable problems with img setting no colors: temp using State
	//		img.create(360 * 3, 300, Color::Black);
	//		forFloat(360) {
	//			forFloatJ(100) {
	//				Color c = randomColor(); //hsbToRgb(i, j, 100.f);//min(brightness, 100));
	//				img.setPixel(i * 3, j * 3, Color::Black);
	//				img.setPixel(i * 3, j * 3 + 1, c);
	//				img.setPixel(i * 3, j * 3 + 2, c);
	//				img.setPixel(i * 3 + 1, j * 3, c);
	//				img.setPixel(i * 3 + 1, j * 3 + 1, c);
	//				img.setPixel(i * 3 + 1, j * 3 + 2, c);
	//				img.setPixel(i * 3 + 2, j * 3, c);
	//				img.setPixel(i * 3 + 2, j * 3 + 1, c);
	//				img.setPixel(i * 3 + 2, j * 3 + 2, c);
	//			}
	//		}
	//		tx.loadFromImage(img);
	//		refreshImage(100);
	//		colorsSprite.setTexture(tx);
	colorsSprite.sP(pos + vecf(brightnessSpectrum.getBounds().width + 6, 3));
	
	slider = Sprite(tx);
	centerOrigin(slider);
	slider.sRot(90);
	slider.sP(brightnessSpectrum.getBounds().left + brightnessSpectrum.getBounds().width / 2,
			  brightnessSpectrum.getBounds().top);
	
	deactivate();
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

