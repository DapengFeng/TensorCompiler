// Copyright 2017 CCFY(Dapeng Feng)
#include "imageoper.h"

namespace Tensor {
#pragma region Macro
#define mTemp cv::Mat temp
#define tTemp (Tensor)temp
#pragma endregion

#pragma region Tensor

#pragma region Constructor
	Tensor::Tensor() {
		google::SetLogDestination(google::GLOG_INFO, "..\\..\\log\\");
		cv::Mat(0, 0, CV_64F, cv::Scalar::all(0)).copyTo(this->mat);
	}

	Tensor::Tensor(const int& n, const double& val) {
		google::SetLogDestination(google::GLOG_INFO, "..\\..\\log\\");
		try {
			if (n < 0) {
				std::string msg = "Error: Construct failed (s >= 0)";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			cv::Mat(n, n, CV_64F, cv::Scalar::all(val)).copyTo(this->mat);
		}
		catch (std::exception ex) {
			throw ex;
		}
	}

	Tensor::Tensor(const int& n, const std::vector<double>& vec) {
		google::SetLogDestination(google::GLOG_INFO, "..\\..\\log\\");
		try {
			if (n < 0) {
				std::string msg = "Error: Construct failed (s >= 0)";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			else if (n*n != vec.size()) {
				std::string msg = "Error: Construct failed (s*s == vec.size())";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			mTemp = cv::Mat(n, n, CV_64F, cv::Scalar::all(0));
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					temp.at<double>(i, j) = vec.at(i*n + j);
				}
			}
			temp.copyTo(this->mat);
		}
		catch (std::exception ex) {
			throw ex;
		}
	}

	Tensor::Tensor(const int& rows, const int& cols, const double& val) {
		google::SetLogDestination(google::GLOG_INFO, "..\\..\\log\\");
		try {
			if ((rows < 0) || (cols < 0)) {
				std::string msg = "Error: Construct failed (rows >= 0 & cols >= 0)";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			cv::Mat(rows, cols, CV_64F, cv::Scalar::all(val)).copyTo(this->mat);
		}
		catch (std::exception ex) {
			throw ex;
		}
	}

	Tensor::Tensor(const int& rows, const int& cols, const std::vector<double>& vec) {
		google::SetLogDestination(google::GLOG_INFO, "..\\..\\log\\");
		try {
			if ((rows < 0) || (cols < 0)) {
				std::string msg = "Error: Construct failed (rows >= 0 & cols >= 0)";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			else if (rows*cols != vec.size()) {
				std::string msg = "Error: Construct failed (rows*cols == vec.size())";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			mTemp = cv::Mat(rows, cols, CV_64F, cv::Scalar::all(0));
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					temp.at<double>(i, j) = vec.at(i*cols + j);
				}
			}
			temp.copyTo(this->mat);
		}
		catch (std::exception ex) {
			throw ex;
		}
	}

	Tensor::Tensor(const std::string& str) {
		google::SetLogDestination(google::GLOG_INFO, "..\\..\\log\\");
		std::string strData = str;
		size_t nsemicolon = 0;
		std::string::size_type nPos;
		nPos = strData.find("[", 0);
		if (nPos != std::string::npos) {
			strData.replace(nPos, 1, "");
		}
		nPos = strData.find("]", 0);
		if (nPos != std::string::npos) {
			strData.replace(nPos, 1, "");
		}
		nPos = strData.find(";\n", 0);
		while (nPos != std::string::npos) {
			nsemicolon++;
			strData.replace(nPos, 2, " ");
			nPos = strData.find(";\n", nPos + 2);
		}
		int rows = (int)nsemicolon + 1;
		size_t ncomma = 0;
		nPos = strData.find(",", 0);
		while (nPos != std::string::npos) {
			ncomma++;
			strData.replace(nPos, 1, " ");
			nPos = strData.find(",", nPos + 1);
		}
		int cols = ((int)ncomma + rows) / rows;
		std::vector<double> vec;
		double temp;
		std::stringstream ss;
		ss << strData;
		while (ss >> temp) {
			vec.push_back(temp);
		}
		Tensor T(rows,cols,vec);
		T.getMatrix().copyTo(this->mat);
	}

	Tensor::Tensor(const cv::Mat& mat)
	{
		google::SetLogDestination(google::GLOG_INFO, "..\\..\\log\\");
		mat.copyTo(this->mat);
	}

	Tensor::Tensor(const cv::Mat* mat) {
		google::SetLogDestination(google::GLOG_INFO, "..\\..\\log\\");
		mat->copyTo(this->mat);
	}

	Tensor::Tensor(const std::vector<std::vector<double>>& vec) {
		google::SetLogDestination(google::GLOG_INFO, "..\\..\\log\\");
		try {
			size_t rows = vec.size();
			if (rows == 0) {
				mTemp(0, 0, CV_64F);
				temp.copyTo(this->mat);
				return;
			}
			else if (rows < 0) {
				std::string msg = "Error: Construct failed (rows >= 0 & cols >= 0)";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			size_t cols = vec[0].size();
			mTemp((int)rows, (int)cols, CV_64F);
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					temp.at<double>(i, j) = vec[i][j];
				}
			}
			temp.copyTo(this->mat);
		}
		catch (std::exception ex) {
			throw ex;
		}
		
	}

	Tensor::Tensor(const Tensor& T) {
		google::SetLogDestination(google::GLOG_INFO, "..\\..\\log\\");
		T.mat.copyTo(this->mat);
	}

	Tensor::Tensor(const Tensor* T) {
		google::SetLogDestination(google::GLOG_INFO, "..\\..\\log\\");
		T->mat.copyTo(this->mat);
	}
#pragma endregion

#pragma region Destructor
	Tensor::~Tensor() {

	}
#pragma endregion


#pragma region Set
	void Tensor::setMatrix(const Tensor& T) {
		T.mat.copyTo(this->mat);
	}

	void Tensor::setMatrix(const Tensor* T) {
		T->mat.copyTo(this->mat);
	}

	void Tensor::setMatrix(const cv::Mat& mat) {
		mat.copyTo(this->mat);
	}

	void Tensor::setMatrix(const cv::Mat* mat) {
		mat->copyTo(this->mat);
	}
#pragma endregion

#pragma region Get
	cv::Mat Tensor::getMatrix() const {
		return this->mat;
	}

	std::string Tensor::toString() const{
		std::stringstream ss;
		int channels = this->Channels();
		for (int i = 0; i < channels; i++) {
			ss << this->getChannel(i);
		}
		return ss.str();
	}

	Tensor Tensor::getChannel(const int& c) const {
		try {
			if ((c < 0) || (c > this->Channels())) {
				std::string msg = "Error: Get failed (channel >= 0 & channel < Tensor::Channels())";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			std::vector<cv::Mat> Channels;
			cv::split(this->mat, Channels);
			if (Channels.empty()) {
				std::string msg = "Error: Get failed (Tensor doesn't storage any data)";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			mTemp = Channels.at(c);
			return tTemp;
		}
		catch (std::exception ex) {
			throw ex;
		}
	}

	Tensor Tensor::getRange(const int& rowRange1, const int& rowRange2, const int& colRange1, const int& colRange2) const {
		try {
			if ((rowRange1 < 0) || (rowRange1 > rowRange2) || (rowRange2 > this->Rows())) {
				std::string msg = "Error: Get failed (0 <= _rowRange.start && _rowRange.start <= _rowRange.end && _rowRange.end <= m.rows)";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			else if ((colRange1 < 0) || (colRange1 > colRange2) || (colRange2 > this->Cols())) {
				std::string msg = "Error: Get failed (0 <= _colRange.start && _colRange.start <= _colRange.end && _colRange.end <= m.cols)";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			mTemp = this->mat(cv::Range(rowRange1, rowRange2), cv::Range(colRange1, colRange2));
			return tTemp;
		}
		catch (std::exception ex) {
			throw ex;
		}
		
	}
#pragma endregion

#pragma region Image_Operation
	// Read
	void Tensor::imread(const std::string &basePathName, const std::string& fileName) {
		try {
			imageOper::imread(this, basePathName, fileName);
		}
		catch (std::exception ex) {
			throw ex;
		}
		
	}

	// Show
	void Tensor::imshow() {
		try {
			imageOper::imshow(this);
		}
		catch (std::exception ex) {
			throw ex;
		}
	}

	// Save
	void Tensor::imsave(const std::string &basePathName, const std::string& fileName) {
		imageOper::imwrite(this, basePathName, fileName);
	}

	Tensor Tensor::RGB2GRAY() const {
		try {
			if ((this->Channels() == 3) || (this->Channels() == 4)) {
				mTemp;
				cv::cvtColor(this->mat, temp, CV_RGB2GRAY);
				return tTemp;
			}
			else {
				std::string msg = "Error: rgb2gray failed (src image must be rgb or rgba)";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
		}
		catch (std::exception ex) {
			throw ex;
		}
	}
#pragma endregion

#pragma region Matrix_Operation
	// Channels
	int Tensor::Channels() const {
		try {
			int channel = this->mat.channels();
			if (channel <= 0) {
				std::string msg = "Error: Channels faied (Channels > 0)";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}	
			return channel;
		}
		catch (std::exception ex) {
			throw ex;
		}
	}

	// Rows
	int Tensor::Rows() const {
		try {
			int rows = this->mat.rows;
			if (rows < 0) {
				std::string msg = "Error: Rows faied (Rows >= 0)";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			return rows;
		}
		catch (std::exception ex) {
			throw ex;
		}
	}

	// Cols
	int Tensor::Cols() const {
		try {
			int cols = this->mat.cols;
			if (cols < 0) {
				std::string msg = "Error: Cols faied (Cols >= 0)";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			return cols;
		}
		catch (std::exception ex) {
			throw ex;
		}
	}

	// Size
	cv::Size Tensor::size() const {
		return this->mat.size();
	}

	// Min
	double Tensor::Min() const {
		int channels = this->Channels();
		int rows = this->Rows();
		int cols = this->Cols();
		double _val = (std::numeric_limits<double>::max)();
		for (int i = 0; i < channels; i++) {
			mTemp = this->getChannel(i).getMatrix();
			for (int j = 0; j < rows; j++) {
				for (int k = 0; k < cols; k++) {
					_val = MIN(_val, temp.at<double>(j, k));
				}
			}
		}
		return _val;
	}

	// Max
	double Tensor::Max() const {
		int channels = this->Channels();
		int rows = this->Rows();
		int cols = this->Cols();
		double _val = (std::numeric_limits<double>::min)();
		for (int i = 0; i < channels; i++) {
			mTemp = this->getChannel(i).getMatrix();
			for (int j = 0; j < rows; j++) {
				for (int k = 0; k < cols; k++) {
					_val = MAX(_val, temp.at<double>(j, k));
				}
			}
		}
		return _val;
	}

	// Find
	std::vector<cv::Point3i> Tensor::Find(const double& _val) const {
		int channels = this->Channels();
		int rows = this->Rows();
		int cols = this->Cols();
		std::vector<cv::Point3i> positions;
		for (int i = 0; i < channels; i++) {
			mTemp = this->getChannel(i).getMatrix();
			for (int j = 0; j < rows; j++) {
				for (int k = 0; k < cols; k++) {
					if (temp.at<double>(j, k) == _val) {
						cv::Point3i pos(i, j, k);
						positions.push_back(pos);
					}
				}
			}
		}
		return positions;
	}

	// Determinat
	double Tensor::Det() const {
		try {
			if (this->Rows() != this->Cols()) {
				std::string msg = "Error: Determinat faied (Tensor::Rows == Tensor::Cols)";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			else if (this->Channels() != 1) {
				std::string msg = "Error: Determinat faied (Tensor::Channels == 1)";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			return cv::determinant(this->mat);
		}
		catch (std::exception ex) {
			throw ex;
		}
	}

	// Transpose
	Tensor Tensor::Transpose() const {
		mTemp = this->mat.t();
		return tTemp;
	}

	// Sine
	Tensor Tensor::Sine() const {
		int channels = this->Channels();
		int rows = this->Rows();
		int cols = this->Cols();
		Tensor temp;
		std::vector<cv::Mat> Channels;
		for (int i = 0; i < channels; i++) {
			Channels.push_back(this->getChannel(i).getMatrix());
			for (int j = 0; j < rows; j++) {
				for (int k = 0; k < cols; k++) {
					Channels.at(i).at<double>(j, k) = std::sin(Channels.at(i).at<double>(j, k));
				}
			}
		}
		cv::merge(Channels, temp.mat);
		return temp;
	}

	// Cosine
	Tensor Tensor::Cosine() const {
		int channels = this->Channels();
		int rows = this->Rows();
		int cols = this->Cols();
		Tensor temp;
		std::vector<cv::Mat> Channels;
		for (int i = 0; i < channels; i++) {
			Channels.push_back(this->getChannel(i).getMatrix());
			for (int j = 0; j < rows; j++) {
				for (int k = 0; k < cols; k++) {
					Channels.at(i).at<double>(j, k) = std::cos(Channels.at(i).at<double>(j, k));
				}
			}
		}
		cv::merge(Channels, temp.mat);
		return temp;
	}

	// Inverse
	Tensor Tensor::Inv() const {
		try {
			if (this->Rows() != this->Cols()) {
				std::string msg = "Error: Inverse faied (Tensor::Rows == Tensor::Cols)";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			mTemp = this->mat.inv();
			return tTemp;
		}
		catch (std::exception ex) {
			throw ex;
		}
	}

	// Discrete Fourier Transform
	Tensor Tensor::DFT() const {
		// expend input image to optimal size
		cv::Mat padded;
		int m = cv::getOptimalDFTSize(this->Rows());
		int n = cv::getOptimalDFTSize(this->Cols());
		// on the border add zero values
		cv::copyMakeBorder(this->mat, padded, 0, m - this->Rows(), 0, n - this->Cols(), cv::BORDER_CONSTANT, cv::Scalar::all(0));

		// add to the expened another plane with zeros
		cv::Mat planes[] = { cv::Mat_<double>(padded),cv::Mat::zeros(padded.size(),CV_64F) };
		cv::Mat complexI;
		// this way teh result may fit in the source matrix
		cv::merge(planes, 2, complexI);

		cv::dft(complexI, complexI);

		/*// compute the manitude and switch to logarithimic scale
		// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
		// planes[0] = Re(DFT(I)), planes[1] = Im(DFT(I))
		cv::split(complexI, planes);
		// planes[0] = magnitude
		cv::magnitude(planes[0], planes[1], planes[0]);
		cv::Mat magI = planes[0];

		// switch to logarithmic scale
		magI += cv::Scalar::all(1);
		log(magI, magI);

		// crop the spectrum, if it has an odd number of rows or columns
		magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));

		// rearrange the quadrants of Fourier image so that the origin is at
		// the image center
		int cx = this->Cols() / 2;
		int cy = this->Rows() / 2;

		// Top-Left
		cv::Mat q0(this->mat, cv::Rect(0, 0, cx, cy));
		// Top-Right
		cv::Mat q1(this->mat, cv::Rect(cx, 0, cx, cy));
		// Bottom-Left
		cv::Mat q2(this->mat, cv::Rect(0, cy, cx, cy));
		// Bottom-Right
		cv::Mat q3(this->mat, cv::Rect(cx, cy, cx, cy));

		// swap quadrant(Top-Left with Bottom-Right)
		mTemp;
		q0.copyTo(temp);
		q3.copyTo(q0);
		temp.copyTo(q3);

		// swap quadrant(Top-Right with Bottom-Left)
		q1.copyTo(temp);
		q2.copyTo(q1);
		temp.copyTo(q2);

		// Transform the  matrix with double values into a
		// viewable image form (double between values 0 and 1)
		cv::normalize(magI, magI, 0, 1, CV_MINMAX);*/

		return (Tensor)complexI;
	}

	// Inverse Discrete Fourier Transform
	Tensor Tensor::IDFT() const {
		cv::Mat inverseTransform;
		cv::idft(this->mat, inverseTransform, cv::DFT_REAL_OUTPUT);
		cv::normalize(inverseTransform, inverseTransform, 0, 1, CV_MINMAX);
		return (Tensor)inverseTransform;
	}

	Tensor Tensor::Normalize() const {
		mTemp = this->mat;
		cv::normalize(temp, temp, 0, 1, CV_MINMAX);
		return tTemp;
	}
#pragma endregion

	// =
	Tensor& Tensor::operator = (const Tensor& T) {
		if (this == &T) {
			return *this;
		}
		else {
			T.mat.copyTo(this->mat);
		}
		return *this;
	}

#pragma region Arithmetic_Operation
	// +
	Tensor operator + (const Tensor& T1, const Tensor& T2) {
		try {
			if (T1.Rows() == 1 && T1.Cols() == 1) {
				return T1.getMatrix().at<double>(0, 0) + T2;
			}
			if (T2.Rows() == 1 && T2.Cols() == 1) {
				return T1 + T2.getMatrix().at<double>(0, 0);
			}
			if ((T1.Rows() != T2.Rows()) || (T1.Cols() != T2.Cols())) {
				std::string msg = "Error: Sizes of input arguments do not match (The operation is neither 'array op array' (where arrays have the same size and the same number of channels), nor 'array op scalar', nor 'scalar op array')";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			mTemp = T1.getMatrix() + T2.getMatrix();
			return tTemp;
		}
		catch (std::exception ex) {
			throw ex;
		}
	}
	Tensor operator + (const Tensor& T, const double& D) {
		mTemp = T.getMatrix() + D;
		return tTemp;
	}
	Tensor operator + (const double& D, const Tensor& T) {
		mTemp = D + T.getMatrix();
		return tTemp;
	}

	// -
	Tensor operator - (const Tensor& T1, const Tensor& T2) {
		try {
			if (T1.Rows() == 1 && T1.Cols() == 1) {
				return T1.getMatrix().at<double>(0, 0) - T2;
			}
			if (T2.Rows() == 1 && T2.Cols() == 1) {
				return T1 - T2.getMatrix().at<double>(0, 0);
			}
			if ((T1.Rows() != T2.Rows()) || (T1.Cols() != T2.Cols())) {
				std::string msg = "Error: Sizes of input arguments do not match (The operation is neither 'array op array' (where arrays have the same size and the same number of channels), nor 'array op scalar', nor 'scalar op array')";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			mTemp = T1.getMatrix() - T2.getMatrix();
			return tTemp;
		}
		catch (std::exception ex) {
			throw ex;
		}
	}
	Tensor operator - (const Tensor& T) {
		mTemp = -T.getMatrix();
		return tTemp;
	}
	Tensor operator - (const Tensor& T, const double& D) {
		mTemp = T.getMatrix() - D;
		return tTemp;
	}
	Tensor operator - (const double& D, const Tensor& T) {
		mTemp = D - T.getMatrix();
		return tTemp;
	}

	// *
	Tensor operator * (const Tensor& T1, const Tensor& T2) {
		try {
			if (T1.Rows() == 1 && T1.Cols() == 1) {
				return T1.getMatrix().at<double>(0, 0) * T2;
			}
			if (T2.Rows() == 1 && T2.Cols() == 1) {
				return T1 * T2.getMatrix().at<double>(0, 0);
			}
			if (T1.Cols() != T2.Rows()) {
				std::string msg = "Error: multiply failed (T1.Cols() == T2.Rows()) ";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			mTemp = T1.getMatrix() * T2.getMatrix();
			return tTemp;
		}
		catch (std::exception ex) {
			throw ex;
		}
	}
	Tensor operator * (const Tensor& T, const double& D) {
		mTemp = T.getMatrix() * D;
		return tTemp;
	}
	Tensor operator * (const double& D, const Tensor& T) {
		mTemp = D * T.getMatrix();
		return tTemp;
	}

	// /
	Tensor operator / (const Tensor& T1, const Tensor& T2) {
		try {
			if (T1.Rows() == 1 && T1.Cols() == 1) {
				return T1.getMatrix().at<double>(0, 0) / T2;
			}
			if (T2.Rows() == 1 && T2.Cols() == 1) {
				return T1 / T2.getMatrix().at<double>(0, 0);
			}
			if ((T1.Rows() != T2.Rows()) || (T1.Cols() != T2.Cols())) {
				std::string msg = "Error: Sizes of input arguments do not match (The operation is neither 'array op array' (where arrays have the same size and the same number of channels), nor 'array op scalar', nor 'scalar op array')";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			mTemp = T1.getMatrix() / T2.getMatrix();
			return tTemp;
		}
		catch (std::exception ex) {
			throw ex;
		}
	}
	Tensor operator / (const Tensor& T, const double& D) {
		mTemp = T.getMatrix() / D;
		return tTemp;
	}
	Tensor operator / (const double& D, const Tensor& T) {
		mTemp = D / T.getMatrix();
		return tTemp;
	}

	// ^
	Tensor operator ^ (const Tensor& T1, const Tensor& T2) {
		try {
			if (T2.Rows() == 1 && T2.Cols() == 1) {
				return T1 ^ T2.getMatrix().at<double>(0, 0);
			}
			if ((T1.Rows() != T2.Rows()) || (T1.Cols() != T2.Cols())) {
				std::string msg = "Error: Sizes of input arguments do not match (The operation is neither 'array op array' (where arrays have the same size and the same number of channels), nor 'array op scalar', nor 'scalar op array')";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			int rows = T1.Rows();
			int cols = T1.Cols();
			mTemp(rows, cols, CV_64F);
			cv::Mat t1 = T1.getMatrix();
			cv::Mat t2 = T2.getMatrix();
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					temp.at<double>(i, j) = std::pow(t1.at<double>(i, j), t2.at<double>(i, j));
				}
			}
			return tTemp;
		}
		catch (std::exception ex) {
			throw ex;
		}
	}

	Tensor operator ^ (const Tensor& T, const double& D) {
		int rows = T.Rows();
		int cols = T.Cols();
		mTemp(rows, cols, CV_64F);
		cv::Mat t = T.getMatrix();
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				temp.at<double>(i, j) = std::pow(t.at<double>(i, j), D);
			}
		}
		return tTemp;
	}
#pragma endregion

#pragma region Random
	Tensor rand(const int& n) {
		mTemp(n, n, CV_64F);
		cv::randu(temp, cv::Scalar::all(0.0), cv::Scalar::all(1.0));
		return tTemp;
	}

	Tensor rand(const int& x, const int& y) {
		mTemp(x, y, CV_64F);
		cv::randu(temp, cv::Scalar::all(0.0), cv::Scalar::all(1.0));
		return tTemp;
	}
#pragma endregion

#pragma region Concat
	// Horizontal
	Tensor hconcat(const Tensor& T1, const Tensor& T2) {
		try {
			if (T1.Rows() != T2.Rows()) {
				std::string msg = "Error: horizontal concat failed (T1.rows == T2.rows)";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			std::vector<cv::Mat> Set;
			Set.push_back(T1.getMatrix());
			Set.push_back(T2.getMatrix());
			mTemp;
			cv::hconcat(Set, temp);
			return tTemp;
		}
		catch (std::exception ex) {
			throw ex;
		}
	}

	// Vertical
	Tensor vconcat(const Tensor& T1, const Tensor& T2) {
		try {
			if (T1.Cols() != T2.Cols()) {
				std::string msg = "Error: vertical concat failed (T1.cols == T2.cols)";
				LOG(ERROR) << msg;
				throw TensorError(msg);
			}
			std::vector<cv::Mat> Set;
			Set.push_back(T1.getMatrix());
			Set.push_back(T2.getMatrix());
			mTemp;
			cv::vconcat(Set, temp);
			return tTemp;
		}
		catch (std::exception ex) {
			throw ex;
		}
	}
#pragma endregion

#pragma region IO_Stream
	// Std Output
	std::ostream& operator << (std::ostream& out, const Tensor& T) {
		out << T.getMatrix();
		return out;
	}

	// Std Input
	std::istream& operator >> (std::istream& in, Tensor& T) {
		int channels = T.Channels();
		int rows = T.Rows();
		int cols = T.Cols();
		double temp;
		std::vector<cv::Mat> Channels;
		cv::split(T.getMatrix(), Channels);
		for (int i = 0; i < channels; i++) {
			for (int j = 0; j < rows; j++) {
				for (int k = 0; k < cols; k++) {
					in >> temp;
					Channels.at(i).at<double>(j, k) = temp;
				}
			}
		}
		cv::merge(Channels, T.getMatrix());
		return in;
	}

	// String Output
	std::stringstream& operator << (std::stringstream& sout, const Tensor& T) {
		sout << T.getMatrix();
		return sout;
	}

	// String Input
	std::stringstream& operator >> (std::stringstream& sin, Tensor& T) {
		return sin;
	}
#pragma endregion

#pragma region GUI
	// Destory Window
	void destroyWindow(const std::string& winName) {
		cv::waitKey(0);
		if (!std::strcmp(winName.c_str(), "all")) {
			cv::destroyAllWindows();
			imageOper::numFigure = 0;
		}
		else {
			cv::destroyWindow(winName);
		}
	}
#pragma endregion

#pragma endregion

} // namespace Tensor