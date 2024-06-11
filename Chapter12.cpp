//12-1-1
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(void) {
	Mat src = imread("labelex.png", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY_INV | THRESH_OTSU); //검은색 픽셀은 배경으로 간주하고, 흰색 픽셀은 객체로 간주하기 때문에 "THRESH_BINARY_INV"사용
	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);
	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	//각 레이블의 면적이 최대, 최소인 객체 찾기
	int min = stats.at<int>(1, 4), max = stats.at<int>(1, 4);
	int min_num = 1, max_num = 1;
	for (int i = 2; i < cnt; i++) {
		int* add = stats.ptr<int>(i);
		if (min > add[4]) { //레이블의 최소 면적
			min = add[4];
			min_num = i;
		}
		if (max < add[4]) { //레이블의 최대 면적
			max = add[4];
			max_num = i;
		}
	}

	for (int i = 1; i < cnt; i++) {
		cout << i << "번 레이블 면적: " << stats.at<int>(i, 4) << endl;
	}
	cout << endl;

	cout << "면적이 최대인 객체의 레이블: " << max_num << endl;
	cout << "무게중심(x, y): " << setw(5) << centroids.at<double>(max_num, 0) << ", " << centroids.at<double>(max_num, 1) << endl;
	cout << "면적이 최소인 객체의 레이블: " << min_num << endl;
	cout << "무게중심(x, y): " << setw(5) << centroids.at<double>(min_num, 0) << ", " << centroids.at<double>(min_num, 1) << endl;

	//면적이 최대(red), 최소(blue) 레이블 표시
	int* p = stats.ptr<int>(min_num);
	rectangle(dst, Rect(p[0], p[1], p[2], p[3]), Scalar(255, 0, 0));
	p = stats.ptr<int>(max_num);
	rectangle(dst, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 0, 255));

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	return 0;
}

//12-1-2
/*#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(void) {
	Mat src = imread("polygon.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);

	Mat bin;
	threshold(gray, bin, 150, 255, THRESH_BINARY_INV);

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);
	cout << "레이블 갯수: " << cnt - 1 << endl;
	cout << "label" << setw(5) << 'x' << "\t" << 'y' << "\t" << "width" << "\t" << "height" << "\t" << "area" << "\t" << "color[B, G, R]" << endl;
	for (int i = 1; i < cnt; i++) {
		int* p = stats.ptr<int>(i);
		cout << i << "\t" << p[0] << "\t" << p[1] << "\t" << p[2] << "\t" << p[3] << "\t" << p[4] << "\t";
		//각 레이블 중심좌표를 이용한 레이블 [B, G, R] 출력
		int x = cvRound(centroids.at<double>(i, 0));
		int y = cvRound(centroids.at<double>(i, 1));
		cout << src.at<Vec3b>(y, x) << endl;
		//각 레이블 중심좌표를 이용한 레이블값 출력
		String num = format("%d", i);
		putText(src, num, Point(x, y), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255));
		//각 레이블 표시
		rectangle(src, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 255, 255));
	}

	imshow("src", src);
	imshow("gray", gray);
	imshow("bin", bin);
	waitKey();
	return 0;
}*/
//12-1-3
/*#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(void) {
	Mat src = imread("polygon.bmp");
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);

	Mat bin;
	threshold(gray, bin, 150, 255, THRESH_BINARY_INV);

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);
	for (int i = 1; i < cnt; i++) {
		//cout << i << "번 객체의 무게중심: " << Point(centroids.at<double>(i, 0), centroids.at<double>(i, 1)) << endl;
		cout << i << "번 객체의 무게중심: (" << centroids.at<double>(i, 0) << ", " << centroids.at<double>(i, 1) << ")" << endl;

		//직접 계산한 각 레이블의 무게중심
		int x_value = 0, y_value = 0;
		int count = 0;
		for (int x = stats.at<int>(i, 0); x < stats.at<int>(i, 0) + stats.at<int>(i, 2); x++) {
			for (int y = stats.at<int>(i, 1); y < stats.at<int>(i, 1) + stats.at<int>(i, 3); y++) {
				if (bin.at<uchar>(y, x) == 255) {
					x_value += x;
					y_value += y;
					count++;
				}
			}
		}
		cout << "직접 계산: " << setw(11) << "(" << (double)x_value / count << ", " << (double)y_value / count << ")" << endl << endl;
	}
	return 0;
}*/
//12-1-4
/*#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(void) {
	//컬러 영상(원본)
	Mat src = imread("car.png");
	//그레이 영상
	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY);

	Mat dst_blur;
	blur(dst, dst_blur, Size(5, 5));
	//x축 방향으로 1차 편미분한 영상
	Mat dx;
	Sobel(dst_blur, dx, -1, 1, 0);
	//이진화 영상
	Mat binary;
	threshold(dx, binary, 110, 255, THRESH_BINARY);
	//최종 영상(번호판만 객체로 인식)
	Mat final;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(40, 5)); //(40 by 5) Mat 객체를 사용
	morphologyEx(binary, final, MORPH_ERODE, Mat()); //침식 연산을 통해 객체(흰색)을 얇게 만든 후
	morphologyEx(final, final, MORPH_CLOSE, kernel); //닫기 연산(팽창->침식)을 통해 kernel 사이즈에 들어가는 객체(흰색)끼리 연결

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(final, labels, stats, centroids);
	int max = stats.at<int>(1, 4);
	int max_num = 1;
	for (int i = 2; i < cnt; i++) {
		int* add = stats.ptr<int>(i);
		if (max < add[4]) {
			max = add[4];
			max_num = i;
		}
	}
	cout << max_num << endl;
	int* p = stats.ptr<int>(max_num);
	rectangle(src, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 0, 255));

	imshow("image", src);
	waitKey();
	return 0;
}*/
