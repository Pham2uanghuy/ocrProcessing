#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <iostream>
#include <leptonica/allheaders.h>
#include <string.h>

int main()
{
    std::string outText;
    cv::Mat img = cv::imread("./images/vietnameseText.webp", cv::IMREAD_COLOR);
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();

    api->Init(NULL, "vie", tesseract::OEM_LSTM_ONLY);
    api->SetPageSegMode(tesseract::PSM_AUTO);
    api->SetImage(img.data, img.cols, img.rows, 3, img.step);
    outText = std::string(api->GetUTF8Text());
    std::cout << outText;
    api->End();
    return 0;
}
