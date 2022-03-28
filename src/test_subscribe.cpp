
#include "camera.hpp"

ros::Subscriber Subscribe_image;

cv::Mat image;
void imageCallback(const sensor_msgs::Image::ConstPtr &scan);
void imageCallback_2(const sensor_msgs::Image::ConstPtr &scan);

int main(int argc, char**argv)
{
    ros::init(argc,argv,"giveme_image_node");
    ros::NodeHandle n;
    ros::NodeHandle nh;
    Subscribe_image=n.subscribe("camera/rgb/image_gaussian_raw",10,imageCallback);
    Subscribe_image=nh.subscribe("camera/rgb/image_resized_raw",10,imageCallback_2);

    while(ros::ok())
    {
        cv::waitKey(1);        
        ros::spinOnce();
    }
    return 0;
}
void imageCallback(const sensor_msgs::Image::ConstPtr &scan)
{
    sensor_msgs::Image my_image;
    std::cout <<"a"<<std::endl;
    my_image=*scan;
    cv_bridge::CvImagePtr matrix_ptr = cv_bridge::toCvCopy(my_image,"bgr8");
    image=matrix_ptr->image;
    cv::namedWindow("gaussian_image_recieve");
    cv::moveWindow("gaussian_image_recieve",100,0);
    cv::imshow("gaussian_image_recieve",image);
}

void imageCallback_2(const sensor_msgs::Image::ConstPtr &scan)
{
    sensor_msgs::Image my_image;
    std::cout <<"b"<<std::endl;
    my_image=*scan;
    cv_bridge::CvImagePtr matrix_ptr = cv_bridge::toCvCopy(my_image,"bgr8");
    image=matrix_ptr->image;
    cv::namedWindow("resized_image_recieve");
    cv::moveWindow("resized_image_recieve",100+my_image.width,0);
    cv::imshow("resized_image_recieve",image);
}
