#include <opencv2/opencv.hpp>
#include <iostream>
#include "window_search.hpp"
#include "cv_helper.hpp"

void window_search(cv::Mat& binary_warped, cv::Mat& window_img,
std::vector<std::unique_ptr<LaneLine>>& lane_lines, std::vector<int>& peaks,
int n_windows, int margin, int minpix) {
  // TODO: Finish this function definition
}


std::vector<std::pair<double, double>> generate_waypoints(cv::Mat& overlay_img,
std::vector<std::unique_ptr<LaneLine>>& lane_lines, double start_fraction,
double stop_fraction, int num_waypoints, int radius, double xm_per_pix,
double ym_per_pix) {
  // TODO: Finish this function defintion
  std::vector<std::pair<double, double>> waypoints_meters;

  return waypoints_meters;
}
