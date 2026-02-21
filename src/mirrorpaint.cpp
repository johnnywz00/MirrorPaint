
#include "mirrorpaint.hpp"
#include "sfmlApp.hpp"


void State::onCreate ()
{
	toolPane.setSize(vecf(scrw, 90));
	toolPane.sP(0, scrh - 90);
	toolPane.setFillColor(Color(152, 173, 100));
	toolPane.setOutlineThickness(3);
	toolPane.setOutlineColor(DKAZURE75);

	gTexture("edges").setRepeated(true);
	auto wid = gTexture("edges").getSize().x;
	vector<Sprite*> edgeSprites {&rightEdge, &leftEdge, &topEdge, &bottomEdge, &toolPaneEdge};
	for (Sprite* spr : edgeSprites) {
		spr->setTexture(gTexture("edges"));
		spr->setTextureRect(IntRect(0, 0, wid, scrw));
	}
	rightEdge.sP(scrw - wid - 1, 0);
	topEdge.setOrigin(wid, 0);
	topEdge.sRot(270);
	bottomEdge.sRot(270);
	bottomEdge.sP(0, scrh);
	topEdge.setOrigin(wid, 0);
	toolPaneEdge.sRot(270);
	toolPaneEdge.sP(toolPane.gP());
	
	float toolPaneBottom = toolPaneEdge.gGB().top + toolPaneEdge.gGB().height;
	float toolPaneMidY = toolPaneBottom + (bottomEdge.gGB().top - toolPaneBottom) / 2;
	
	artistName = Text("", gFont("userName"), 24);
	artistName.setOutlineThickness(1);
	artistName.setOutlineColor(Color::Black);
	artistName.setFillColor(AZURE75);
	artistName.sP(scrw - 320, scrh - 50);
	
	float widgetX = 30;
	pinwheelSprite.setTexture(gTexture("pinwheel"));
	centerOrigin(pinwheelSprite);
	pinwheelSprite.sP(widgetX, toolPaneMidY);
	
	widgetX += 55;
	axisButton6.setSize(vecf(70, 70));
	centerOrigin(axisButton6);
	axisButton6.sP(widgetX, toolPaneMidY);
	axisButton6.setFillColor(Color(220, 220, 100));
	axisButton6.setOutlineThickness(2);
	axisButton6.setOutlineColor(DKORANGE);
	
	axis6Sprite.setTexture(gTexture("axis6"));
	centerOrigin(axis6Sprite);
	axis6Sprite.sP(axisButton6.gP());

	widgetX += 90;
	axisButton8.setSize(vecf(70, 70));
	centerOrigin(axisButton8);
	axisButton8.sP(widgetX, toolPaneMidY);
	axisButton8.setFillColor(Color(220, 220, 100));
	axisButton8.setOutlineThickness(2);
	axisButton8.setOutlineColor(DKORANGE);
	
	axis8Sprite.setTexture(gTexture("axis8"));
	centerOrigin(axis8Sprite);
	axis8Sprite.sP(axisButton8.gP());

	widgetX += 45;
	paletteButton.setSize(vecf(70, 45));
	paletteButton.sP(widgetX, toolPaneMidY - 38);
	paletteButton.setFillColor(drawColor);
	paletteButton.setOutlineThickness(2);
	paletteButton.setOutlineColor(DKORANGE);

	paletteSprite.setTexture(gTexture("palette"));
	centerOrigin(paletteSprite);
	paletteSprite.sP(widgetX + 35, toolPaneMidY);
	paletteSprite.setScale(.75, .75);

	bkgdColorButton.setSize(vecf(33, 30));
	bkgdColorButton.sP(widgetX, toolPaneMidY + 10);
	bkgdColorButton.setFillColor(app->redrawColor);
	bkgdColorButton.setOutlineThickness(2);
	bkgdColorButton.setOutlineColor(DKORANGE);

	widgetX += 37;
	outlineColorButton.setSize(vecf(33, 30));
	outlineColorButton.sP(widgetX, toolPaneMidY + 10);
	outlineColorButton.setFillColor(outlineColor);
	outlineColorButton.setOutlineThickness(2);
	outlineColorButton.setOutlineColor(DKORANGE);

	whichColorArrow.setTexture(gTexture("arrow"));
	whichColorArrow.setOrigin(whichColorArrow.gLB().width, whichColorArrow.gLB().height);
	whichColorArrow.setScale(.66, .66);
	whichColorArrow.sP(rectCenter(paletteButton));
	
		/* Brush buttons */
	float brbuttonPad = 4;
	float brbuttonSize = gTexture("regularBrush").getSize().x;
	float brbuttonScale = 1.25;
	widgetX = paletteButton.gGB().left + paletteButton.gGB().width + 				brbuttonPad + brbuttonSize * brbuttonScale / 2;
	
	brushButtons.emplace_back(gTexture("regularBrush"),
							  DrawingMode(regular, false),
							  vecf(widgetX, toolPaneMidY - brbuttonSize * brbuttonScale / 2 - brbuttonPad / 2));
	brushButtons.emplace_back(gTexture("inkyBrush"),
							  DrawingMode(inky, true),
							  vecf(widgetX, toolPaneMidY + brbuttonSize * brbuttonScale / 2 + brbuttonPad / 2));
	widgetX += brbuttonSize * brbuttonScale + brbuttonPad;
	brushButtons.emplace_back(gTexture("calligBrush"),
							  DrawingMode(calligraphy, false),
							  vecf(widgetX, toolPaneMidY - brbuttonSize * brbuttonScale / 2 - brbuttonPad / 2));
	brushButtons.emplace_back(gTexture("doubleOutline"),
							  DrawingMode(doubleOutline, false),
							  vecf(widgetX, toolPaneMidY + brbuttonSize * brbuttonScale / 2 + brbuttonPad / 2));
	widgetX += brbuttonSize * brbuttonScale + brbuttonPad;
	brushButtons.emplace_back(gTexture("circleRoll"),
							  DrawingMode(circleRoll, true),
							  vecf(widgetX, toolPaneMidY - brbuttonSize * brbuttonScale / 2 - brbuttonPad / 2));
	brushButtons.emplace_back(gTexture("triangleRoll"),
							  DrawingMode(triangleRoll, true),
							  vecf(widgetX, toolPaneMidY + brbuttonSize * brbuttonScale / 2 + brbuttonPad / 2));
	widgetX += brbuttonSize * brbuttonScale + brbuttonPad;
	brushButtons.emplace_back(gTexture("hexagonRoll"),
							  DrawingMode(hexagonRoll, true),
							  vecf(widgetX, toolPaneMidY - brbuttonSize * brbuttonScale / 2 - brbuttonPad / 2));
	brushButtons.emplace_back(gTexture("starRoll"),
							  DrawingMode(starRoll, true),
							  vecf(widgetX, toolPaneMidY + brbuttonSize * brbuttonScale / 2 + brbuttonPad / 2));
	widgetX += brbuttonSize * brbuttonScale + brbuttonPad;
	brushButtons.emplace_back(gTexture("bucket"),
							  DrawingMode(fill, false),
							  vecf(widgetX, toolPaneMidY - brbuttonSize * brbuttonScale / 2 - brbuttonPad / 2));
	brushButtons.emplace_back(gTexture("gradient"),
							  DrawingMode(gradientSpline, false),
							  vecf(widgetX, toolPaneMidY + brbuttonSize * brbuttonScale / 2 + brbuttonPad / 2));
	
	brButtonHilite.setSize(vecf(brushButtons[0].spr.gGB().width + 20, brushButtons[0].spr.gGB().width + 20));
	centerOrigin(brButtonHilite);
	brButtonHilite.sP(brushButtons[0].spr.gP());
	brButtonHilite.setFillColor(Color(0, 0, 0, 70));
	
	
	widgetX += brbuttonSize * brbuttonScale + brbuttonPad;
	thicknessIndicator.setSize({150, 3});
	thicknessIndicator.setOrigin(0, thicknessIndicator.gLB().height / 2);
	thicknessIndicator.sP(widgetX, toolPaneMidY);
	thicknessIndicator.setFillColor(Color::Black);
	
	float quarter = (bottomEdge.gGB().top - toolPaneBottom) / 4;
	sliders.emplace_back("lineThk", gTexture("sliderHandle"), vecf(widgetX, toolPaneBottom + quarter), .6, 40, 10,
						[&](float x) { lineThickness = x; });
	sliders.emplace_back("outlineThk", gTexture("sliderHandle"), vecf(widgetX, toolPaneBottom + 3 * quarter), 0, 20, 4,
						 [&](float x) { outlineThickness = x; });
	
	widgetX += sliders.back().track.getSize().x + 3 * brbuttonPad;
	sliders.emplace_back("colorDev", gTexture("sliderHandle"), vecf(widgetX, toolPaneBottom + quarter), 0, 150, 3,
						 [&](float x) { colorDev = x > 145 ? 255 : (uint)x; });
	
	clearScreenButton.setSize(vecf(70, 70));
	centerOrigin(clearScreenButton);
	clearScreenButton.sP(scrw - 60, toolPaneMidY);
	clearScreenButton.setFillColor(Color::White);
	clearScreenButton.setOutlineThickness(2);
	clearScreenButton.setOutlineColor(DKORANGE);

	saveButton.setSize(vecf(70, 70));
	centerOrigin(saveButton);
	saveButton.sP(scrw - 150, toolPaneMidY);
	saveButton.setFillColor(Color::Blue);
	saveButton.setOutlineThickness(2);
	saveButton.setOutlineColor(DKORANGE);
		
	float canvasHt = scrh - toolPane.gLB().height;
	canvOrigin = vecf(scrcx, canvasHt / 2);
	
//	rt.create(scrw, SCRH() - toolPane.gLB().height);
	rt.create(scrw, scrw); //EXPMT
	rt.clear(Color::Transparent);
//	permRt.create(scrw, SCRH() - toolPane.gLB().height);
	permRt.create(scrw, scrw); //EXPMT
	permRt.clear(Color::Transparent);

	canvasSprite.setTexture(rt.getTexture());
	centerOrigin(canvasSprite);
	canvasSprite.sP(canvOrigin);
	permCanvasSprite.setTexture(permRt.getTexture());
	centerOrigin(permCanvasSprite);
	permCanvasSprite.sP(canvOrigin);
	
	rtOffset = (scrw - canvasHt) / 2; //EXPMT
//	canvasSprite.setTextureRect(IntRect(0, rtOffset, scrw, canvasHt)); //EXPMT
//	permCanvasSprite.setTextureRect(IntRect(0, rtOffset, scrw, canvasHt)); //EXPMT

	colorPicker = ColorPicker({5, scrh - toolPane.gLB().height - 306}, gTexture("sliderHandle"));
	axis6Picker = AxisPicker({0, toolPane.gGB().top}, 60, this);
	axis8Picker = AxisPicker({0, toolPane.gGB().top}, 45, this);
	
	img.create(360 * 3, 300);
	tx.loadFromImage(img);
	refreshImage(100);
	colorPicker.colorsSprite.setTexture(tx);
	
	whichColorRect = &paletteButton;
	whichColor = &drawColor;
	
	
	reset();
}

