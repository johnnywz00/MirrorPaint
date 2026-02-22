//
//  AxisPicker.cpp
//  MirrorDraw
//
//  Created by John Ziegler on 2/21/26.
//  Copyright © 2026 John Ziegler. All rights reserved.
//

#include "mirrorpaint.hpp"

AxisPicker::RegionSelector::RegionSelector (float ax, float degItvl, AxisPicker* parent, ClockDir cd)
	: axis(ax)
	, degInterval(degItvl)
	, clockDir(cd)
{
	setPoints(parent->finalPos);
	setLines();
}

void AxisPicker::RegionSelector::setPoints (vecf ogn)
{
	vxLocs.clear();
	vxLocs.push_back(ogn);
	vxLocs.push_back(ogn + toRect(axisLength, axis));
	vxLocs.push_back(ogn + toRect(axisLength, clockDir == clockwise ? axis + degInterval / 2 : axis - degInterval / 2));
	refreshVA();
}

void AxisPicker::RegionSelector::refreshVA ()
{
	va.clear();
	for (auto& pt : vxLocs)
		va.appendPtC(pt, isSelected ? SKYBLUE : (int(axis) == 270 && clockDir == clockwise) ? Color(240, 240, 240) : Color::White);
}

void AxisPicker::RegionSelector::setLines ()
{
	lines.push_back(Line(vxLocs[0], vxLocs[1]));
	lines.push_back(Line(vxLocs[1], vxLocs[2]));
	lines.push_back(Line(vxLocs[2], vxLocs[0]));
}

bool AxisPicker::RegionSelector::linesContain (float x, float y)
{
	for (auto& l : lines) {
		vecf pdif = toPolar(vecf(x, y) - l.pt1);
		if (clockDir == clockwise) {
			if (!clockwiseOf(pdif.y, l.angle))
				return false;
		}
		else {
			if (clockwiseOf(pdif.y, l.angle))
				return false;
		}
	}
	return true;
}

AxisPicker::AxisSelector::AxisSelector (float deg, vecf pos)
{
	axis = czdg(deg);
	r.setSize({axisLength, 8});
	r.setOrigin(0, r.gLB().height / 2);
	r.setFillColor(Color(0, 0, 30));
	r.sP(pos);
	r.setRotation(axis);
}

AxisPicker::AxisPicker (vecf auxPos, float degInterval, State* app_)
	: app(app_)
{
	pane.setSize({axisLength * 2 + 4, axisLength * 2 + 4});
	pane.setFillColor(Color(245, 245, 255));
	pane.setOutlineColor(Color(220, 220, 255));
	pane.setOutlineThickness(2);
	pane.setOrigin(pane.gLB().width / 2, pane.gLB().height / 2);
	pane.sP(auxPos.x + pane.gLB().width / 2, auxPos.y - pane.gLB().height / 2);
	finalPos = pane.gP();
	
	allCircle.setRadius(15);
	centerOrigin(allCircle);
	allCircle.setOutlineColor(Color(0, 0, 30));
	allCircle.setOutlineThickness(2);
	allCircle.setFillColor(Color(100, 95, 150));
	allCircle.sP(finalPos);
	
	axes.clear();
	for (float d = 90; d < 450; d += degInterval) {
		AxisSelector as {d, finalPos};
		RegionSelector rs {czdg(d), degInterval, this};
		as.ccw = rs;
		rs = {czdg(d), degInterval, this, clockwise};
		as.cw = rs;
		axes.push_back(as);
		
		regionBoundaries.appendPtC(finalPos, Color(200, 200, 200));
		regionBoundaries.appendPtC(finalPos + toRect(axisLength, d - degInterval / 2), Color(200, 200, 200));
	}
	
	deactivate();
}

void AxisPicker::selectAxis (AxisSelector& a)
{
	if (a.cw.isSelected && a.ccw.isSelected) {
		a.cw.isSelected = false;
		a.ccw.isSelected = false;
	}
	else {
		a.cw.isSelected = true;
		a.ccw.isSelected = true;
	}
	selectRegion(a.cw);
	selectRegion(a.ccw);
}

void AxisPicker::selectAll ()
{
	vector<RegionSelector*> rss;
	for (auto& a : axes) {
		rss.push_back(&a.cw);
		rss.push_back(&a.ccw);
	}
	bool shouldSelect = indexWhich(rss, [&](auto x){ return !x->isSelected; }) != -1;
	for (auto& r : rss) {
		r->isSelected = shouldSelect;
		selectRegion(*r);
	}
}

void AxisPicker::selectRegion (RegionSelector& rs)
{
	auto itr = std::find_if(app->activeRegions.begin(), app->activeRegions.end(),
							[&](auto& ele) { return round(ele.axisAngle) == round(rs.axis) && ele.dirFromAxis == rs.clockDir; });
	if (rs.isSelected) {
		if (itr == app->activeRegions.end())
			app->activeRegions.push_back(DrawRegion(rs.axis, rs.clockDir));
	}
	else {
		if (itr != app->activeRegions.end())
			app->activeRegions.erase(itr);
	}
	rs.refreshVA();
}

void AxisPicker::draw (RenderTarget& target, RenderStates states) const
{
	if (!isActive)
		return;
	target.draw(pane);
	for (auto& a : axes) {
		target.draw(a.cw.va);
		target.draw(a.ccw.va);
		target.draw(a.r);
	}
	target.draw(allCircle);
	target.draw(regionBoundaries);
}
