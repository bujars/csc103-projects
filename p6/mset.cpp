#include <QtGui>
#include "mset.h"

// for our timer function:
#include <time.h>
#include <inttypes.h>

// for debugging:
#include <iostream>
using std::cout;
using std::endl;


// hack: keep a variable to let us know if the application
// has been initialized so that we can draw the set on startup
bool drawnYet = false;


// In case you want to time your routines, the following function
// should give you a microsecond timer.
uint64_t clockGetTime_mu()
{
	timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (uint64_t)ts.tv_sec * 1000000LL + (uint64_t)ts.tv_nsec / 1000LL;
}

mandelbrotArea::mandelbrotArea(QWidget *parent) : QWidget(parent)
{
	// set our inital view to hold the entire mandelbrot set.
	// a 3x3 square with -2,-1.5 as the lower left should work.
	llCoord.real = -2;
	llCoord.imag = 1.5; //note i changed to + to be upper left
	windowWidth = 3;
	this->maxIterations = 200; // a decent default
	setAttribute(Qt::WA_StaticContents);
}

bool mandelbrotArea::saveImage(const QString &fileName, const char *fileFormat)
{
	QImage visibleImage = image;
	resizeImage(&visibleImage, size());
	visibleImage.save(fileName, fileFormat);
	return true;
}

void mandelbrotArea::refreshImage()
{
	// this is just an example.  by making this function a "slot" (see the
	// header file) we can easily connect it to events from other objects
	// just as an illustration, we'll draw the gradient the other way.
	/*QPainter qp(&image);
	QColor qc;
	QPen qpen;
	// get the dimensions of our image in terms of pixels:
	unsigned long iwidth = image.width();
	unsigned long iheight = image.height();
	double unit = 1.0 / iwidth; // on a scale of 0-1, how wide is a pixel?
	for (unsigned long i = 0; i < iwidth; i++) {
		qc.setRgbF(i*unit,sqrt(i*unit),i*unit); // set the color we want to draw.
		qpen.setColor(qc); // apply the color to the pen
		qp.setPen(qpen);   // set the painter to use that pen
		qp.drawLine(iwidth-i-1,0,iwidth-i-1,iheight); // draw a line of the specified color.
	}
	
	update(); // repaint screen contents
	*/
	llCoord.real = -2;
	llCoord.imag = 1.5;
	windowWidth = 3;
	render();
	return;
}

void mandelbrotArea::mouseDoubleClickEvent(QMouseEvent *event)
{
	/* TODO: write the code for the zoom operation.  You can get
	// the mouse button from event->button() and check for
	// event->button() == Qt::LeftButton, etc. to figure out what
	// button is being pressed.
	*/
	
	/*	when we click, we get the x and y cooord of that position.
		We want ti use that click as sort of the "center" of where we want to go
		*/

	/*
	//complex but((3/500)*(event->x())-2, (3/500)*(event->y()) +1.5);
	//this->llcoord = this->llcoord/2;
	//llCoord.real = llCoord.real/2;
	//llCoord.imag = 1.5/2;
	*/	
	unsigned long iwidth = image.width();
	unsigned long iheight = image.height();
	/*double unit = 1.0 / iwidth;*/
	double unit = windowWidth/iwidth; /*This is just from the read me where the example is 3/500. 3 in this case is the window width, and 500, iWidth, is the number of pixles -- except it gets adjusted accordingly. */
	
	/* Note how I used unit and real and imaginary coordinates, 
	 * this is because if a user begisn to alter the cooridnates, 
	 * they will be able to kee moving around and repeating it, withought going out of some weird bounds.
	 * Additionally, notice unit. that's because it changes each time.
	 * Lastly, this but, gets the coordinate of the click, or the middle. 
	 * Now what you have to do is adjust accordiningly to keeping the the middle, 
	 * how is that? find the distance between the click and the current coordinates. 
	 * */


	/*Again notice the negation, that is to get the neg of that value*/
	complex but((unit)*(event->x())+llCoord.real, -(unit)*(event->y()) +llCoord.imag);

	//the read coordinate should be divded by 2, 
	//and the imaginary goes up by two. 
	//For this what we do is just bring in the corrdinates closer. 
	//The image never actually changes.????
	//windowWidth/=2; //This is to get a smaller version of the window
	if(event->button() == Qt::LeftButton){ /*Originally when you clicked the screen would just adjust to the reverse side*/
		windowWidth/=2;
		//llCoord.real = llCoord.real/2 - but.real /*- llCoord.real/2*/;
		//llCoord.imag = llCoord.imag/2 + but.imag /*+ llCoord.imag/2*/; //changed from - to + b/c we start at -2 1.5 and 1.5 is + 
		llCoord.real = but.real - windowWidth/2; // - but.real;
		llCoord.imag = but.imag + windowWidth/2 ; //+ but.imag;
		
		//windowWidth/=2;
		render();
	}
	else if(event->button() == Qt::RightButton){
		windowWidth*=2;
		llCoord.real = llCoord.real*2 - but.real;
		llCoord.imag = llCoord.imag*2 - but.imag;
		//windowWidth/=2;
		render();
	}
	//windowWidth/=iwidth; //Because when you are clicking you want to resize the window to your "new" "box"
}