bool State::handleTextEvent (Event& event)
{
	if (activeTbox
		&& (event.type == Event::TextEntered
			|| event.type == Event::KeyPressed
			|| event.type == Event::KeyReleased)) {
		if (event.type == Event::TextEntered) {
			if (event.text.unicode == 8)
				if (iKP(LShift))
					activeTbox->clear();
				else activeTbox->deleteLastChar();
				else if (event.text.unicode == 9) ; // Don't write the \t
				else activeTbox->appendText(event.text.unicode);
		}
		if (event.type == Event::KeyPressed
			&& (event.key.code == Keyboard::Escape || event.key.code == Keyboard::Enter)) {
			activeTbox->setActive(false);
			activeTbox = nullptr;
		}
		return true;
	}
	return false;
}


void State::reset ()
{
	drawing = false;
	lastPts.clear();
	activeRegions.clear();
	colorPicker.isActive = false;
	draggingSlider = nullptr;
	
		// ideally add picker regions as being selected from start
	for (float i : {0, 45, 90, 135, 180, 225, 270, 315}) {
		DrawRegion dr {i, clockwise};
		DrawRegion dr2 {i};
		activeRegions.push_back(dr);
		activeRegions.push_back(dr2);
	}
	
}


void State::draw ()
{
	auto w = rwin;
	w->draw(permCanvasSprite);
	w->draw(canvasSprite);
	
	if (!drawing && !draggingSlider)
		for (auto& ar : activeRegions)
			w->draw(ar.ghost);
	
	w->draw(toolPane);
	w->draw(brButtonHilite);
	w->draw(toolPaneEdge);
	w->draw(bottomEdge);
	w->draw(leftEdge);
	w->draw(rightEdge);
	w->draw(topEdge);
	
	w->draw(pinwheelSprite);
	w->draw(axisButton6);
	w->draw(axisButton8);
	w->draw(axis6Sprite);
	w->draw(axis8Sprite);
	
	w->draw(paletteButton);
	w->draw(bkgdColorButton);
	w->draw(outlineColorButton);
	w->draw(paletteSprite);
	w->draw(whichColorArrow);
	
	for (auto& bb : brushButtons)
		w->draw(bb.spr);
	
	w->draw(clearScreenButton);
	w->draw(saveButton);
	w->draw(artistName);
	
	w->draw(colorPicker);
	w->draw(axis6Picker);
	w->draw(axis8Picker);

	for (auto& slid : sliders)
		w->draw(slid);
}


