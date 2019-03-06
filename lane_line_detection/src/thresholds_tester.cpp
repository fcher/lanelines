#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include "cv_helper.hpp"
#include "overloader.hpp"
#include "thresholds.hpp"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./thresholds_tester > <path_to_warped_images\\*.png> \n";
    return 1;
  }

  // create save path for final thresholded images
  std::string save_path = "../images/thresholded_images/";
  if (!boost::filesystem::exists(save_path)) {
    boost::filesystem::create_directory(save_path);
  }
  std::vector<cv::String> image_paths;
  cv::glob(argv[1], image_paths);

  /*
   * TODO:
   * This is your playground for tuning thresholds. Do whatever you want here
   * initially. But the final program should run your apply_thresholds function
   * in a for-loop on all test images, visualize the results, and save them
   * to ../images/thresholded_images/
   */

}
