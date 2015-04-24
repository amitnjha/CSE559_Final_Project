#include <iostream>
#include <fstream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"
#include "opencv2/stitching/detail/matchers.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "opencv2/videoio/videoio_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/face/facerec.hpp"


using namespace std;
using namespace cv;

bool try_use_gpu = false;
vector<Mat> imgs;
string result_name = "result.jpg";

void printUsage();
int parseCmdArgs(int argc, char** argv);



int main(int argc, char* argv[])
{
	//bool a = cv::face::initModule_facerec();
	
	vector<Mat> vImg;
	Mat rImg;

	string dirname = argv[1];
	int imgCount = atoi( argv[2]);

	//if last char of dirname does not have '/' append one.

	for (int i = 1; i <= imgCount; i++){
		
		//cout << dirname << "/" << i << ".jpg" << endl;
		cout << "Reading " << dirname + "/" + to_string(i) + ".jpg" << endl;
		vImg.push_back(imread(dirname + "/" + to_string(i) + ".jpg"));
	}


	Stitcher stitcher = Stitcher::createDefault(true);

	unsigned long AAtime = 0, BBtime = 0; //check processing time
	AAtime = getTickCount(); //check processing time

	Stitcher::Status status = stitcher.stitch(vImg, rImg);
	
	BBtime = getTickCount(); //check processing time 
	printf("%.2lf sec \n", (BBtime - AAtime) / getTickFrequency()); //check processing time

	//outputfile name
	string outputdir = ".";
	if (argc >= 4)
		outputdir = argv[3];

	string prefix = "result_with_" + to_string(imgCount);
	
	string suffix = ".jpg";

	if (Stitcher::OK == status){
		imwrite(outputdir + "/" + prefix+suffix, rImg);
		//imshow("Stitching Result", rImg);
	}
	else
		printf("Stitching failed.");

	//waitKey(0);

}



void printUsage()
{
    cout <<
        "Rotation model images stitcher.\n\n"
        "stitching img1 img2 [...imgN]\n\n"
        "Flags:\n"
        "  --try_use_gpu (yes|no)\n"
        "      Try to use GPU. The default value is 'no'. All default values\n"
        "      are for CPU mode.\n"
        "  --output <result_img>\n"
        "      The default is 'result.jpg'.\n";
}


int parseCmdArgs(int argc, char** argv)
{
    if (argc == 1)
    {
        printUsage();
        return -1;
    }
    for (int i = 1; i < argc; ++i)
    {
        if (string(argv[i]) == "--help" || string(argv[i]) == "/?")
        {
            printUsage();
            return -1;
        }
        else if (string(argv[i]) == "--try_use_gpu")
        {
            if (string(argv[i + 1]) == "no")
                try_use_gpu = false;
            else if (string(argv[i + 1]) == "yes")
                try_use_gpu = true;
            else
            {
                cout << "Bad --try_use_gpu flag value\n";
                return -1;
            }
            i++;
        }
        else if (string(argv[i]) == "--output")
        {
            result_name = argv[i + 1];
            i++;
        }
        else
        {
            Mat img = imread(argv[i]);
            if (img.empty())
            {
                cout << "Can't read image '" << argv[i] << "'\n";
                return -1;
            }
            imgs.push_back(img);
        }
    }
    return 0;
}