void mandelbrotArea::mousePressEvent(QMouseEvent *event)
{
	// if you want your application to respond to mouse
	// clicks, implement this function.  You can figure out
	// which mouse button was pressed by examining event->button()
	// and you can get the position from event->pos()
}

void mandelbrotArea::mouseMoveEvent(QMouseEvent *event)
{
	// This will be called whenever the mouse moves across your
	// window.  Might be useful for dragging the image, should
	// you decide to implement it.
}

void mandelbrotArea::mouseReleaseEvent(QMouseEvent *event)
{
	// this would be useful to implement the drag operation.
}

void mandelbrotArea::paintEvent(QPaintEvent *event)
{
	// check: if blank, render first.
	if (!drawnYet) {
		drawnYet = true;
		this->render();
	}
	// otherwise, just repaint the portion of the screen that needs it.
	QPainter painter(this);
	QRect dirtyRect = event->rect();
	painter.drawImage(dirtyRect, image, dirtyRect);
}

void mandelbrotArea::resizeEvent(QResizeEvent *event)
{
	resizeImage(&image, QSize(width(), height()));
	update();
	QWidget::resizeEvent(event);
	return;
}

void mandelbrotArea::render()
{

	// TODO: write this function.
	// draw the portion of the mandelbrot set that lies in our window.
	// idea: loop through all the pixels, iterate the function figure out how
	// quickly the point is diverging, and color it based on the result


	// to give you some idea of what you need to do, I've drawn a nice green
	// gradient on the screen.  You will want to set the individual pixels
	// using the qp.drawPoint(x,y) function, instead of drawing a line.
	QPainter qp(&image);
	QColor qc;
	QPen qpen;
	// get the dimensions of our image in terms of pixels:
	unsigned long iwidth = image.width();
	unsigned long iheight = image.height();
	//double unit = 1.0 / iwidth; /* on a scale of 0-1, how wide is a pixel?*/ /*Note that this only give u a small portion of the screen*/
	double unit = this->windowWidth/iwidth;
	//complex bef(0, 0); //note bounds start at 1 since c0 = 0. 

	for(unsigned long i = 0; i < iwidth; i++){ /*Width pixles*/
		for(unsigned long j = 0; j < iheight; j++){ /*height pixels*/
		complex z(0, 0); /*State Z off at 0 so that in the first runtime of mandelbrot in the coordiantions, */
		complex c(((unit)*i + this->llCoord.real/*-2 but as we click this should change*/), -(unit)*j + this->llCoord.imag/*1.5 at first but when u click around this doesnt actually work*/);
		double iteration = 1; /*This value will be used to calulcate the color stuff*/ 
		/*NOTE iteration has to be a doulbe because it will become a large value that divides 1 later on and will thus be 0 if that occurs*/
		while(z.norm() < 4 && iteration < this->maxIterations){ 
			/*NOTE how you have norm is less than four. 
			 * THe original expression states norm of z is less than two but thats if you take into consideration the square root of that vlaue */
			z = z*z + c; 	
			//because now is the current value that we are looking at
			iteration++;
		}
		/*iteration = 1;*/ /*Note this line messed you up and only produced a white scrren because it set iterations to 1 and thus the color was always one. */
		qc.setRgbF(1/iteration, sqrt(1/iteration), 1/iteration); /*According to skeith just do 1/iterations*/
		iteration = 1; /*Note iterations should be set to 1 but I believe the for loops outside handle this. */
		/*Keep the below the same*/
		qpen.setColor(qc);
		qp.setPen(qpen);
		qp.drawPoint(i, j); /*width, height. */
		
		}
	}
/*	
	for (unsigned long i = 0; i < iwidth; i++) {
		qc.setRgbF(i*unit, sqrt(i*unit) ,i*unit); // set the color we want to draw.
		qpen.setColor(qc); // apply the color to the pen
		qp.setPen(qpen);   // set the painter to use that pen
		qp.drawLine(i,0,i,iheight); // draw a line of the specified color.
	}*/
	update(); // repaint screen contents
	return;
}

void mandelbrotArea::resizeImage(QImage *image, const QSize &newSize)
{
	// your custom resize code would go here...
	if (image->size() == newSize)
		return;

	// for now, we will just expand our image with blank (white) space.
	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));
	QPainter painter(&newImage);
	painter.drawImage(QPoint(0, 0), *image);
	*image = newImage;
}

unsigned long mandelbrotArea::getIterations()
{
	/* NOTE: this is used by MainWindow for the initial value to place
	 * in the iteration control dialog. */
	return this->maxIterations;
}

void mandelbrotArea::setIterations(unsigned long newMax)
{
	/* NOTE: this is called by MainWindow once the iterations
	 * dialog has been processed. */
	this->maxIterations = newMax;
}
