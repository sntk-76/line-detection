# Lane Detection with OpenCV

## Introduction

The primary objective of this project is to develop a solution using OpenCV for the detection of street lanes within an input image. This lane detection process is vital for various computer vision applications, including autonomous vehicles and driver assistance systems. In this project, we utilize OpenCV, a powerful computer vision library, to implement a lane detection pipeline.

## Methodology

### Program Implementation

- **Programming Language**: The project is implemented in C++ using the OpenCV library. OpenCV provides a wide range of tools and functions for image processing and computer vision.

- **Image Processing Pipeline**: The project involves a series of steps to detect and highlight street lanes within an image:

  1. **Image Loading**: The input image is read and stored as a 'Mat' variable, an OpenCV data type for image representation.

  2. **Edge Detection**: The Canny edge detection algorithm is applied to the input image. This step produces a binary image highlighting the edges of objects within the image.

  3. **Region of Interest (ROI) Selection**: To isolate the road area, the detected edges are filtered, excluding the top third of the image. This step narrows the focus to the region of interest (ROI), where the road lanes are expected.

  4. **Hough Transform**: The standard Hough Transform is applied to detect the lines representing the street lanes within the ROI. Hand-tuning of Hough transform parameters is performed for each image to optimize detection accuracy.

  5. **Visualization**: The detected lane lines are overlaid on the original image, highlighted in red. This final image provides a visual representation of the detected road lanes.

## Results and Challenges

The results of the project demonstrate the successful detection of road lanes. However, there is an issue with the visualization: the red color extends beyond the road area and into the sky. Multiple attempts have been made to address this problem by adjusting the parameters of the various functions involved in the pipeline, but significant improvements have not been achieved. This challenge highlights the complexity of fine-tuning parameters for different scenarios and the need for advanced image processing techniques to improve the lane detection process.

## Future Improvements

To enhance the project and address the color bleed issue, consider the following potential improvements:

- **Parameter Fine-Tuning**: Continuously experiment with and fine-tune Hough Transform parameters to improve lane detection accuracy and reduce color bleed.

- **Advanced Image Processing**: Implement more advanced image processing techniques, such as masking and filtering, to refine lane isolation within the image.

- **Visualization Techniques**: Experiment with different visualization methods, such as semi-transparent overlays, to highlight lanes without color bleed into the sky.

- **Machine Learning**: Explore the integration of machine learning models to improve lane detection accuracy under various conditions.

## Usage

1. **Prerequisites**: Ensure you have OpenCV installed in your C++ development environment.

2. **Clone the Repository**: Clone this repository to your local machine.

3. **Compilation**: Compile the C++ code with OpenCV support.

4. **Execution**: Run the compiled executable, providing your own input image for lane detection.

## Contributions

Contributions to this project are welcome. If you have suggestions or improvements, please feel free to create pull requests. We value collaboration and the community's input to enhance this project.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

 
