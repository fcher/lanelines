#include <opencv2/opencv.hpp>
#include <iostream>
#include <matplotlibcpp.h>
#include "overloader.hpp"
#include "cv_helper.hpp"
#include "thresholds.hpp"
#include "window_search.hpp"
#include "signal_proc.hpp"
#include "lane_line.hpp"

namespace plt = matplotlibcpp;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./window_search_tester <path_to_thresholded_images\\*.png> \n";
    return 1;
  }
  std::vector<cv::String> image_paths;
  cv::glob(argv[1], image_paths);
  cv::Mat binary_warped, histogram;

  binary_warped = cv::imread(image_paths[0], CV_LOAD_IMAGE_GRAYSCALE);

  std::vector<int> peaks;
  peaks = findPeaks(binary_warped, histogram);
  // Feel free to comment out the lines below. They are for visualizing histogram.
  std::vector<double> histogram_vis;
  histogram.copyTo(histogram_vis);
  plt::plot(histogram_vis);
  plt::show();

}
