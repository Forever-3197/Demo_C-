#include<iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
int main()
{
//1、读入一张图片，返回一个矩阵对象
Mat img = imread("./logo.png",1);
//2、定义一个窗口盛放该图片
namedWindow("原图");
//3、显示该图片
imshow("游戏原图",img);
//4、等待6000ms后窗口退出
waitKey(6000);
    using namespace std;    //记得写就行
    cout << "HelloWorld\n"; //打印“helloworld"
    //cout << endl;         //这句是单独打一个回车的意思，因为题目不要求，我们就不打了s
return 0;
}