void State::onMouseDown (int x, int y)
{
	if (colorPicker.slider.gGB().contains(x, y)) {
		draggingSlider = &colorPicker.slider;
		clickOffset = colorPicker.slider.gP() - vecf(x, y);
	}
	
	else if (colorPicker.isActive && colorPicker.brightnessSpectrum.getBounds().contains(x, y)) {
		recalcBrightness(x, y, {0, 0});
	}
	
	else if (colorPicker.colorsSprite.gGB().contains(x, y)) {
		*(whichColor) = colorPicker.getColorAt(x, y, curBrightness);
		whichColorRect->setFillColor(*(whichColor));
		
//		r2.setFillColor(Color(drawColor.r, drawColor.g, drawColor.b, 160));
	}
	
	else if (colorPicker.pane.gGB().contains(x, y))
		; // don't draw on canvas
	
	else if (axis6Picker.pane.gGB().contains(x, y)) {
		if (hyp(axis6Picker.allCircle.gP(), vecf(x, y)) < axis6Picker.allCircle.getRadius())
			axis6Picker.selectAll();
		else {
			for (auto& a : axis6Picker.axes) {
				if (rotatedContains(a.r, x, y)) {
					axis6Picker.selectAxis(a);
					break;
				}
				else if (a.cw.linesContain(x, y)) {
					a.cw.isSelected = !a.cw.isSelected;
					axis6Picker.selectRegion(a.cw);
					break;
				}
				else if (a.ccw.linesContain(x, y)) {
					a.ccw.isSelected = !a.ccw.isSelected;
					axis6Picker.selectRegion(a.ccw);
					break;
				}
			}
		}
	}

	
	else if (axis8Picker.pane.gGB().contains(x, y)) {
		if (hyp(axis8Picker.allCircle.gP(), vecf(x, y)) < 	axis8Picker.allCircle.getRadius())
			axis8Picker.selectAll();
		else {
			for (auto& a : axis8Picker.axes) {
				if (rotatedContains(a.r, x, y)) {
					axis8Picker.selectAxis(a);
					break;
				}
				else if (a.cw.linesContain(x, y)) {
					a.cw.isSelected = !a.cw.isSelected;
					axis8Picker.selectRegion(a.cw);
					break;
				}
				else if (a.ccw.linesContain(x, y)) {
					a.ccw.isSelected = !a.ccw.isSelected;
					axis8Picker.selectRegion(a.ccw);
					break;
				}
			}
		}
	}

	else if (clearScreenButton.gGB().contains(x, y))
		clearCanvas();

	else if (saveButton.gGB().contains(x, y))
		saveCanvasToDiskFile();
	
	else if (paletteButton.gGB().contains(x, y)) {
		bool wasActive = colorPicker.isActive && whichColorRect == &paletteButton;
		deactivateAll();
		if (!wasActive)
			colorPicker.activate();
		whichColorArrow.sP(rectCenter(paletteButton));
		whichColor = &drawColor;
		whichColorRect = &paletteButton;
	}

	else if (bkgdColorButton.gGB().contains(x, y)) {
		bool wasActive = colorPicker.isActive && whichColorRect == &bkgdColorButton;
		deactivateAll();
		if (!wasActive)
			colorPicker.activate();
		whichColorArrow.sP(rectCenter(bkgdColorButton));
		whichColor = &app->redrawColor;
		whichColorRect = &bkgdColorButton;
	}

	else if (outlineColorButton.gGB().contains(x, y)) {
		bool wasActive = colorPicker.isActive && whichColorRect == &outlineColorButton;
		deactivateAll();
		if (!wasActive)
			colorPicker.activate();
		whichColorArrow.sP(rectCenter(outlineColorButton));
		whichColor = &outlineColor;
		whichColorRect = &outlineColorButton;
	}

	else if (pinwheelSprite.gGB().contains(x, y)) {
		deactivateAll();
		activeRegions.clear();
		for (float i = 0; i < 360; i += 360 / 12) {
			DrawRegion dr {i, clockwise};
			activeRegions.push_back(dr);
		}
	}
	
	else if (axisButton6.gGB().contains(x, y)) {
		bool wasActive = axis6Picker.isActive;
		deactivateAll();
		if (!wasActive) {
			axis6Picker.activate();
			activeRegions.clear();
			reloadRegions(axis6Picker);
		}
	}

	else if (axisButton8.gGB().contains(x, y)) {
		bool wasActive = axis8Picker.isActive;
		deactivateAll();
		if (!wasActive) {
			axis8Picker.activate();
			activeRegions.clear();
			reloadRegions(axis8Picker);
		}
	}
	
	else if (checkSlidersForClick(x, y))
		;  /* Handled in if clause */
	
	else if (checkBrushButtonsForClick(x, y))
		; /* Handled in if clause */
	
	else if (toolPane.gGB().contains(x, y) ||
			 toolPaneEdge.gGB().contains(x, y))
		; /* Do nothing */
	
	else if (canvasSprite.gGB().contains(x, y))
		startStroke(float(x), float(y));
	
}

