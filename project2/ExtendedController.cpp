// ExtendedController.c++

#include "ExtendedController.h"
#include "ModelView.h"

ExtendedController::ExtendedController(const std::string& name, int rcFlags):
	GLFWController(name, rcFlags)
{
}

void ExtendedController::handleMouseMotion(int x, int y)
{
	// get a pixel (dx, dy)
	float dx = x - screenBaseX;
	float dy = y - screenBaseY;

	// update Controller::screenBaseX, Controller::screenBaseY
	screenBaseX = x;
	screenBaseY = y;
	
	// if translation, map (dx, dy) to (dxInLDS, dyInLDS) and pass to
	// ModelView::addToGlobalPan
	if (mouseMotionIsTranslate)
	{
		double ldsX, ldsY;
		pixelPointToLDSPoint(x, y, ldsX, ldsY);
		float dxInLDS = x;
		float dyInLDS = y;
		float dzInLDS = 0;
		ModelView::addToGlobalPan(dxInLDS, dyInLDS, dzInLDS);
	}
	
	// else if rotation, map (dx, dy) to rotation angles and pass to
	// ModelView::addToGlobalRotationDegrees.
	else if (mouseMotionIsRotate)
	{
		float rx = dx;
		float ry = dy;
		float rz = 0;
		ModelView::addToGlobalRotationDegrees(rx, ry, rz);
	}
	
	// do a redraw()
	redraw();
}
