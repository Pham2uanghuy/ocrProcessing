#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <iostream>

int main()
{
    cv::Mat img = cv::imread("/home/os1611/Workspace/OpenCV/sample_form.jpg");
    if (img.empty())
    {
        std::cerr << "Không thể đọc ảnh!" << std::endl;
        return -1;
    }

    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    cv::Mat thresh;
    cv::threshold(gray, thresh, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    cv::Rect roi(100, 200, 300, 50);
    cv::Mat field = thresh(roi);

    cv::imshow("Field ROI", field);
    cv::waitKey(0);

    tesseract::TessBaseAPI tess;
    if (tess.Init(NULL, "eng"))
    {
        std::cerr << "Không thể khởi tạo Tesseract!" << std::endl;
        return -1;
    }

    tess.SetImage(field.data, field.cols, field.rows, field.channels(), field.step1());
    std::string text = std::string(tess.GetUTF8Text());

    std::cout << "Text nhận dạng: " << text << std::endl;

    return 0;
}
