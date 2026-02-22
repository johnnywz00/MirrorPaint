/*
 - textbox for reloading pics to work on
 - more undo layers
 - periodic squares
 - thumbnails of mirrors could be stuck together to make tile art
 - colordev func that stores the last val used and stays within a range of it (static stored in the func)

 - hexagons are not centered/symmetric
 
 * make splineDraw work properly with bisections

 - auto paint/randmotion
 - HeartShape
 - bulldozers/roll stamp drawing
 - center orig of callig?
 - textbox for pinwheel arms
 - pixel blend option

 //effects like twined strings could be accomplished by drawing a temporary one-pix line for the duration of a stroke, and rendering the twines after the stroke has finished. same for the original idea of brush editor/pixels in a line, and other forms of periodic custom brushes
 */

#ifndef MIRRORDRAW_H
#define MIRRORDRAW_H

#include "jwzsfml.hpp"
#include "timedeventmanager.hpp"
#include "resourcemanager.hpp"

class FullscreenOnlyApp;
class State;

#include "editorcomponents.hpp"
#include "ColorPicker.hpp"
#include "AxisPicker.hpp"


class State
{
public:
	void onCreate ();
	
	bool handleTextEvent (Event& event);
	
	void onMouseDown (int x, int y);
	
	void onMouseUp (int x, int y);
	
	void onKeyPress (Keyboard::Key);
	
	void onKeyRelease (Keyboard::Key);
	
	void update (const Time& time);
	
	void draw ();
	
	FullscreenOnlyApp* 		app;
	RenderWindow*  		 	rwin;
	TimedEventManager*  	timedMgr;
	vecI					mouseVec
							, oldMouse
	;
	vector<DrawRegion>		activeRegions;	// by AxisPicker

private:
	static constexpr float	splinePeriodSize = 6;

	void reset();

	void reloadRegions (AxisPicker&);
	
	bool checkSlidersForClick (int x, int y);
	
	bool checkBrushButtonsForClick (int x, int y);
	
	void deactivateAll ()
	{
		colorPicker.deactivate();
		axis6Picker.deactivate();
		axis8Picker.deactivate();
	}
	
	void setBrushThickness (float thk) { lineThickness = thk; }
	
	void setOutlineThickness (float thk) { outlineThickness = thk; }
	
	void setColorDev (float dev) { colorDev = dev; }
	
	void toggleColorDevFunc ();
	
	vector<vecf> getMirroredPts (float x, float y);
	vector<vecf> getMirroredPts (const vecf& v) { return getMirroredPts(v.x, v.y); }

	void startStroke (float x, float y);
	
	void continueStroke ();
	
	void brushDraw ();
	
	void periodicDraw ();
	
	void splineDraw ();
	
	void paintGradientSpline(bool symm = false);
	
	void fillArea (vector<vecf>);
	
	void rtDraw (Shape& d)
	{
		d.move(0, rtOffset);
		rt.draw(d);
	}
	
	void rtDraw (Sprite& d, bool doMove = true)
	{
		if (doMove)
			d.move(0, rtOffset);
		rt.draw(d);
	}
	
	void rtDraw (TransformableVxArray& va)
	{
		va.move(0, rtOffset);
		rt.draw(va);
	}
	
	void permRtDraw (Sprite& d)
	{
		d.move(0, rtOffset);
		permRt.draw(d);
		d.move(0, -rtOffset);
	}
	
	void clearCanvas ();
	
	void saveCanvasToDiskFile();
		

	ColorPicker				colorPicker;
	AxisPicker				axis6Picker
							, axis8Picker
	;
	Sprite					canvasSprite
							, permCanvasSprite
							, pinwheelSprite
							, axis6Sprite
							, axis8Sprite
							, paletteSprite
							, saveSprite
							, leftEdge
							, rightEdge
							, topEdge
							, bottomEdge
							, toolPaneEdge
	;
	RectangleShape			toolPane
							, axisButton6
							, axisButton8
							, paletteButton
							, clearScreenButton
							, brButtonHilite
							, bkgdColorButton
							, outlineColorButton
	;
	vector<BrushButton>		brushButtons;
	vector<Slider>			sliders;
	Text					artistName
							, clearBtnTxt
	;
	
	RectangleShape*			whichColorRect;
	Sprite					whichColorArrow;
	Color*					whichColor;
	
	RenderTexture			rt
							, permRt
	;
	Image					rtImg;

	DrawingMode				curMode {regular, false};
	Sprite*					draggingSlider = nullptr;
	Textbox*				activeTbox = nullptr;
	function<Color(Color&, int)>
							colorDevFunc = &colorDevLockHue;
	Color					drawColor = ORANGE75
							, outlineColor = AZURE;
	;
	
	vector<vecf>			lastPts;
	vector<vecf>			splinePts;
	vecf					lastDrawLoc;
	vecf 					canvOrigin;
	vecf					clickOffset;
	//	float 					lastSplineAng;
	float					periodSize = 8;
	float 					rtOffset = 0;
	float					lineThickness = 10;
	float					outlineThickness = 5;
	float 					curBrightness = 100;
	uint					saveID = 1;
	uint 					colorDev = 3;
	bool					drawing;
}; //end class State

#endif