bool State::checkSlidersForClick (int x, int y)
{
	for (auto& sl : sliders) {
		if (sl.handle.gGB().contains(x, y)) {
			draggingSlider = &(sl.handle);
			clickOffset = sl.handle.gP() - vecf(x, y);
			return true;
		}
	}
	return false;
}

bool State::checkBrushButtonsForClick (int x, int y)
{
	for (auto& bb : brushButtons) {
		if (bb.spr.gGB().contains(x, y)) {
			brButtonHilite.sP(bb.spr.gP());
			curMode = bb.mode;
			return true;
		}
	}
	return false;
}

void State::onMouseUp (int x, int y)
{
	if (drawing && curMode.type == gradientSpline)
		paintGradientSpline(
							true
							);
	drawing = false;
	draggingSlider = nullptr;
}


void State::onKeyPress(Keyboard::Key k)
{
	Sprite* spr;
	switch(k) {
		case Keyboard::Escape:
			if (iKP(LShift))
				clearCanvas();
			else app->close();
			break;
		case Keyboard::LShift:
			chooseCanvasColor = true;
			break;
		case Keyboard::LAlt:
			chooseSecondaryColor = true;
			break;
		case Keyboard::Space:
			colorPicker.deactivate();
			axis6Picker.deactivate();
			axis8Picker.deactivate();
			break;
		case Keyboard::L:
			artistName.setString("Laith");
			break;
		case Keyboard::R:
			if (iKP(LShift)) {
				clearCanvas();
				Texture tx_;
//				tx_.loadFromFile("/Users/johnwz/Desktop/rebekah.png");
				tx_.loadFromFile("/Users/johnwz/Desktop/Mirror Pics/13862201567504068.png");
				Sprite s_{tx_};
				permRtDraw(s_);
				permRt.display();
			}
			else artistName.setString("Ravenna");
			break;
		case Keyboard::Backspace:
			artistName.setString("");
			break;
		case Keyboard::Z:
			rt.clear(Color::Transparent);  // "undo"
			break;
		case Keyboard::Tilde:
			static bool which = true;
			which = !which;
			spr = &(sliders[indexWhich(sliders, [&](auto x){ return x.name == "colorDev";})].handle);
			if (which) {
				colorDevFunc = &colorDevLockHue;
				spr->setColor(Color::White);
			}
			else {
				colorDevFunc = &colorWithRandDeviation;
				spr->setColor(Color::Blue);
			}
			break;
		default:
			break;
	}
}


