/*
 * test.cpp
 *
 *  Created on: 23-Feb-2014
 *      Author: sumit4iit
 *     	Trains classifier for given set of images.
 */
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <highgui.h>
#include "read_csv.cpp"
using namespace cv;
using namespace std;
const int debug = 0;

/*
String face_cascade_name = "haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
*/
String window_name = "demo";

//void detectAndDisplay(Mat frame);


int main(int argc, const char *argv[])
{
/*	if (!face_cascade.load(face_cascade_name))
	{
		printf("--(!)Error loading\n");
		return -1;
	};
	if (!eyes_cascade.load(eyes_cascade_name))
	{
		printf("--(!)Error loading\n");
		return -1;
	};
*/
	// Check for valid command line arguments, print usage
	// if no arguments were given.
	if (debug && argc != 3)
	{
		cout << "usage: " << argv[0] << " <TrainCSV.ext>" << argv[1]
				<< " <TestCSV.ext> " << endl;
		exit(1);
	}
	else if(argc != 2)
	{
		cout<< "usage: " << argv[0] << "<TrainCSV.ext>";
		exit(1);
	}


	// Get the path to your CSV.
	// fn_csv are training samples.
	// test_csv are testing samples.

	string fn_csv = string(argv[1]);

//	string test_csv = string(argv[2]);

	// These vectors hold the images and corresponding labels.

	vector<Mat> images;
	vector<int> labels;

	// The following line predicts the label of a given
	// test image:

//	vector<Mat> testImages;
//s	vector<int> testLabels;

	// Read in the data. This can fail if no valid
	// input filename is given.

	try
	{
		read_csv(fn_csv, images, labels);

//		if(debug)
//		read_csv(test_csv, testImages, testLabels);

		cout << "executed read_csv\n";
	}
	catch (cv::Exception& e)
	{
		cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg
				<< endl;
		// nothing more we can do
		exit(1);
	}

	// Quit if there are not enough images for this demo.
	if (images.size() <= 1)
	{
		string error_message =
				"This demo needs at least 2 images to work. Please add more images to your data set!";
		CV_Error(CV_StsError, error_message);
	}
	cout << "Read the file\n";

	// initialize contrib module.
	// Apparently opencv sometimes faces issues while dynamically loading libopencvcontrib.so while runtime.
	cv::initModule_contrib();

	Ptr<FaceRecognizer> model = createLBPHFaceRecognizer(1, 8, 8, 8, 123.0);

	cout << "Created Model" << endl;
	model->train(images, labels);

	cout << "Training was successful with " << images.size() << " images";

	cout << "Model Information:" << endl;
	string model_info =
			format(
					"\tLBPH(radius=%i, neighbors=%i, grid_x=%i, grid_y=%i, threshold=%.2f)",
					model->getInt("radius"), model->getInt("neighbors"),
					model->getInt("grid_x"), model->getInt("grid_y"),
					model->getDouble("threshold"));
	cout << model_info << endl;
	vector<Mat> histograms = model->getMatVector("histograms");

	cout<<"Saving model: lbp_features.xml\n";
	model->save("lbp_features.xml");

	// visualize these histograms or stats.
	// or perhaps for using another training model?
	cout << "Size of the histograms: " << histograms[0].total() << endl;

/*	if(debug)
	{
		for (int i = 0; i < (int)testImages.size(); i++)
		{
			int predictedLabel = model->predict(testImages[i]);
			string result_message = format("Predicted class = %d / Actual class = %d.",
					predictedLabel, testLabels[i]);
			cout << result_message << endl;
		}
	}*/

//	vector<Mat> faces;
/*	namedWindow(window_name);
	CvCapture* cam;
	Mat frame;
	cam = cvCreateFileCapture("hp.mp4");
	if(cam)
	{

		int numFrames = (int) cvGetCaptureProperty(cam,CV_CAP_PROP_FRAME_COUNT);
//		for(int i=1 ; i<numFrames; i++)
//		{
			frame = cvQueryFrame(cam);
			if(!frame.empty())
			{
				detectAndDisplay(frame);

				waitKey(0);
			}
//		}
	}
*/
	return 0;
}
/*
void detectAndDisplay( Mat frame )
{
  vector<Rect> faces;
  vector<Mat> faceROI;

  Mat frame_gray;

  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );

  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

  for( size_t i = 0; i < faces.size(); i++ )
  {
    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );

    //    ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

    rectangle(frame, Point(faces[i].x, faces[i].y), Point(faces[i].x+faces[i].width, faces[i].y+faces[i].height), Scalar(0,0,0),2,0 );
    Mat ROI = frame_gray( faces[i] );
    faceROI.push_back(ROI);
    /*    std::vector<Rect> eyes;

    //-- In each face, detect eyes
    eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( size_t j = 0; j < eyes.size(); j++ )
     {
       Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
       int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
       circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
     }

  }
  //-- Show what you got

//  return &faceROI;
  imshow( window_name, frame );

 }
*/
