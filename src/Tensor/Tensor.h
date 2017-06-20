// Copyright 2017 CCFY(Dapeng Feng)
#pragma once
#pragma warning(disable:4996)

#pragma region Header
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <opencv2\opencv.hpp>
#endif // !_CRT_SECURE_NO_WARNINGS

#ifndef GOOGLE_GLOG_DLL_DECL
#define GOOGLE_GLOG_DLL_DECL
#ifndef GLOG_NO_ABBREVIATED_SEVERITIES
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog\logging.h>
#endif // !GLOG_NO_ABBREVIATED_SEVERITIES
#endif // !GOOGLE_GLOG_DLL_DECL
#pragma endregion


namespace Tensor {
#pragma region Tensor

	class Tensor {
#pragma region public
	public:
#pragma region Constructor
		Tensor();
		Tensor(const int& n, const double& val = 0);
		Tensor(const int& n, const std::vector<double>& vec);
		Tensor(const int& rows, const int& cols, const double& val = 0);
		Tensor(const int& rows, const int& cols, const std::vector<double>& vec);
		explicit Tensor(const std::string& str);
		explicit Tensor(const cv::Mat& mat);
		explicit Tensor(const cv::Mat* mat);
		explicit Tensor(const std::vector<std::vector<double>>& vec);
		Tensor(const Tensor& T);
		Tensor(const Tensor* T);
#pragma endregion

#pragma region Destructor
		~Tensor();
#pragma endregion

#pragma region Set
		void setMatrix(const Tensor& T);
		void setMatrix(const Tensor* T);
		void setMatrix(const cv::Mat& mat);
		void setMatrix(const cv::Mat* mat);
#pragma endregion

#pragma region Get
		/** @brief Return the matrix

		Get the whole channels of the matrix.
		The only way to transfer a Tensor to cv::Mat
		@param null.
		*/
		cv::Mat getMatrix() const;

		std::string toString() const;

		/** @brief Return the channnel of the matrix
		Get a specific channel of the 3D matrix
		@param c Channel of the matrix
		+ For example, a RGB matrix,
		+ c = 0, stands for the Blue channel
		+ c = 1, stands for the Green channel
		+ c = 2, stands for the Red channel
		*/
		Tensor getChannel(const int& c) const;

		/** @brief Return the region of the matrix

		The mothed will return a region of the matrix. And the four params is used to specify a row or a column span in a matrix ( Mat )
		and for many other purposes. Range(a,b) is basically the same as a:b in Matlab or a..b in Python. As in Python,
		start is an inclusive left boundary of the range and end is an exclusive right boundary of the range. Such a half-opened interval
		is usually denoted as \f$[start,end)\f$ .
		@param rowRange1 The row number of start
		@param rowRange2 The row number of end
		@param colRange1 The col number of start
		@param colRange2 The col number of end
		*/
		Tensor getRange(const int& rowRange1, const int& rowRange2, const int& colRange1, const int& colRange2) const;

#pragma endregion

#pragma region Image_Operation
		/** @brief Loads an image from a file.

		@anchor imread

		The function imread loads an image from the specified file and returns it. If the image cannot be
		read (because of missing file, improper permissions, unsupported or invalid format), the function
		returns an empty matrix ( Mat::data==NULL ).

		Currently, the following file formats are supported:

		-   Windows bitmaps - \*.bmp, \*.dib (always supported)
		-   JPEG files - \*.jpeg, \*.jpg, \*.jpe (see the *Notes* section)
		-   JPEG 2000 files - \*.jp2 (see the *Notes* section)
		-   Portable Network Graphics - \*.png (see the *Notes* section)
		-   WebP - \*.webp (see the *Notes* section)
		-   Portable image format - \*.pbm, \*.pgm, \*.ppm \*.pxm, \*.pnm (always supported)
		-   Sun rasters - \*.sr, \*.ras (always supported)
		-   TIFF files - \*.tiff, \*.tif (see the *Notes* section)
		-   OpenEXR Image files - \*.exr (see the *Notes* section)
		-   Radiance HDR - \*.hdr, \*.pic (always supported)
		-   Raster and Vector geospatial data supported by Gdal (see the *Notes* section)

		@note

		-   The function determines the type of an image by the content, not by the file extension.
		-   In the case of color images, the decoded images will have the channels stored in **B G R** order.
		-   On Microsoft Windows\* OS and MacOSX\*, the codecs shipped with an OpenCV image (libjpeg,
		libpng, libtiff, and libjasper) are used by default. So, OpenCV can always read JPEGs, PNGs,
		and TIFFs. On MacOSX, there is also an option to use native MacOSX image readers. But beware
		that currently these native image loaders give images with different pixel values because of
		the color management embedded into MacOSX.
		-   On Linux\*, BSD flavors and other Unix-like open-source operating systems, OpenCV looks for
		codecs supplied with an OS image. Install the relevant packages (do not forget the development
		files, for example, "libjpeg-dev", in Debian\* and Ubuntu\*) to get the codec support or turn
		on the OPENCV_BUILD_3RDPARTY_LIBS flag in CMake.
		-   In the case you set *WITH_GDAL* flag to true in CMake and @ref IMREAD_LOAD_GDAL to load the image,
		then [GDAL](http://www.gdal.org) driver will be used in order to decode the image by supporting
		the following formats: [Raster](http://www.gdal.org/formats_list.html),
		[Vector](http://www.gdal.org/ogr_formats.html).
		-   If EXIF information are embedded in the image file, the EXIF orientation will be taken into account
		and thus the image will be rotated accordingly except if the flag @ref IMREAD_IGNORE_ORIENTATION is passed.
		@param basePathName Base path to the working direcotry
		@param fileName A given name of the file
		*/
		void imread(const std::string &basePathName, const std::string& fileName);