void State::onKeyRelease(Keyboard::Key k)
{
	switch(k) {
		case Keyboard::LShift:
			chooseCanvasColor = false;
			break;
		case Keyboard::LAlt:
			chooseSecondaryColor = false;
			break;
		default:
			break;
	}
}

void State::reloadRegions (AxisPicker& ap)
{
	activeRegions.clear();
	for (auto& a : ap.axes) {
		if (a.cw.isSelected)
			activeRegions.push_back(DrawRegion(a.cw.axis, a.cw.clockDir));
		if (a.ccw.isSelected)
			activeRegions.push_back(DrawRegion(a.ccw.axis, a.ccw.clockDir));
	}

}

void State::clearCanvas ()
{
	rt.clear(Color::Transparent);
	permRt.clear(Color::Transparent);
}

void State::saveCanvasToDiskFile ()
{
	RenderTexture temp;
	temp.create(rt.getSize().x, rt.getSize().y);
	temp.clear(app->redrawColor);
	Sprite s {permRt.getTexture()};
	temp.draw(s);
	s.setTexture(rt.getTexture());
	temp.draw(s);
	string folderName = artistName.getString() == "Laith" ? "Laith Mirrors/" : artistName.getString() == "Ravenna" ? "Ravenna Mirrors/" : "";
	string fname = "/Users/johnwz/Desktop/" + folderName + tS(saveID++) + tS(int(lineThickness)) + tS(int(curBrightness)) + tS(int(drawColor.r)) + tS(rand()) + ".png";
	temp.getTexture().copyToImage().saveToFile(fname);
	gSound("save").play();
}

