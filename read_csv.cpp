/*
 * read_csv.cpp
 *
 *  Created on: 23-Feb-2014
 *      Author: sumit4iit
 *      File operations required for the training.
 */

#include<string>
#include<vector>
#include<sstream>
#include<iostream>
#include<fstream>
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;

static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ',')
{
	std::ifstream file(filename.c_str(), ifstream::in);
	if (!file)
	{
		string error_message =
				"No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, classlabel;
	while (getline(file, line))
	{
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, classlabel);
		if (!path.empty() && !classlabel.empty())
		{

			Mat image = imread(path, CV_LOAD_IMAGE_GRAYSCALE);
			if (!image.empty())
			{

/*				if (debug)
				{
					namedWindow("show",CV_WINDOW_AUTOSIZE);
					imshow("show",image);
					waitKey(0);
				}*/

				// if the size of image is now equal to 110x150 then resize it.
				if (image.size().height != 150 || image.size().width != 110)
				{
//					cout << "resizing " << path << endl;
					Size s;
					s.height = 150;
					s.width = 110;
					if (image.size().height > 150)
					{
						// if scaling
						resize(image, image, s, 0, 0, INTER_AREA);
					}
					else
					{
						// if scaling up, then use cubic interpolation.
						resize(image, image, s, 0, 0, INTER_CUBIC);
					}
//					cout << image.rows << " " << image.cols << endl;
				}

				images.push_back(imread(path, 0));
				labels.push_back(atoi(classlabel.c_str()));
			}
			else
			{
				cout << "Image read failed." << endl;
			}
		}
	}
}


