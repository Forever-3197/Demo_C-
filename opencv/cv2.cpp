#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main() {

//Mat m =Mat ::ones(Size(3,2),CV_32FC(3));
/*第一中访问方式
    Mat m = (Mat_<int>(3, 2) << 11, 12, 13, 14, 15, 16);
    for (int i = 0;i < m.rows;i++) {
        for (int j = 0;j < m.cols;j++) {
            cout << m.at<int>(i, j) << ",";
        }
        cout << endl;
    }
    cout << m.total();
    waitKey(0);
    return 0;*/
//第二种访问方式
/*
    Mat m = (Mat_<int>(3, 2) << 12, 13, 14, 15, 15, 16);
    for (int i = 0;i < m.rows;i++) {
        const int * ptr = m.ptr<int>(i);
        for (int j = 0;j < m.cols;j++) {
            cout << ptr[j]<<",";
        }
        cout << endl;
    }
    waitKey(0);
    return 0;*/
//第三种方法
//Vec<int, 3> vi(12, 23, 44);
//cout << vi;
Mat m = imread("./mm.jpg");
resize(m, m, Size(),0.5,0.5);//我长宽都变为原来的0.5倍
/*
    for (int i = 0;i < 100;i++) {
        for (int j = 0;j < 100;j++) {
            cout << m.at<Vec3b>(i, j) << ",";
        }
        cout << endl;
    }*/
/*
    Mat k;
    vector<Mat> planes;
    split(m, planes);
    imshow("1", planes[0]);
    imshow("2", planes[1]);
    imshow("3", planes[2]);
    merge(planes, k);
    
    waitKey(0);*/
/*

//选取指定矩阵范围
    Mat a = (Mat_<int>(4, 4) << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Mat k = a.colRange(Range(2, 4));//第三列第四列
//    Mat k = a.rowRange(Range(2, 4));//第三行第四行
    for (int i = 0;i < k.rows;i++) {
        for (int j = 0;j < k.cols;j++) {
            cout << k.at<int>(i, j) << ",";
        }
        cout << endl;
    }
    waitKey(0);

    Mat b = k.clone();
    Mat c;
    k.rowRange(2, 4).copyTo(c);
    //Rect 左上角坐标 右下
    */

namedWindow("Image");
imshow("原始图像",m);

Mat grad_x, grad_y;
Mat abs_grad_x, abs_grad_y, m2;
//求x方向梯度
    Sobel(m, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);
    imshow("【效果图】X方向Sobel", abs_grad_x);

    //求y方向梯度
    Sobel(m, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);
    imshow("【效果图】Y方向Sobel", abs_grad_y);

    //合并梯度（近似）
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, m2);
    imshow("【效果图】整体方向Sobel", m2);

Mat src1 = (Mat_<uchar>(2, 3) << 11, 22, 33, 44, 55, 100);
Mat src2 = (Mat_<float>(2, 3) << 2, 2, 2, 2, 2, 3);
Mat dst;
multiply(src1,src2,dst,1.0,CV_32FC1);//两个Mat相加
for (int i = 0;i < dst.rows;i++) {
    for (int j = 0;j < dst.cols;j++) {
        cout << dst.at<float>(i, j) << ",";
    }
    cout << endl;
}
//c++点乘 multiply（src1,src2,dst,1.0,CV_32FC1）
//pyhton 点乘 np.multiply(src1,src2)
//或者将 src1 设置为 uint8  src2 设置为 float   src1*src2
//点除 src1/src2
//Mat 点除 divide();
//ndarray 点除
// src2/src1 uint8 /0=0 float /0=inf
//Mat 矩阵乘法  src1*src2
// gemm()
//np.doc(src1,src2)

waitKey(0);
}