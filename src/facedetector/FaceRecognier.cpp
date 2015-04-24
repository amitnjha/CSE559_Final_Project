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

using namespace cv;
//using namespace cv::face;
using namespace std;

static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
	std::ifstream file(filename.c_str(), ifstream::in);
	if (!file) {
		string error_message = "No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, classlabel;
	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, classlabel);
		if (!path.empty() && !classlabel.empty()) {
			images.push_back(imread(path, 0));
			labels.push_back(atoi(classlabel.c_str()));
		}
	}
}


int main5(int argc, char* argv[]){
	
	//FaceRecognizer* f = cv::face::createLBPHFaceRecognizer();
	//FaceRecognizer* f = createLBPHFaceRecognizer();
	bool a = cv::initModule_contrib();
	//FaceRecognizer* f = createLBPHFaceRecognizer();
	Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();

	FileStorage fs;
	fs.open("recognizer/lbph_human_faces.xml", FileStorage::READ);
	model->load(fs);
	Mat input  = imread(argv[1],0);
	int i = model->predict(input);
	cout << "prediction is" << i << endl;
	//f->create("recognizer/lbph_human_faces.xml");
	//f->write(fs);
	return 0;
}

