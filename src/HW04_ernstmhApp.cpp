#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_ernstmhApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void HW04_ernstmhApp::setup()
{
	//work
}

void HW04_ernstmhApp::mouseDown( MouseEvent event )
{
}

void HW04_ernstmhApp::update()
{
}

void HW04_ernstmhApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( HW04_ernstmhApp, RendererGl )
