#include <iostream>

#include "Tensor.h"

using std::cout;
using std::cin;
#define PAUSE system("pause")

DEFINE_bool(use_OpenCV, true, "Whether to use OpenCV");

int main(int argc, char** argv) {
	google::ParseCommandLineFlags(&argc, &argv, true);
	google::InitGoogleLogging(argv[0]);
	google::SetLogDestination(google::GLOG_INFO, "..\\..\\log\\");

	int x,y;
	while (cin >> x >> y) {
		try {
			std::vector<double> vec(x*y, 2);
			Tensor::Tensor t1(x, y,vec);
			Tensor::Tensor t2(x, y, 1.0);
			cout << (t1 ^ t2) << "\n";
			cout << (t1 ^ 2) << "\n";
			cout << Tensor::rand(x, y) << "\n";
			std::stringstream ss;
			ss << t1;
			std::string str = ss.str();
			cout << str << "\n";
			Tensor::Tensor t3(str);
			cout << t3 << "\n";
			str = "2";
			Tensor::Tensor t4(str);
			cout << t4 << "\n";
			Tensor::Tensor img;
			img.imread("D:\\Tensor", ".\\test.jpg");
			img.imshow();
			img = img.getRange(0, 10, 0, 10);
			img.imshow();
			cout << img.toString() << "\n";
			for (int i = 0; i < 3; i++) {
				cout << img.getChannel(i) << "\n";
			}
			img.RGB2GRAY().imshow();
			img.imsave("D:\\Tensor", ".\\rkobe.jpg");
			//Tensor::Tensor(*p)(const Tensor::Tensor&, const Tensor::Tensor&) = Function.mapFunction["hconcat"];
			//Tensor::Tensor(*p)(const Tensor::Tensor&, const Tensor::Tensor&)(t1, t2);
			//cout << t1 - t2 << "\n";
			//cout << -t2 << "\n";
			//cout << t1 * t2 << "\n";
			//cout << t2.Inv() << "\n";
			/*cout << t2 * -1 << "\n";
			cout << -1 * t2 << "\n";
			cout << t2 / 0 << "\n";
			cout << 0 / t2 << "\n";
			cout << t1 + 3 << "\n";*/
			/*std::stringstream ss;
			ss << t1;
			std::string str = ss.str();
			cout << str << "\n";
			Tensor::Tensor t3;
			t3.imread("D:\\Tensor", ".\\test.jpg");
			t3.imshow();
			Tensor::destroyWindow("all");
			cout << t1 + t1 * t2 << "\n";*/
			//cout << t2.Det() << "\n";
			//cout << Tensor::hconcat(t1, t2) << "\n";
		}
		catch (std::exception ex){
			std::cerr << ex.what() << "\n";
			continue;
		}
	}
	
	PAUSE;
	return 0;
}