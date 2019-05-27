// CascadeClassifier.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

CascadeClassifier faceCascade;

void detectAndDisplay(Mat img)
{
	Mat grayImg;
	cvtColor(img, grayImg, COLOR_BGR2GRAY);
	equalizeHist(grayImg, grayImg);
	std::vector<Rect> face;
	faceCascade.detectMultiScale(grayImg, face);

	for (int i = 0; i < face.size(); i++) {
		//Point center(face[i].x + face[i].width / 2, face[i].y + face[i].height / 2);
		rectangle(img, Point(face[i].x, face[i].y), Point(face[i].x + face[i].width, face[i].y + face[i].height), Scalar(255, 255, 0), 4);
	}
	
	Mat resizeImg;
	for (int i = 1; i < 20; i++) {
		if (img.cols / i <= 1000) {
			resize(img, resizeImg, Size(img.cols / i, img.rows / i), 0, 0, INTER_LINEAR);
			break;
		}
	}
	imshow("Display", resizeImg);
}

int main()
{
	String faceCasName = "haarcascade_frontalface_alt.xml";
	if (!faceCascade.load(faceCasName)) {
		cout << "Loading FaceCascade fail......";
		return -1;
	}
	else
		cout << "Loading FaceCascade success...." << endl;

	String srcName;
	cout << "Please input file name : ";
	cin >> srcName;
	Mat src = imread(srcName, IMREAD_UNCHANGED);
	detectAndDisplay(src);

	waitKey(0);
	return 0;
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的秘訣: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
