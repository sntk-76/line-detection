#include <opencv2/opencv.hpp>
using namespace cv;

/*Introduction: For this project, our objective is to develop a solution using OpenCV to detect street lanes.Throughout my code, I have endeavored to provide
//clear explanations for each section of the code and have made a point to clearly declare each of the implemented functions.*/



/*Step 1:
During the process of line detection using the functions introduced in our lab sessions, I encountered an issue where one of the lines that detected
the street lanes began from the top of the picture. Despite my efforts to adjust the parameters in both the 'canny()' and 'houghlines()' functions, I
was unable to find a solution to this problem. As a result, I decided to take a different approach and cut the top portion of the image to eliminate
the noise causing this distortion in the picture. I have included a function in my code, provided below, that removes 1/3 of the upper part of the
image, which I call during the execution of my program.*/


Mat areaOfInterest(Mat img)
{
    std::vector<Point> points;

    int width = img.cols;
    int height = img.rows;
    Point upperLeftPoint = Point(0, height / 3);
    Point lowerLeftPoint = Point(0, height);
    Point upperRightPoint = Point(width, height / 3);
    Point lowerRightPoint = Point(width, height);
    points.push_back(upperLeftPoint);
    points.push_back(upperRightPoint);
    points.push_back(lowerRightPoint);
    points.push_back(lowerLeftPoint);

    Mat fillMask = Mat::zeros(img.size(), img.type());
    fillPoly(fillMask, points, Scalar(255));

    Mat masked;

    bitwise_and(img, fillMask, masked);

    return masked;
}


//From this point on, we will begin the process of solving the project : 


int main(int argc, char** argv)
{
    /*To begin with, we read in the image file and store it in a `Mat` variable, which is a type of variable that saves the image in memory as an object.
    This enables us to apply various processing techniques to the image using the `Mat` object and implement different functions on it as needed.*/
    Mat input_image = imread("C:/Users/sina tavakoli/source/repos/homework/homework/road9.jpg");

    /*We now have the image stored in the 'input_image' variable, and we can proceed to apply the Canny edge detection algorithm to this image.
    The resulting output will be saved in a variable named 'edges_image'. The output of the Canny function is a binary image, where the white
    points represent edges and the black points represent non-edges. Additionally, we have set the threshold parameters for the Canny function
    as follows: threshold 1 is set to 150, and threshold 2 is set to 380. This means that any pixel intensity values below 150 will be considered
    non-edges, and any values above 380 will be considered strong edges. Pixels with values in between these two thresholds will be considered light edges.*/
    Mat edges_image;
    Canny(input_image, edges_image, 150, 380);

    /*In the first section of the code, I have defined a function that cuts off the upper portion of the input image and explained the resulting changes to the image.
    Moving on, in the code section below, I have applied the 'areaofinterest()' function to the 'edges_image' variable. This function is designed to isolate the region
    of the image that corresponds to the road and extract this area for further processing.*/
    edges_image = areaOfInterest(edges_image);


    /*After the previous image processing steps, the HoughLines transform is used to detect the lines in the edge-detected image. The function call to HoughLines takes
    the edge-detected image, "edges_image", as input and the detected lines are stored in the "lines" variable. In this implementation, a value of "2" is used for "rho"
    parameter which reduces the detection accuracy but also speeds up the algorithm. The "theta" parameter is set to the standard value of "CV_PI/180". Additionally, a
    threshold value of "310" is used for "threshold1" parameter which determines the minimum number of votes that a line needs to be detected. */
    std::vector<Vec2f> lines;
    HoughLines(edges_image, lines, 2, CV_PI / 180, 310, 0, 0);

    /*In the following step, I draw the lines that were detected in the previous step on the original image and color them in red. To do this, I use the coordinates of the
    endpoints of the detected lines to create lines that connect these points. These lines are drawn with a red color to differentiate them from the rest of the image. The
    lines are drawn with a specific angle and a length of 1500 pixels from the center of the image to both sides. This process helps to visually identify the detected lane
    lines in the original image.*/
    std::vector<Point> pts;
    Mat output = input_image.clone();
    for (size_t i = 0; i < lines.size(); i++)
    {

        float rho = lines[i][0];
        float theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1500 * (-b));
        pt1.y = cvRound(y0 + 1500 * (a));
        pt2.x = cvRound(x0 - 1500 * (-b));
        pt2.y = cvRound(y0 - 1500 * (a));
        line(output, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
        pts.push_back(pt1);
        pts.push_back(pt2);
    }

    /*In the following code section, my objective is to highlight the detected street lanes on the original input image.*/
    namedWindow("lines Image", WINDOW_NORMAL);
    imshow("lines Image", output);

    /*In the following code, I have applied a red color to the area between the two red lines to emphasize the detected road
    However, it is unfortunate that this area extends to the sky and I am unable to modify the code to improve the detection.*/
    std::vector<std::vector<Point>> poly{ pts };
    fillPoly(output, poly, Scalar(0, 0, 255));

    /*In this final part of the code, I aim to show the final image which includes the original image with the detected street lanes
    and the colored area between them. This image represents the output of the program and provides a visual representation of the detected
    street lanes for further analysis and processing.*/
    namedWindow("Output Image", WINDOW_NORMAL);
    imshow("Output Image", output);
    waitKey(0);

    return 0;
}
//---------------------REPORT------------------------------------------REPORT-------------------------------------------REPORT---------------------------------------

/*Introduction:

    The objective of this project was to develop a solution using OpenCV to detect street lanes from an image.The proposed solution utilized the standard Hough Transform to
    extract the lines representing the street lanes in the image.The pipeline included generating the edge map with the Canny algorithm, applying the Hough transform to detect
    the lines, and plotting the detected lines on the original image in red.

    Methodology :

    The program was implemented in C++ using the OpenCV library.The input image was read and stored as a Mat variable, which is a type of variable that saves the image
    in memory as an object.The Canny edge detection algorithm was applied to the image to obtain a binary image representing the edges of the objects in the image.The
    edges were then filtered to isolate the area corresponding to the road by removing the top third of the image.The standard Hough Transform was applied to detect the
    lines representing the street lanes in the image.The Hough transform parameters were hand - tuned for each image to achieve the best results.Finally, the detected
    lines were plotted on the original image in red.

    Results :

    The generated output image demonstrates that the implemented code has effectively detected the road lanes. However, upon attempting to highlight the area between
    the detected lanes in red, it was observed that the red color continues beyond the road area and into the sky. I have made several attempts to rectify this issue
    by adjusting the parameters of the various functions involved in the pipeline, but unfortunately, no significant improvement has been achieved.*/