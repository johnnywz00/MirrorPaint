//
//  AxisPicker.hpp
//  MirrorDraw
//
//  Created by John Ziegler on 2/21/26.
//  Copyright © 2026 John Ziegler. All rights reserved.
//

#ifndef AxisPicker_hpp
#define AxisPicker_hpp

#include "mirrorpaint.hpp"

class AxisPicker : public Drawable
{
public:
	struct RegionSelector
	{
		RegionSelector () { }
		
		RegionSelector (float ax, float degItvl, AxisPicker* parent, ClockDir cd=counterclockwise);
		
		void setPoints (vecf ogn);
		
		void refreshVA ();
		
		void setLines ();
		
		bool linesContain (float x, float y);
		
		float 			axis;
		float 			degInterval;
		ClockDir		clockDir = counterclockwise;
		VertexArray 	va {TriangleStrip};
		vector<Line>	lines;
		vector<vecf>	vxLocs;
		bool			isSelected = false;
	};
	
	struct AxisSelector
	{
		AxisSelector () { }
		
		AxisSelector (float deg, vecf pos);
		
		RectangleShape 	r;
		RegionSelector 	cw;
		RegionSelector 	ccw;
		float 			axis;
	};
	
	static constexpr float	axisLength = 200;

	AxisPicker () { }
	
	AxisPicker (vecf auxPos, float degInterval, State* app_);
	
	void deactivate ()
	{
		isActive = false;
		moveAll({-2000, -2000});
	}
	
	void activate ()
	{
		isActive = true;
		moveAll(finalPos);
	}
	
	void selectAxis (AxisSelector& a);
	
	void selectAll ();
	
	void selectRegion (RegionSelector& rs);
	
	void draw (RenderTarget& target, RenderStates states) const;
	
	void moveAll (vecf newPos)
	{
		pane.sP(newPos);
		for (auto& a : axes)
			a.r.sP(newPos);
	}
	
	RectangleShape			pane;
	CircleShape				allCircle;
	VertexArray				regionBoundaries {Lines};
	vector<AxisSelector>	axes;
	State*					app = nullptr;
	vecf					finalPos;
	bool					isActive = false;
};

#endif /* AxisPicker_hpp */
