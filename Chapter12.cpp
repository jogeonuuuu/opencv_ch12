//12-1-1
/*#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(void) {
	Mat src = imread("labelex.png", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return -1; }
	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY_INV | THRESH_OTSU); //������ �ȼ��� ������� �����ϰ�, ��� �ȼ��� ��ü�� �����ϱ� ������ "THRESH_BINARY_INV"���
	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);
	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	//�� ���̺��� ������ �ִ�, �ּ��� ��ü ã��
	int min = stats.at<int>(1, 4), max = stats.at<int>(1, 4);
	int min_num = 1, max_num = 1;
	for (int i = 2; i < cnt; i++) {
		int* add = stats.ptr<int>(i);
		if (min > add[4]) { //���̺��� �ּ� ����
			min = add[4];
			min_num = i;
		}
		if (max < add[4]) { //���̺��� �ִ� ����
			max = add[4];
			max_num = i;
		}
	}

	for (int i = 1; i < cnt; i++) {
		cout << i << "�� ���̺� ����: " << stats.at<int>(i, 4) << endl;
	}
	cout << endl;

	cout << "������ �ִ��� ��ü�� ���̺�: " << max_num << endl;
	cout << "�����߽�(x, y): " << setw(5) << centroids.at<double>(max_num, 0) << ", " << centroids.at<double>(max_num, 1) << endl;
	cout << "������ �ּ��� ��ü�� ���̺�: " << min_num << endl;
	cout << "�����߽�(x, y): " << setw(5) << centroids.at<double>(min_num, 0) << ", " << centroids.at<double>(min_num, 1) << endl;

	//������ �ִ�(red), �ּ�(blue) ���̺� ǥ��
	int* p = stats.ptr<int>(min_num);
	rectangle(dst, Rect(p[0], p[1], p[2], p[3]), Scalar(255, 0, 0));
	p = stats.ptr<int>(max_num);
	rectangle(dst, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 0, 255));

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	return 0;
}*/
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
	cout << "���̺� ����: " << cnt - 1 << endl;
	cout << "label" << setw(5) << 'x' << "\t" << 'y' << "\t" << "width" << "\t" << "height" << "\t" << "area" << "\t" << "color[B, G, R]" << endl;
	for (int i = 1; i < cnt; i++) {
		int* p = stats.ptr<int>(i);
		cout << i << "\t" << p[0] << "\t" << p[1] << "\t" << p[2] << "\t" << p[3] << "\t" << p[4] << "\t";
		//�� ���̺� �߽���ǥ�� �̿��� ���̺� [B, G, R] ���
		int x = cvRound(centroids.at<double>(i, 0));
		int y = cvRound(centroids.at<double>(i, 1));
		cout << src.at<Vec3b>(y, x) << endl;
		//�� ���̺� �߽���ǥ�� �̿��� ���̺� ���
		String num = format("%d", i);
		putText(src, num, Point(x, y), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255));
		//�� ���̺� ǥ��
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
		//cout << i << "�� ��ü�� �����߽�: " << Point(centroids.at<double>(i, 0), centroids.at<double>(i, 1)) << endl;
		cout << i << "�� ��ü�� �����߽�: (" << centroids.at<double>(i, 0) << ", " << centroids.at<double>(i, 1) << ")" << endl;

		//���� ����� �� ���̺��� �����߽�
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
		cout << "���� ���: " << setw(11) << "(" << (double)x_value / count << ", " << (double)y_value / count << ")" << endl << endl;
	}
	return 0;
}*/
//12-1-4
/*#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(void) {
	//�÷� ����(����)
	Mat src = imread("car.png");
	//�׷��� ����
	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY);

	Mat dst_blur;
	blur(dst, dst_blur, Size(5, 5));
	//x�� �������� 1�� ��̺��� ����
	Mat dx;
	Sobel(dst_blur, dx, -1, 1, 0);
	//����ȭ ����
	Mat binary;
	threshold(dx, binary, 110, 255, THRESH_BINARY);
	//���� ����(��ȣ�Ǹ� ��ü�� �ν�)
	Mat final;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(40, 5)); //(40 by 5) Mat ��ü�� ���
	morphologyEx(binary, final, MORPH_ERODE, Mat()); //ħ�� ������ ���� ��ü(���)�� ��� ���� ��
	morphologyEx(final, final, MORPH_CLOSE, kernel); //�ݱ� ����(��â->ħ��)�� ���� kernel ����� ���� ��ü(���)���� ����

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
