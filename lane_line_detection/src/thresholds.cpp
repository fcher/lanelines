#include "thresholds.hpp"
#include "cv_helper.hpp"

void abs_sobel_thresh(cv::Mat& src, cv::Mat& dst, char orient, int sobel_kernel=7, int thresh_min=40, int thresh_max=100) {
  cv::Mat gray;
  cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

  if (orient == 'x') {
    // TODO: Make the appropriate call to cv::Sobel
  }
  else if (orient == 'y') {
    // TODO: Make the appropriate call to cv::Sobel
  }
  else {
    std::stringstream ss;
    ss << orient << "is invalid for argument orient. Must be either 'x' or 'y'.\n";
    throw std::runtime_error(ss.str());
  }

  /*
   * TODO:
   * Finish the rest of this function definition
   */
}

void sobel_mag_dir_thresh(cv::Mat& src, cv::Mat& mag, cv::Mat& dir, int sobel_kernel, int mag_thresh_min=40, int mag_thresh_max=100, float dir_thresh_min=0.7, float dir_thresh_max=1.3) {
  cv::Mat gray;
  cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
  /*
   * TODO:
   * Finish the rest of this function definition
   */
}

/*
 * TODO:
 * Implement your apply_thresholds function here
 */