		/** @brief Displays an image in the specified window.

		The function imshow displays an image in the specified window. The function may scale the image, depending on its depth:

		-   If the image is 8-bit unsigned, it is displayed as is.
		-   If the image is 16-bit unsigned or 32-bit integer, the pixels are divided by 256. That is, the
		value range [0,255\*256] is mapped to [0,255].
		-   If the image is 32-bit floating-point, the pixel values are multiplied by 255. That is, the
		value range [0,1] is mapped to [0,255].

		@note

		[__Windows Backend Only__] Pressing Ctrl+C will copy the image to the clipboard.

		[__Windows Backend Only__] Pressing Ctrl+S will show a dialog to save the image.

		@param null.
		*/
		void imshow();

		/** @brief Saves an image to a specified file.

		The function imwrite saves the image to the specified file. The image format is chosen based on the
		filename extension (see Tensor::imread for the list of extensions). Only 8-bit (or 16-bit unsigned (CV_16U)
		in case of PNG, JPEG 2000, and TIFF) single-channel or 3-channel (with 'BGR' channel order) images
		can be saved using this function.

		It is possible to store PNG images with an alpha channel using this function. To do this, create
		8-bit (or 16-bit) 4-channel image BGRA, where the alpha channel goes last. Fully transparent pixels
		should have alpha set to 0, fully opaque pixels should have alpha set to 255/65535.
		@param basePathName Base path to the working direcotry
		@param fileName A given name of the file
		*/
		void imsave(const std::string &basePathName, const std::string& fileName);

		Tensor RGB2GRAY() const;
#pragma endregion

#pragma region Matrix_Operation
		/** @brief Return the channel-number of the matrix.

		The number of channels
		@param null.
		*/
		int Channels() const;

		/** @brief Return the row-number of the matrix.

		The number of rows or -1 when the matrix has more than 2 dimensions
		@param null.
		*/
		int Rows() const;

		/** @brief Return the col-number of the matrix.

		The number of cols or -1 when the matrix has more than 2 dimensions
		@param null.
		*/
		int Cols() const;

		/** @brief Return the [col-number x row-number]of the matrix.

		The number of [cols x rows] or [-1 x -1] when the matrix has more than 2 dimensions
		@param null.
		*/
		cv::Size size() const;

		/** @brief Finds global minimum
		@param null.
		*/
		double Min() const;

		/** @brief Finds global maximum
		@param null.
		*/
		double Max() const;

