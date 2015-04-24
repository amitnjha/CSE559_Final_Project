#include "opencv2\highgui\highgui.hpp"
#include "opencv2\core\core.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2\imgproc\imgproc_c.h"
#include "opencv2\imgproc\types_c.h"
#include "opencv2\contrib\contrib.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]){
	//bool a = cv::face::initModule_facerec();
	bool a = cv::initModule_contrib();
	Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
	//FaceRecognizer* f = cv::createLBPHFaceRecognizer();
	CascadeClassifier classifier;
	FileStorage fs;
	fs.open("recognizer/lbph_human_faces.xml", FileStorage::READ);
	model->load(fs);

	classifier.load("cascades/haarcascade_frontalface_alt.xml");

	//CvCapture *capture;
	VideoCapture cap(0);
	if (!cap.isOpened()){
		cout << "Error opening camera" << endl;
	}
	int i = 0;
	while (true){
		
		Mat frame;
		Mat frame_gray;
		std::vector<Rect> rects;
		cap >> frame;
		cvtColor(frame, frame_gray, CV_BGR2GRAY);
		equalizeHist(frame_gray, frame_gray);
		classifier.detectMultiScale(frame_gray, rects, 1.3, 4, 0, Size(25, 25));
		cout << "face count " << rects.size() << endl;
		imshow("me", frame);
		if (rects.size() > 0){
			//try to predict who is it?
			Rect rect = rects[0];
			Mat detectedface = frame_gray(rect);
			//i++;
			//imwrite(to_string(i) + ".jpg",detectedface);
			int prediction = model->predict(detectedface);
			cout << "Detected Face is " << prediction << endl;
		}

		if (waitKey(300) == 0)
			break;
		//recognition
	}
	return 0;

}