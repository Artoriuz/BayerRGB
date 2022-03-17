#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    Mat input_img, output_img;
    Mat tmp_blue, tmp_green, tmp_red;

    input_img = imread(argv[1], IMREAD_ANYDEPTH);

    output_img = Mat::zeros(input_img.rows, input_img.cols, CV_16UC3);

    tmp_blue = Mat::zeros(input_img.rows, input_img.cols, CV_16UC1);
    tmp_green = Mat::zeros(input_img.rows, input_img.cols, CV_16UC1);
    tmp_red = Mat::zeros(input_img.rows, input_img.cols, CV_16UC1);

    cout << "Starting grayscale to RGB mapping" << endl;
    for (int idy = 0; idy < input_img.rows; idy++) { 
        for (int idx = 0; idx < input_img.cols; idx++) { 
            if ((idy % 2 == 0) && (idx % 2 == 0)) {
                tmp_red.at<ushort>(idy, idx) = input_img.at<ushort>(idy, idx);
            } else if ((idy % 2 == 0) && (idx % 2 != 0)) {
                tmp_green.at<ushort>(idy, idx) = input_img.at<ushort>(idy, idx);
            } else if ((idy % 2 != 0) && (idx % 2 == 0)) {
                tmp_green.at<ushort>(idy, idx) = input_img.at<ushort>(idy, idx);
            } else if ((idy % 2) != 0 && (idx % 2 != 0)) {
                tmp_blue.at<ushort>(idy, idx) = input_img.at<ushort>(idy, idx);
            }
        }
    }
    
    cout << "Merging channels" << endl;
    vector<Mat> channels;
    channels = {tmp_blue, tmp_green, tmp_red};
    merge(channels, output_img);
    
    cout << "Writing result to PNG" << endl;
    vector<int> compression_params;
    compression_params.push_back(IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
    
    string filename(argv[1]);
    size_t lastindex = filename.find_last_of("."); 
    string rawname = filename.substr(0, lastindex); 
    
    imwrite(rawname + ".png", output_img, compression_params);
    
    cout << "write complete" << endl;
    
    return 0;
}