		/** @brief Finds global position

		The method find the global position of the special value
		@param _val The value of the element.
		*/
		std::vector<cv::Point3i> Find(const double& _val) const;

		/** @brief Returns the determinant of a square floating-point matrix.

		The function calculates and returns the determinant of the
		specified matrix. For small matrices ( mtx.cols=mtx.rows\<=3 ), the
		direct method is used. For larger matrices, the function uses LU
		factorization with partial pivoting.

		For symmetric positively-determined matrices, it is also possible to use
		eigen decomposition to calculate the determinant.
		@param null.
		*/
		double Det() const;

		/** @brief Transposes a matrix.

		The method performs matrix transposition by means of matrix expressions. It does not perform the
		actual transposition but returns a temporary matrix transposition object that can be further used as
		a part of more complex matrix expressions or can be assigned to a matrix:
		@code
		Mat A1 = A + Mat::eye(A.size(), A.type())*lambda;
		Mat C = A1.t()*A1; // compute (A + lambda*I)^t * (A + lamda*I)
		@endcode
		*/
		Tensor Transpose() const;

		/** @brief Return the sine of the matrix

		The method performs element sine of the matrix.
		@param null.
		*/
		Tensor Sine() const;

		/** @brief Return the cosine of the matrix

		The method performs element cosine of the matrix.
		@param null.
		*/
		Tensor Cosine() const;

		/** @brief Inverses a matrix.

		The method performs a matrix inversion by means of matrix expressions. This means that a temporary
		matrix inversion object is returned by the method and can be used further as a part of more complex
		matrix expressions or can be assigned to a matrix.
		@param null.
		*/
		Tensor Inv() const;

		/** @brief Performs a forward Discrete Fourier transform of a 1D or 2D floating-point array.

		The function cv::dft performs one of the following:
		-   Forward the Fourier transform of a 1D vector of N elements:
		\f[Y = F^{(N)}  \cdot X,\f]
		where \f$F^{(N)}_{jk}=\exp(-2\pi i j k/N)\f$ and \f$i=\sqrt{-1}\f$
		-   Inverse the Fourier transform of a 1D vector of N elements:
		\f[\begin{array}{l} X'=  \left (F^{(N)} \right )^{-1}  \cdot Y =  \left (F^{(N)} \right )^*  \cdot y  \\ X = (1/N)  \cdot X, \end{array}\f]
		where \f$F^*=\left(\textrm{Re}(F^{(N)})-\textrm{Im}(F^{(N)})\right)^T\f$
		-   Forward the 2D Fourier transform of a M x N matrix:
		\f[Y = F^{(M)}  \cdot X  \cdot F^{(N)}\f]
		-   Inverse the 2D Fourier transform of a M x N matrix:
		\f[\begin{array}{l} X'=  \left (F^{(M)} \right )^*  \cdot Y  \cdot \left (F^{(N)} \right )^* \\ X =  \frac{1}{M \cdot N} \cdot X' \end{array}\f]

		In case of real (single-channel) data, the output spectrum of the forward Fourier transform or input
		spectrum of the inverse Fourier transform can be represented in a packed format called *CCS*
		(complex-conjugate-symmetrical). It was borrowed from IPL (Intel\* Image Processing Library). Here
		is how 2D *CCS* spectrum looks:
		\f[\begin{bmatrix} Re Y_{0,0} & Re Y_{0,1} & Im Y_{0,1} & Re Y_{0,2} & Im Y_{0,2} &  \cdots & Re Y_{0,N/2-1} & Im Y_{0,N/2-1} & Re Y_{0,N/2}  \\ Re Y_{1,0} & Re Y_{1,1} & Im Y_{1,1} & Re Y_{1,2} & Im Y_{1,2} &  \cdots & Re Y_{1,N/2-1} & Im Y_{1,N/2-1} & Re Y_{1,N/2}  \\ Im Y_{1,0} & Re Y_{2,1} & Im Y_{2,1} & Re Y_{2,2} & Im Y_{2,2} &  \cdots & Re Y_{2,N/2-1} & Im Y_{2,N/2-1} & Im Y_{1,N/2}  \\ \hdotsfor{9} \\ Re Y_{M/2-1,0} &  Re Y_{M-3,1}  & Im Y_{M-3,1} &  \hdotsfor{3} & Re Y_{M-3,N/2-1} & Im Y_{M-3,N/2-1}& Re Y_{M/2-1,N/2}  \\ Im Y_{M/2-1,0} &  Re Y_{M-2,1}  & Im Y_{M-2,1} &  \hdotsfor{3} & Re Y_{M-2,N/2-1} & Im Y_{M-2,N/2-1}& Im Y_{M/2-1,N/2}  \\ Re Y_{M/2,0}  &  Re Y_{M-1,1} &  Im Y_{M-1,1} &  \hdotsfor{3} & Re Y_{M-1,N/2-1} & Im Y_{M-1,N/2-1}& Re Y_{M/2,N/2} \end{bmatrix}\f]

		In case of 1D transform of a real vector, the output looks like the first row of the matrix above.
		@param null.
		*/
		Tensor DFT() const;