void State::startStroke (float x, float y)
{
	permRtDraw(canvasSprite);
	permRt.display();
	rt.clear(Color::Transparent);
	
//	lastPts = getMirroredPts(x, y + rtOffset); //EXPMT
	lastPts = getMirroredPts(x, y);
	
	if (curMode.type == fill)
		fillArea(lastPts);
	else drawing = true;
	
	if (curMode.type == gradientSpline) {
		splinePts.clear();
		splinePts.emplace_back(x, y);
		lastDrawLoc = {x, y};
	}
	else
		lastDrawLoc = {-1000, -1000};
}

void State::continueStroke ()
{
	if (curMode.isPeriodic)
		periodicDraw();
	else if (curMode.type == fill)
		return;
	else if (curMode.type == gradientSpline)
		splineDraw();
	else brushDraw();
}

void State::fillArea (vector<vecf> pts)
{
	Image temp {permRt.getTexture().copyToImage()};
	ZImage im {temp};
	for (auto& p : pts) {
		im.fillInWithColor(vecU(p.x, p.y + rtOffset), drawColor, colorDev);
	}
	Texture t;
	t.loadFromImage(im);
	Sprite s {t};
	
	rtDraw(s, false);
	rt.display();
}

void State::splineDraw()
{
	vecf curPos {float(mouseVec.x), float(mouseVec.y)};
	if (hyp(curPos, lastDrawLoc) > splinePeriodSize) {
		auto newPts = getMirroredPts(curPos.x, curPos.y);
		forNum(newPts.size()) {
			auto end = newPts[i];
			auto start = lastPts[i];
			auto pdif = toPolar(end - start);
			RectangleShape r;
			r.setSize({pdif.x, 3});
			r.setOrigin(0,1);
			r.setPosition(start);
			r.setFillColor(drawColor);
			r.setRotation(pdif.y);
			rtDraw(r);
		}
		rt.display();
		splinePts.push_back(curPos);
		lastDrawLoc = curPos;
		lastPts = newPts;
	}
}

void State::paintGradientSpline(bool symmetric)
{
	vector<LineSegment> segs;
	forNum(splinePts.size() - 1) {
		segs.emplace_back(splinePts[i], splinePts[i + 1]);
	}
	float halfThick = lineThickness / 2;
	forNum(segs.size()) {
		float prevAngle = i == 0 ? segs[i].angle : bisectSmallest(segs[i].angle, segs[i - 1].angle);
		float nextAngle = i == segs.size() - 1 ? segs[i].angle : bisectSmallest(segs[i].angle, segs[i + 1].angle);
		auto brPts = getMirroredPts(segs[i].pt1
									+ pVec(halfThick, prevAngle + 90));
		auto blPts = getMirroredPts(segs[i].pt1
									+ pVec(halfThick, prevAngle + 270));
		auto trPts = getMirroredPts(segs[i].pt2
									+ pVec(halfThick, nextAngle + 90));
		auto tlPts = getMirroredPts(segs[i].pt2
									+ pVec(halfThick, nextAngle + 270));
									
		auto startPts = getMirroredPts(segs[i].pt1);
		auto endPts = getMirroredPts(segs[i].pt2);
		forNum(brPts.size()) {
			if (symmetric) {
				TransformableVxArray va {TriangleStrip};
				va.appendPtC(startPts[i], drawColor);
				va.appendPtC(blPts[i], outlineColor);
				va.appendPtC(endPts[i], drawColor);
				va.appendPtC(tlPts[i], outlineColor);
				va.configure();
				rtDraw(va);
				TransformableVxArray va2 {TriangleStrip};
				va2.appendPtC(startPts[i], drawColor);
				va2.appendPtC(brPts[i], outlineColor);
				va2.appendPtC(endPts[i], drawColor);
				va2.appendPtC(trPts[i], outlineColor);
				va2.configure();
				rtDraw(va2);
			}
			else {
				TransformableVxArray va {TriangleStrip};
				va.appendPtC(brPts[i], drawColor);
				va.appendPtC(blPts[i], outlineColor);
				va.appendPtC(trPts[i], drawColor);
				va.appendPtC(tlPts[i], outlineColor);
				va.configure();
				rtDraw(va);
			}
		}
	}
	rt.display();
}

