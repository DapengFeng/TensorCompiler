// Copyright 2017 CCFY(Dapeng Feng)
#include <fstream>
#include <sstream>

#include "imageoper.h"

namespace Tensor {
	void imageOper::fpIO(std::string &FileName, const std::string &basePathName, const std::string &fileName) {
		std::string basefilename;
		basefilename.assign(basePathName);

		std::string filename;
		filename.assign(fileName);

		size_t ntimes = 0;
		// "..\"
		std::string::size_type nPos = filename.find("..\\", 0);
		if (nPos != std::string::npos) {
			while (nPos != std::string::npos) {
				ntimes++;
				nPos = filename.find("..\\", nPos + 3);
			}
			// std::cout << ntimes << std::endl;
			while (ntimes--) {
				const std::string::size_type last_pattern_idx = basefilename.find_last_of("\\/");
				if (last_pattern_idx != std::string::npos)
				{
					basefilename.erase(last_pattern_idx, std::string::npos);
				}
				const std::string::size_type first_pattern_idx = filename.find_first_of("..\\");
				if (first_pattern_idx != std::string::npos)
				{
					filename.erase(first_pattern_idx, 3);
				}
			}
		}
		else {
			// ".\"
			nPos = filename.find(".\\", 0);
			if (nPos != std::string::npos) {
				const std::string::size_type first_pattern_idx = filename.find_first_of(".\\");
				if (first_pattern_idx != std::string::npos)
				{
					filename.erase(first_pattern_idx, 2);
				}
			}
			else {
				// ":\"
				nPos = filename.find(":\\", 0);
				if (nPos != std::string::npos) {
					FileName.assign(filename);
					return;
				}
				else {
					std::stringstream ss;
					ss << "The format of path to " << filename << " is incorrect.\n";
					std::string msg = ss.str();
					LOG(ERROR) << msg;
					throw TensorError(msg);
				}
			}
		}
		FileName = basefilename + "\\" + filename;
		return;
	}

	void imageOper::imread(Tensor* const T, const std::string &basePathName, const std::string &fileName) {
		std::string FileName;
		try {
			imageOper::fpIO(FileName, basePathName, fileName);
			cv::Mat img = cv::imread(FileName);
			if (img.empty()) {
				std::stringstream ss;
				ss << "Can't open " << FileName << "\n";
				std::string msg = ss.str();
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			T->setMatrix(img);
			/*cv::namedWindow("test");
			cv::imshow("test", img);
			cv::waitKey(0);
			cv::destroyWindow("test");*/
			LOG(INFO) << FileName << " was loaded successful!\n";
		}
		catch (std::exception ex) {
			throw ex;
		}
		return;
	}

	int imageOper::numFigure = 0;
	void imageOper::imshow(const Tensor* const T) {
		cv::Mat img = T->getMatrix();
		if (img.empty()) {
			std::stringstream ss;
			ss << "Mat is empty\n";
			std::string msg = ss.str();
			LOG(ERROR) << msg;
			throw TensorError(msg);
		}
		else {
			imageOper::numFigure++;
			std::stringstream ss;
			ss << "Figure" << imageOper::numFigure;
			cv::namedWindow(ss.str());
			cv::imshow(ss.str(), img);
			cv::waitKey(1);
		}
		return;
	}

	void imageOper::imwrite(const Tensor* const T, const std::string &basePathName, const std::string& fileName) {
		try {
			std::string FileName;
			imageOper::fpIO(FileName, basePathName, fileName);
			cv::imwrite(FileName, T->getMatrix());
			LOG(INFO) << FileName << " was written successful!\n";
		}
		catch (std::exception ex) {
			throw ex;
		}
		return;
	}
} // namespace Tensor