		/** @brief Performs a inverse Discrete Fourier transform of a 1D or 2D floating-point array.

		The function cv::dft performs one of the following:
		-   Forward the Fourier transform of a 1D vector of N elements:
		\f[Y = F^{(N)}  \cdot X,\f]
		where \f$F^{(N)}_{jk}=\exp(-2\pi i j k/N)\f$ and \f$i=\sqrt{-1}\f$
		-   Inverse the Fourier transform of a 1D vector of N elements:
		\f[\begin{array}{l} X'=  \left (F^{(N)} \right )^{-1}  \cdot Y =  \left (F^{(N)} \right )^*  \cdot y  \\ X = (1/N)  \cdot X, \end{array}\f]
		where \f$F^*=\left(\textrm{Re}(F^{(N)})-\textrm{Im}(F^{(N)})\right)^T\f$
		-   Forward the 2D Fourier transform of a M x N matrix:
		\f[Y = F^{(M)}  \cdot X  \cdot F^{(N)}\f]
		-   Inverse the 2D Fourier transform of a M x N matrix:
		\f[\begin{array}{l} X'=  \left (F^{(M)} \right )^*  \cdot Y  \cdot \left (F^{(N)} \right )^* \\ X =  \frac{1}{M \cdot N} \cdot X' \end{array}\f]

		In case of real (single-channel) data, the output spectrum of the forward Fourier transform or input
		spectrum of the inverse Fourier transform can be represented in a packed format called *CCS*
		(complex-conjugate-symmetrical). It was borrowed from IPL (Intel\* Image Processing Library). Here
		is how 2D *CCS* spectrum looks:
		\f[\begin{bmatrix} Re Y_{0,0} & Re Y_{0,1} & Im Y_{0,1} & Re Y_{0,2} & Im Y_{0,2} &  \cdots & Re Y_{0,N/2-1} & Im Y_{0,N/2-1} & Re Y_{0,N/2}  \\ Re Y_{1,0} & Re Y_{1,1} & Im Y_{1,1} & Re Y_{1,2} & Im Y_{1,2} &  \cdots & Re Y_{1,N/2-1} & Im Y_{1,N/2-1} & Re Y_{1,N/2}  \\ Im Y_{1,0} & Re Y_{2,1} & Im Y_{2,1} & Re Y_{2,2} & Im Y_{2,2} &  \cdots & Re Y_{2,N/2-1} & Im Y_{2,N/2-1} & Im Y_{1,N/2}  \\ \hdotsfor{9} \\ Re Y_{M/2-1,0} &  Re Y_{M-3,1}  & Im Y_{M-3,1} &  \hdotsfor{3} & Re Y_{M-3,N/2-1} & Im Y_{M-3,N/2-1}& Re Y_{M/2-1,N/2}  \\ Im Y_{M/2-1,0} &  Re Y_{M-2,1}  & Im Y_{M-2,1} &  \hdotsfor{3} & Re Y_{M-2,N/2-1} & Im Y_{M-2,N/2-1}& Im Y_{M/2-1,N/2}  \\ Re Y_{M/2,0}  &  Re Y_{M-1,1} &  Im Y_{M-1,1} &  \hdotsfor{3} & Re Y_{M-1,N/2-1} & Im Y_{M-1,N/2-1}& Re Y_{M/2,N/2} \end{bmatrix}\f]

		In case of 1D transform of a real vector, the output looks like the first row of the matrix above.
		@param null.
		*/
		Tensor IDFT() const;

