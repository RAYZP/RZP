
#include<math.h>
#include<iostream> 
#include <opencv2/opencv.hpp> 
using namespace cv;
using namespace std;
int main()
{
	Mat temp = imread("E:\\opencvcode\\ConsoleApplication3\\ConsoleApplication3\\img\\image (2).bmp");//前一帧
	Mat frame = imread("E:\\opencvcode\\ConsoleApplication3\\ConsoleApplication3\\img\\image (3).bmp");//后一帧
	//pyrDown(temp, temp);
	//pyrDown(frame, frame);

	//int resize_height = 861;
	//int resize_width = 484;
	//resize(temp, temp, Size(resize_width, resize_height), (0, 0), (0, 0), INTER_LINEAR);//重新调整图像大小
	//resize(frame, frame, Size(resize_width, resize_height), (0, 0), (0, 0), INTER_LINEAR);//重新调整图像大小
	resize(frame, frame, Size(temp.size().width, temp.size().height), (0, 0), (0, 0), INTER_LINEAR);//重新调整图像大小
	//Mat MoveDetect(Mat temp, Mat frame)
	//{
	Mat result = frame.clone();
	//将background和frame转为灰度图  
	Mat gray1, gray2;
	cvtColor(temp, gray1, CV_BGR2GRAY);
	cvtColor(frame, gray2, CV_BGR2GRAY);
	//将background和frame做差  
	Mat diff;
	absdiff(gray1, gray2, diff);
	//imshow("diff", diff);
	//对差值图diff_thresh进行阈值化处理  
	Mat diff_thresh;
	threshold(diff, diff_thresh, 25,255, CV_THRESH_BINARY);
	/*imshow("diff_thresh", diff_thresh);*/
	//腐蚀  
	Mat kernel_erode = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat kernel_dilate = getStructuringElement(MORPH_RECT, Size(15, 15));
	erode(diff_thresh, diff_thresh, kernel_erode);
	/*imshow("erode", diff_thresh);*/
	//膨胀  
	dilate(diff_thresh, diff_thresh, kernel_dilate);

	Mat srcImage = diff_thresh.clone();
	int W = srcImage.cols, H = srcImage.rows;
	int step = srcImage.step, nstep = srcImage.step;
	const unsigned char *p0 = srcImage.data;
	int xmin = 1e6 , ymin =1e6 , xmax = 0, ymax = 0;
	for (int i = 0; i < H; i++)
	{
		const unsigned char *p = p0 + i*step;

		for (int j = 0; j < W; j++)
		{
			const unsigned char *pj = p + j;
			if (p[j] > 0)
			{
				xmin = min(j, xmin);
				xmax = max(j, xmax);
				ymin = min(i, ymin);
				ymax = max(i, ymax);
			}
		}
	}
	rectangle(result, Rect(xmin, ymin, xmax - xmin, ymax - ymin), Scalar(0, 255, 0), 1, 1, 0);
	
	cvWaitKey(0);
}