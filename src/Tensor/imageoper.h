// Copyright 2017 CCFY(Dapeng Feng)
#pragma once

#include "Tensor.h"

namespace Tensor {
	class imageOper {
	public:
		static int numFigure;
		void static fpIO(std::string& FileName, const std::string& basePathName, const std::string& fileName);
		void static imread(Tensor* const T, const std::string& basePathName, const std::string& fileName);
		void static imshow(const Tensor* const T);
		void static imwrite(const Tensor* const T, const std::string& basePathName, const std::string& fileName);
	}; // class imageOper
} // namespace Tensor