		/** @brief Normalizes the norm or value range of an array.

		The function Tensor::normalize normalizes scale and shift the input array elements so that
		\f[\| \texttt{dst} \| _{L_p}= \texttt{alpha}\f]
		(where p=Inf, 1 or 2) when normType=NORM_INF, NORM_L1, or NORM_L2, respectively; or so that
		\f[\min _I  \texttt{dst} (I)= \texttt{alpha} , \, \, \max _I  \texttt{dst} (I)= \texttt{beta}\f]

		when normType=NORM_MINMAX (for dense arrays only). The optional mask specifies a sub-array to be
		normalized. This means that the norm or min-n-max are calculated over the sub-array, and then this
		sub-array is modified to be normalized.

		In case of sparse matrices, only the non-zero values are analyzed and transformed. Because of this,
		the range transformation for sparse matrices is not allowed since it can shift the zero level.
		@param null.
		*/
		Tensor Normalize() const;

#pragma endregion

		Tensor& operator = (const Tensor& T);
#pragma endregion

#pragma region private
	private:
		cv::Mat mat;
#pragma endregion

	}; // class Tensor

#pragma region Arithmetic_operation
	Tensor operator + (const Tensor& T1, const Tensor& T2);
	Tensor operator + (const Tensor& T, const double& D);
	Tensor operator + (const double& D, const Tensor& T);
	Tensor operator - (const Tensor& T1, const Tensor& T2);
	Tensor operator - (const Tensor& T);
	Tensor operator - (const Tensor& T, const double& D);
	Tensor operator - (const double& D, const Tensor& T);
	Tensor operator * (const Tensor& T1, const Tensor& T2);
	Tensor operator * (const Tensor& T, const double& D);
	Tensor operator * (const double& D, const Tensor& T);
	Tensor operator / (const Tensor& T1, const Tensor& T2);
	Tensor operator / (const Tensor& T, const double& D);
	Tensor operator / (const double& D, const Tensor& T);
	Tensor operator ^ (const Tensor& T1, const Tensor& T2);
	Tensor operator ^ (const Tensor& T, const double& D);
#pragma endregion

#pragma region Random
	Tensor rand(const int& n);
	Tensor rand(const int& x, const int& y);
#pragma endregion

#pragma region Concat
	/** @brief Applies horizontal concatenation to given matrices.

	The function horizontally concatenates two Tensor matrices (with the same number of rows).
	@param T1 the first Tensor
	@param T2 the second Tensor
	*/
	Tensor hconcat(const Tensor& T1, const Tensor& T2);

	/** @brief Applies vertical concatenation to given matrices.

	The function vertically concatenates two Tensor matrices (with the same number of cols).
	@param T1 the first Tensor
	@param T2 the second Tensor
	*/
	Tensor vconcat(const Tensor& T1, const Tensor& T2);
#pragma endregion

#pragma region IO_Stream
	// Std Output
	std::ostream& operator << (std::ostream& out, const Tensor& T);

	// Std Input
	std::istream& operator >> (std::istream& in, Tensor& T);

	// String Output
	std::stringstream& operator << (std::stringstream& sout, const Tensor& T);

	// String Input
	std::stringstream& operator >> (std::stringstream& sin, Tensor& T);
#pragma endregion

#pragma region GUI
	/** @brief Destroys the window.

	The function destroyWindow destroys the window with the given name. When name is "all",
	The function will destroy all windows opened before.

	@param winname Name of the window to be destroyed.
	*/
	void destroyWindow(const std::string& winName);
#pragma endregion

#pragma endregion

#pragma region TensorError
	class TensorError
		:public std::exception
	{
	public:
		typedef std::exception _Mybase;

		explicit TensorError(const std::string& msg)
			:_Mybase(msg.c_str())
		{ // construct from message string
		}

		explicit TensorError(const char* msg)
			: _Mybase(msg)
		{ // construct from message string
		}

	}; // class TensorError
#pragma endregion

} // namespace Tensor