void State::periodicDraw ()
{
	periodSize = lineThickness;
	
	if (curMode.type == inky)
		periodSize *= .3;
	
	if (hyp(vecf(mouseVec.x, mouseVec.y), lastDrawLoc) > periodSize) {
		auto newPts = getMirroredPts(mouseVec.x, mouseVec.y);
		vecf curPos = {float(mouseVec.x), float(mouseVec.y)};
//	if (hyp(vecf(mx, my + rtOffset), lastDrawLoc) > periodSize) { //EXPMT
//		auto newPts = getMirroredPts(mx, my + rtOffset); //EXPMT
//		vecf curPos = {float(mx), float(my + rtOffset)}; //EXPMT
		Color devColor = colorDevFunc(drawColor, colorDev);
		forNum(newPts.size()) {
			if (curMode.type == starRoll) {
				StarShape t;
				t.setSize({lineThickness, lineThickness / 2.2f});
				t.setFillColor(devColor);
				t.setOutlineThickness(outlineThickness);
				t.setOutlineColor(outlineColor);
				t.setRotation(toPolar(newPts[i] - lastPts[i]).y);
				centerOrigin(t);
				t.sP(newPts[i]);
				rtDraw(t);
			}
			else if (curMode.type == hexagonRoll) {
				HexagonShape t;
				t.setSize({lineThickness, lineThickness});
				t.setFillColor(devColor);
				t.setOutlineThickness(outlineThickness);
				t.setOutlineColor(outlineColor);
				t.setRotation(toPolar(newPts[i] - lastPts[i]).y);
				centerOrigin(t);
				t.sP(newPts[i]);
				rtDraw(t);
			}
			else if (curMode.type == triangleRoll) {
				TriangleShape t;
				t.setSize({lineThickness, lineThickness});
				t.setFillColor(devColor);
				t.setOutlineThickness(outlineThickness);
				t.setOutlineColor(outlineColor);
				t.setRotation(toPolar(newPts[i] - lastPts[i]).y);
				centerOrigin(t);
				t.sP(newPts[i]);
				rtDraw(t);
			}
			else if (curMode.type == circleRoll) {
				CircleShape t;
				t.setRadius(lineThickness / 2);
				t.setFillColor(devColor);
				t.setOutlineThickness(outlineThickness);
				t.setOutlineColor(outlineColor);
				centerOrigin(t);
				t.sP(newPts[i]);
				rtDraw(t);
			}
			else if (curMode.type == inky) {
				CircleShape t;
				t.setRadius(lineThickness / 2);
				centerOrigin(t);
				t.setFillColor(devColor);
				t.setScale(randFloat(.5, 1.5), randFloat(.5, 1.5));
				t.sP(newPts[i]);
				rtDraw(t);
			}
		}
		rt.display();
		lastDrawLoc = curPos;
		lastPts = newPts;
	}
}

