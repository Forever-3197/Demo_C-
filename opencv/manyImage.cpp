/* #include <iostream>
#include <opencv2/opencv.hpp>
 
using namespace std;
using namespace cv;
 
 
//每行显示两个图片
void mergeImage(Mat &dst, vector<Mat> &images)
{
	int imgCount = (int)images.size();
 
	if (imgCount <= 0)
	{
		printf("the number of images is too small\n");
		return;
	}
 
	printf("imgCount = %d\n", imgCount);
 
	//将每个图片缩小为指定大小
	int rows = 300;
	int cols = 400;
	for (int i = 0; i < imgCount; i++)
	{
		resize(images[i], images[i], Size(cols, rows)); //注意区别：Size函数的两个参数分别为：宽和高，宽对应cols，高对应rows
	}
 
	//创建新图片的尺寸
	//	高：rows * imgCount/2
	//	宽：cols * 2
	//
	dst.create(rows * imgCount / 2, cols * 2, CV_8UC3);
 
	for (int i = 0; i < imgCount; i++)
	{
		images[i].copyTo(dst(Rect((i % 2) * cols, (i / 2)*rows, images[0].cols, images[0].rows)));
	}
}
 
int main()
{
	vector<Mat> images(4);//相当于创建一个图像数组
	Mat dst;
 
	images[0] = imread("./mm.jpg");
	images[1] = imread("./mm.jpg");
	images[2] = imread("./mm.jpg");
	images[3] = imread("./mm.jpg");
 
	mergeImage(dst, images);
	imshow("dst", dst);
 
	waitKey(0);	
	destroyAllWindows();
 
	return 0;
} */

#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

#define NameWindow "图片处理效果"  
void imshowMany(const std::string& _winName, const vector<Mat>& ployImages);//  


int main()

{

	//图像显示测试

	Mat srcImage = cv::imread("./mm.jpg");    //注意这里的//的方向，一开始写反了，怎么都出不来。
//	imshow("原图", srcImage);

	Mat temImage, grayImage, midImage, edgeImage, dstImage;


	cv::cvtColor(srcImage, grayImage, CV_BGR2GRAY);//转换为灰度图  
	blur(grayImage, grayImage, Size(5, 5), Point(-1, -1));//均值模糊  
	//GaussianBlur(grayImage, grayImage, Size(5, 5), 0, 0);  
//	imshow("原图灰度图+均值模糊", grayImage);
	cvtColor(grayImage, midImage, CV_GRAY2BGR);//转为三通道图,用于多图显示，位置（1，2）  
	Canny(grayImage, edgeImage, 50, 100, 3);//tempImage为单通道二值图，在多图函数中不可显示  
//	imshow("灰度图Canny边缘检测", edgeImage);
	cvtColor(edgeImage, temImage, CV_GRAY2BGR);//转为三通道图，用于多图显示，位置（2，1）  
	cvtColor(edgeImage, dstImage, CV_GRAY2BGR);//转为三通道图，用于多图显示，位置（2，2）  


	vector<Vec2f>lines;//矢量结构lines用于存放得到的线段矢量集合  
	HoughLines(edgeImage, lines, 1, CV_PI / 180, 123, 0, 0);//阈值的选择对结果影响很大  


	for (size_t i = 0; i < lines.size(); i++)//在图中绘制出每条线段  
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dstImage, pt1, pt2, Scalar(255, 0, 255), 1, 8);//线条颜色为紫色  
	}
//	imshow("基于canny的Hough直线变换", dstImage);

//实现一窗多显示的关键：

	vector<Mat>Images(12);//模板类vector，用于放置4个类型为Mat的元素，即四张图片  
	Images[0] = srcImage;
	Images[1] = midImage;
	Images[2] = temImage;
	Images[3] = dstImage;
    Images[4] = srcImage;
	Images[5] = midImage;
	Images[6] = temImage;
	Images[7] = dstImage;
    Images[8] = srcImage;
	Images[9] = midImage;
	Images[10] = temImage;
	Images[11] = dstImage;




	namedWindow(NameWindow);
	imshowMany(NameWindow, Images);//调用一个窗口显示多图函数  


	waitKey(0);
	return 0;


}


//自定义一个窗口显示多图函数  
void imshowMany(const std::string& _winName, const vector<Mat>& ployImages)
{
	int nImg = (int)ployImages.size();//获取在同一画布中显示多图的数目  


	cv::Mat dispImg;


	int size;
	int x, y;
	//若要在OpenCV实现同一窗口显示多幅图片，图片要按矩阵方式排列，类似于Matlab中subplot();     
	//多图按矩阵排列的行数  ，h: 多图按矩阵排列的的数    
	int w, h;


	float scale;//缩放比例  
	int max;


	if (nImg <= 0)
	{
		printf("Number of arguments too small....\n");
		return;
	}
	else if (nImg > 12)
	{
		printf("Number of arguments too large....\n");
		return;
	}
	else if (nImg == 1)
	{
		w = h = 1;
		size = 400;
	}
	else if (nImg == 2)
	{
		w = 2; h = 1;//2x1  
		size = 400;
	}
	else if (nImg == 3 || nImg == 4)
	{
		w = 2; h = 2;//2x2  
		size = 400;
	}
	else if (nImg == 5 || nImg == 6)
	{
		w = 3; h = 2;//3x2  
		size = 300;
	}
	else if (nImg == 7 || nImg == 8)
	{
		w = 4; h = 2;//4x2  
		size = 300;
	}
	else
	{
		w = 4; h = 3;//4x3  
		size = 200;
	}


	dispImg.create(Size(100 + size*w, 30 + size*h), CV_8UC3);//根据图片矩阵w*h，创建画布，可线的图片数量为w*h  


	for (int i = 0, m = 20, n = 20; i<nImg; i++, m += (20 + size))
	{
		x = ployImages[i].cols; //第(i+1)张子图像的宽度(列数)  
		y = ployImages[i].rows;//第(i+1)张子图像的高度（行数）  

		max = (x > y) ? x : y;//比较每张图片的行数和列数，取大值  
		scale = (float)((float)max / size);//计算缩放比例  

		if (i%w == 0 && m != 20)
		{
			m = 20;
			n += 20 + size;
		}


		Mat imgROI = dispImg(Rect(m, n, (int)(x / scale), (int)(y / scale))); //在画布dispImage中划分ROI区域  
		resize(ployImages[i], imgROI, Size((int)(x / scale), (int)(y / scale))); //将要显示的图像设置为ROI区域大小  
	}
	namedWindow(_winName);
	imshow(_winName, dispImg);
}
