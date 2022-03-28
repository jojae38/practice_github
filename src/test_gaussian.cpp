#include "camera.hpp"
#include <math.h>
using namespace std;
#define PI 3.141592

void show_img(cv::Mat *image,int x,int y,string window_name);
void My_gaussian_func(cv::Mat *org_img,cv::Mat *gaussian_image,int size, float sigma,vector<vector<double>> &filter);
double getKernal(int size,float sigma,int x,int y,double z);
int main()
{
    int size;
    float sigma;
    int base_line=100;
    int pic_size=0;
    cout << "Test Gaussian Filter"<<endl;
    while(true)
    {
        cout << "Input Size(odd_num): ";
        cin >> size;
        if(size%2==1)
            break;
        else
            cout <<"Size must be odd num"<<endl;
    }
    cout << "Input Sigma: ";
    cin>> sigma;
    vector<vector<double>> filter(size,vector<double>(size,0));

    cv::Mat org_img;
    cv::Mat gaussian_func_img;
    cv::Mat my_gaussian_func_img;
    

    org_img=cv::imread("/home/cona/Pictures/lena.jpeg");

    // my_gaussian_func_img.zeros(org_img.rows,org_img.cols,org_img.type());
    my_gaussian_func_img = cv::Mat::zeros(org_img.rows, org_img.cols, org_img.type());
    //std::cout << my_gaussian_func_img.rows << std::endl << my_gaussian_func_img.cols << std::endl;
    
    cv::GaussianBlur(org_img,gaussian_func_img,cv::Size(),sigma);
    My_gaussian_func(&org_img,&my_gaussian_func_img,size,sigma,filter);
    pic_size=org_img.rows;
    while(true)
    {
        show_img(&org_img,base_line+pic_size*0,0,"org_img");
        show_img(&gaussian_func_img,base_line+pic_size*1,0,"gaussian_func_img");
        show_img(&my_gaussian_func_img,base_line+pic_size*2,0,"my_gaussian_func_img");
        if(cv::waitKey(10)==27)
        break;
    }
    
    return 0;
}
void show_img(cv::Mat *image,int x,int y,string window_name)
{
    cv::namedWindow(window_name);
    cv::moveWindow(window_name,x,y);
    cv::imshow(window_name,*image);
}
void My_gaussian_func(cv::Mat *org_img,cv::Mat *gaussian_image,int size, float sigma,vector<vector<double>> &filter)
{
    double x=(size-1)/2;
    double y=(size-1)/2;
    double z=1./(2*PI*sigma*sigma);
    double sum=0;
    
    cout <<"filter"<<endl;
    for(double i=0;i<size;i++)
    {
        for(double j=0;j<size;j++)
        {
            filter[i][j]=getKernal(size,sigma,abs(x-i),abs(y-j),z);
            cout <<setw(10)<<filter[i][j];
            sum+=filter[i][j];
        }
        cout <<endl;
    }
    cout <<"filter sum is: "<<sum<<endl;
    double summ=0;
    for(int i=0;i<size;i++)
    {
        summ=0;
        for(int j=0;j<size;j++)
        {
            summ+=filter[i][j];
            
        }
        cout <<summ<<endl;
    }
    for(int row=0;row<org_img->rows;row++)
    {
        for(int col=0;col<org_img->cols;col++)
        {
            if(row>x&&row<org_img->rows-x-1&&col>y&&col<org_img->cols-y-1)
            {
                double b=0;
                double r=0;
                double g=0;
                for(int i=0;i<size;i++)
                {
                    for(int j=0;j<size;j++)
                    {
                        double b_temp=org_img->at<cv::Vec3b>(row-size+i,col-size+j)[0]*filter[i][j];
                        double r_temp=org_img->at<cv::Vec3b>(row-size+i,col-size+j)[1]*filter[i][j];
                        double g_temp=org_img->at<cv::Vec3b>(row-size+i,col-size+j)[2]*filter[i][j];
                        b+=b_temp;
                        r+=r_temp;
                        g+=g_temp;
                    }
                }
                //cout <<int(b)<<"  "<<int(r)<<"  "<<int(g)<<endl;
                gaussian_image->at<cv::Vec3b>(row,col)[0]+=int(b);
                gaussian_image->at<cv::Vec3b>(row,col)[1]+=int(r);
                gaussian_image->at<cv::Vec3b>(row,col)[2]+=int(g);
            }
            else
            {
                gaussian_image->at<cv::Vec3b>(row,col)[0]=org_img->at<cv::Vec3b>(row,col)[0];
                gaussian_image->at<cv::Vec3b>(row,col)[1]=org_img->at<cv::Vec3b>(row,col)[1];
                gaussian_image->at<cv::Vec3b>(row,col)[2]=org_img->at<cv::Vec3b>(row,col)[2];
            }
        }
    }
}
double getKernal(int size,float sigma,int x,int y,double z)
{
    double pow_val=-(x*x+y*y);
    double div_val=2*sigma*sigma;
    double all=double(pow_val/div_val);
    return z*exp(all);
}