## Introduction

This is a project for LiDAR to camera calibration， including automatic calibration and manual calibration.

## Prerequisites

- Cmake
- opencv 2.4
- eigen 3
- PCL 1.9
- Pangolin

## Compile
Compile in their respective folders

```shell
# mkdir build
mkdir -p build && cd build
# build
cmake .. && make
```

## Usage
1. Four input files: 

   ```
   Usage: ./run_lidar2camera <image_path> <pcd_path> <intrinsic_extrinsic_json>
   ```
+ **image_path:** image file from the Camera sensor
+ **pcd_path:** PCD file from the Lidar sensor
+ **intrinsic_extrinsic_json**: Camera intrinsic and extrinsic parameter JSON file


2. Run the test sample:

   The executable file is under the bin folder.

   ```
   cd ~./manual_calib/
   ./bin/run_lidar2camera ./data/test.png ./data/test.pcd ./data/test.json
   ```

3. Calibration panel:

   The calibration window consists of the left control panel for manual calibration and the right point cloud projection image. Users can check whether the points cloud and the image are aligned by clicking the corresponding button in the panel or using Keyboard as input to adjust the extrinsic parameter. When the points cloud and the image are aligned, the calibration ends, click the save button to save the result.  

   | Extrinsic Params | Keyboard_input | Extrinsic Params | Keyboard_input |
   | :--------------: | :------------: | :--------------: | :------------: |
   |    +x degree     |       q        |    -x degree     |       a        |
   |    +y degree     |       w        |    -y degree     |       s        |
   |    +z degree     |       e        |    -z degree     |       d        |
   |     +x trans     |       r        |     -x trans     |       f        |
   |     +y trans     |       t        |     -y trans     |       g        |
   |     +z trans     |       y        |     -z trans     |       h        |

   | Intrinsic Params | Keyboard_input | Intrinsic Params | Keyboard_input |
   | :--------------: | :------------: | :--------------: | :------------: |
   |       + fy       |       i        |       - fy       |       k        |
   |       + fx       |       u        |       - fx       |       j        |

   ```Intensity Color```: LiDAR intensity is recorded as the return strength of a laser beam, partly based on the reflectivity of the object struck by the laser pulse. This button can change the display mode to intensity map display mode. This can help to check if the ground lane lines are aligned.

   ```	Overlap Filter```: Eliminate overlap Lidar points within a depth of 0.4m. 

   ``deg step`` ``t step `` ``fxfy scale`` : These three buttons change the adjustment step for every click or keyboard input.

   ``point size``: Adjust the size of Lidar points in the projection image.

   ``Reset``:  Press button to reset all manual adjustment.

   ``Save Image``:  If the this button was pressed, the results (calibrated image,  extrinsic and intrinsic matrix) are stored by default at running directory `~./manual_calib/`:


