# Instructions
```
docker build -t lanelines .
```

This may take anywhere from 5-60 mins depending on your internet speed. Once
completed, verify the image ```lanelines``` exists by running the following
command:

```
docker images
```

Once you are on a machine with the eec193_lab1 image, run the following command to mount your container:
```
docker run -it --name=project -v <any_path_on_host_machine>:/root/lanelines lanelines
```

The ```--name``` flag creates a docker container named "project" which will
be your project environment.

The ```-v``` flag mounts a shared volume between your docker container and host machine. This will allow you to modify code files in your docker container from
your host machine. It is highly recommended that when you choose the folder
on your host machine that the folder is empty so that your project folder isn't
full of unnecessary clutter.

Whenever you wish to enter your docker container again, make sure it is running
by running the command:

```
docker container ls
```

If you don't see the container "lanelines", then you need to start it by
running the following command:
```
docker start project
```

Enter your docker container by running this command

```
docker exec -it -e DISPLAY=<IPv4_Address>:0.0 project /bin/bash
```

The ```-e``` flag passes an environment variable, which in this case is your ```DISPLAY``` variable. This is to forward your display port so you can view images from your docker container. You can find your IPv4_Address by typing ```ifconfig```.

Once inside your docker container, change to the appropriate directory.

```
cd /root/lanelines
```

## The Process
Here is a summary of every step in the pipeline.

* Compute the camera calibration matrix and distortion coefficients given a set of chessboard images.
* Apply a distortion correction to the raw input images.
* Apply a perspective transform to transform the image into a "birds-eye view."
* Use color and gradient thresholds to isolate the lane line pixels, creating a
binary image.
* Cluster the lane lines into their individual instances using the window search
algorithm
* Find the polynomial best-fit lines for each lane line
* Use the best-fit lines to generate waypoints
* Calculate other potentially helpful information such as center
offset, radii of curvature, etc.
* Use history information to smooth the best-fit lines across frames,
such as using a simple-moving average or other filtering techniques
* Warp the detected lane boundaries and waypoints back onto the original image.
* Output visual display of the lane boundaries and waypoints

## Phase 1: Camera Calibration
This project is broken into two CMake projects. The first of which is the camera
calibration. You may find this project at ```camera_calibration/```.

In order to accurately measure distance from images, we must first correct any
distortions caused by the lens of the camera. This is done by taking pictures
of a well-defined, high-contrast object at different angles: a checkerboard.
Using a set of checkerboard images, we can obtain a camera matrix and list of
distortion coefficients which can be used to undistort images from a particular
camera.

### Running the executables

This will generate the executables ```calibrate_camera```, and ```instrinsics_tester```.

To run the first executable:
```
./calibrate_camera <path_to_yaml_file> <path_to_checkerboard_images>\*.png
```

To run the second executable:
```
./intrinsics_tester <path_to_yaml_file> <path_to_checkerboard_images>\*.png
```

NOTE: you may have to change the extension to *.jpg if the images are JPEG.

Your yaml files should be saved in the top directory. For the Udacity camera,
name the yaml file ```udacity_parameters.yaml```. For the UC Davis camera,
name the yaml file ```fisheye_parameters.yaml```.

## Phase 2: Lane Line Detection
This is the real lane line detection project. It is another CMake project that
is located at ```lane_line_detection/```.

This project is purposefully broken into many subparts. Most of them with their
own module file and tester file. This is to both ensure you build your program
incrementally and to allow you to parallelize your work.

### Phase 2.1 Perspective Transformation
To more easily isolate the lane line pixels, it helps to get a birds-eye
view of the road, so we cut out unnecessary information. We do this
by performing a perspective transformation.

This is done by defining four source points which define your ground plane
and four destination points which define where your ground plane will appear
in the birds-eye view.

The goals of this part are as follows:
* Tune the source and destination points appropriately to get an accurate birds-eye view
* Save the final birds-eye view images to ```images/warped_images/``` for use in the next part

The source and destination points will be in the yaml file.
#### Running the executable

This will generate many executables. However, for this part,
you only need to worry about ```perspective_transform_tester```.

To run the executable:
```
./perspective_transform_tester <path_to_yaml_file> <path_to_test_images>\*.png
```
NOTE: you may have to change the extension to *.jpg if the images are JPEG.

### Phase 2.2 Color and Gradient Thresholds

To properly isolate the lane line pixels, you will apply color and gradient
thresholds.

#### Running the executable

This will generate many executables. However, for this part,
you only need to worry about ```thresholds_tester```.

Run this command to execute:
```
./thresholds_tester <path_to_warped_images>
```

#### Phase 2.2.1 abs_sobel_thresh
The function ```abs_sobel_thresh``` uses the Sobel algorithm to find the gradient
of the image with respect to x or y, takes the absolute value of the gradient,
and applies some upper and lower thresholds, returning some binary image.

The steps are as follows:
1. Find gradient with respect to x or y depending on input ```char orient```
2. Take absolute value of gradient
3. Normalize all values to be between 0-255
4. Convert image to type CV_8U (8-bit unnsigned cv::Mat)
5. Apply thresholds

#### Phase 2.2.2 sobel_mag_dir_thresh
The function ```sobel_mag_dir_thresh``` uses the Sobel algorithm to find the
magnitude and direction of the gradient of an image and applies some lower and
upper thresholds. So there will be two output images.

1. Find both the gradient with respect to x and y
2. Take the absolute value of the gradient images
3. Calculate the magnitude and direction of the gradient
4. Normalize the magnitude of the gradient to be between 0-255
5. Convert the magnitude of the gradient to type ```CV_8U```
6. Apply thresholds for both the magnitude and direction

### Phase 2.2.3 apply_thresholds
```apply_thresholds``` will wrap all the threshold functions you want to call into one function call.

### Phase 2.4 Window Search
To cluster the lane lines, we will use window search. Window Search is a
clustering algorithm particular to clustering lane lines. We need to be able to
cluster the different instances of lane lines to find the best-fit lines.

The goals are as follows:
* Use the window search algorithm to cluster the lane lines in the 8 test images
* Visualize the window search
* Compute the best-fit lines
* Visualize the best-fit lines
* Compute the waypoints in both pixels and meters
* Visualize the waypoints

#### Phase 2.4.1 Implementing the Window Search

The window search algorithm starts by looking at the column-wise histogram peaks
on the left and right-hand side of the binary warped image, choosing the largest
peaks for each side. The locations of these peaks are where the window searches
will start.

Once you've defined your starting position, the window search re-centers itself
based on the mean position of the non-zero pixels inside the window until it
reaches the boundaries of the image.


#### Phase 2.4.2 Calculating the Best-Fit Lines

Once you have finished window search for one lane line, we need to find the
best-fit line for that lane line. 

#### Phase 2.4.2 Generating Waypoints
Now that we have our left and right best-fit lines, we can generate waypoints
along the center-line. Not only do we need to visualize the waypoints, we need
to convert them to the proper frame of reference. While the waypoints in pixels
will have their origin at the top left corner of the image, as is standard in
computer vision, the waypoints in meters you will also be calculating will have
their origin at the bottom-center of the image.

### Phase 2.5 Putting it all Together
Now it's time for you to put everything together. There are two main files
for this project: ```images_main.cpp``` and ```video_main.cpp```. As the names
suggest, one is for testing your full pipeline on individual images that you
select. The other one is for testing your full pipeline on video.