void State::brushDraw ()
{
//	auto newPts = getMirroredPts(mx, my + rtOffset); //EXPMT
	auto newPts = getMirroredPts(mouseVec.x, mouseVec.y);
	Color col = colorDevFunc(drawColor, colorDev);
	forNum(newPts.size()) {
		
		if (curMode.type == calligraphy) {
			RectangleShape r;
			r.setSize({lineThickness, lineThickness * 7});
			r.setOrigin(0, r.gLB().height / 2);
			r.setFillColor(col);
			r.setRotation(czdg(315 + activeRegions[i].axisAngle + (activeRegions[i].dirFromAxis == clockwise ? -90 : 0)));
			auto dif = newPts[i] - lastPts[i];
			auto h = ceil(hyp(dif));
			for (float x = 1; x < h; ++x) {
				r.sP(lastPts[i] + x / h * dif);
				rtDraw(r);
			}
			r.sP(newPts[i]);
			rtDraw(r);
		}
		
		else {
			RectangleShape r;
			CircleShape c;
			auto pdif = toPolar(newPts[i] - lastPts[i]);
			
			r.setFillColor(col);
			r.setSize({pdif.x, lineThickness});
			r.setOrigin(0, r.gLB().height / 2);
			r.sP(lastPts[i]);
			r.setRotation(pdif.y);
			rtDraw(r);
			
			c.setRadius(lineThickness / 2);
			c.setFillColor(col);
			centerOrigin(c);
			c.sP(lastPts[i]);
			rtDraw(c);
			c.sP(newPts[i]);
			rtDraw(c);
			
			if (curMode.type == doubleOutline) {
				Color col2 = colorDevFunc(outlineColor, colorDev);
				vecf dif1 = toRect(((lineThickness + outlineThickness) * .5) - 1, pdif.y + 90);
				vecf dif2 = toRect(((lineThickness + outlineThickness) * .5) - 1, pdif.y + 270);
				
				c.setFillColor(col2);
				c.setRadius(outlineThickness / 2);
				centerOrigin(c);
				c.sP(lastPts[i] + dif1);
				rtDraw(c);
				c.sP(lastPts[i] + dif2);
				rtDraw(c);
				c.sP(newPts[i] + dif1);
				rtDraw(c);
				c.sP(newPts[i] + dif2);
				rtDraw(c);
				
				r.setFillColor(col2);
				r.setSize({pdif.x, outlineThickness});
				r.setOrigin(0, r.gLB().height / 2);
				r.setRotation(pdif.y); //
				r.sP(lastPts[i] + dif1);
				rtDraw(r);
				r.sP(lastPts[i] + dif2);
				rtDraw(r);
			}

		}
	}
	rt.display();
	lastPts = newPts;
}

vector<vecf> State::getMirroredPts (float x, float y)
{
	vector<vecf> pts;
	vecf controlPt {x, y};
//	vecf ctlDif {controlPt - vecf(canvOrigin.x, canvOrigin.y + rtOffset)}; //EXPMT
	vecf ctlDif {controlPt - canvOrigin};
	vecf curPDif = toPolar(ctlDif);
	for (auto& ar : activeRegions) {
//		pts.push_back(ar.derivePt(curPDif.x, curPDif.y + 90) + vecf(canvOrigin.x, canvOrigin.y + rtOffset)); //EXPMT
		pts.push_back(ar.derivePt(curPDif.x, curPDif.y + 90) + canvOrigin);
	}
	return pts;
}

void State::update (const Time& time)
{
	timedMgr->fireReadyEvents(time);
	
	//ikp
	
	if (drawing) {
		continueStroke();
	}
	
	else if (draggingSlider == &colorPicker.slider) {
		recalcBrightness(mouseVec.x, mouseVec.y, clickOffset);
	}
	
	else if (draggingSlider) {
		int idx = -1;
		forNum(sliders.size()) {
			if (&(sliders[i].handle) == draggingSlider)
				idx = i;
		}
		if (idx != -1) {
			Slider& sl = sliders[idx];
			auto& track = sl.track;
			auto& hdl = sl.handle;
			hdl.sP(clamp(mouseVec.x + clickOffset.x, track.gP().x, track.gGB().left + track.gGB().width),
				   hdl.gP().y);
			sl.curVal = ((hdl.gP().x - track.gP().x) / track.gGB().width) * (sl.maxVal - sl.minVal) + sl.minVal;
			sl.func(sl.curVal);
			if (sl.name != "colorDev")
				track.setScale(1, max(.333f, sl.curVal / 3));
		}
	}
	
	else {
		auto pts = getMirroredPts(mouseVec.x, mouseVec.y);
		forNum(pts.size()) {
			activeRegions[i].ghost.sP(pts[i]);
		}
	}
	
	// DEBUG/TESTING
//	mouseTxt.setString(tS(mx) + ", " + tS(my));
//	debugTxt.setString(
//					   );
	
} //end update
