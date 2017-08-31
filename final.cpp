#include<iostream>
#include "CImg.h"
using namespace std;
using namespace cimg_library;

class img
{
    int b1=0,b2=0,b3=0,b4=0;
    int counter_x=0,counter_y=0,counter=0;
protected:
    CImg<float> image;
    char filename[100];
public:
    img()
    {
        cout<<"Enter file name\n";
        cin>>filename;
        image.load_bmp(filename);
        //image.crop(0,0,1,0,500,500,1,0);
        //image = new CImg<unsigned char>(filename);

    }
    img(char x[])
    {
        image.load_bmp(x);
        //image = new CImg<>(filename);
        //CImg<float> img2(x);
        //image = img2;
    }

    void fillBlack()
    {
            for(int m=0;m<image.height();m++)
        {

        for(int n=0;n<image.width();n++)
        {
            if(image(n,m,1)==255)
            {
                for(int j=0;n+j<image.width();j++)
                {
                    if(image(n+j,m,0)<150||image(n+j,m,1)<150||image(n+j,m,2)<150)
                        {b1=1;break;}
                }
                for(int k=0;n-k>0;k++)
                {
                    if(image(n-k,m,0)<150||image(n-k,m,1)<150||image(n-k,m,2)<150)
                        {b2=1;break;}
                }
                for(int l=0;m+l<image.height();l++)
                {
                    if(image(n,m+l,0)<150||image(n,m+l,1)<150||image(n,m+l,2)<150)
                        {b3=1;break;}
                }
                for(int i=0;m-i>0;i++)
                {
                    if(image(n,m-i,0)<150||image(n,m-i,1)<150||image(n,m-i,2)<150)
                        {b4=1;break;}
                }
                if(b1==1&&b2==1&&b3==1&&b4==1)
                {
                    image(n,m,1)=0;
                    image(n,m,2)=0;
                    image(n,m,0)=0;
                    b1=0;b2=0;b3=0;b4=0;
                }
            }

            }

        }

    }
    void findCentroid()
    {
        for(int i=0;i<image.width();i++)
    {
        for(int j=0;j<image.height();j++)
        {
            if(image(i,j,1)==0)
            {
                counter_x+=i;
                counter_y+=j;
                counter++;
            }
        }
    }
    }
    int returnCentroidX()
    {
        return counter_x;
    }
    int returnCentroidY()
    {
        return counter_y;
    }
    int returnCounter()
    {
        return counter;
    }
    char* returnFileName()
    {
        return filename;
    }
};
class draw: public img
{
    unsigned char red[3] = {255,0,0};
public:
    draw(char x[]): img(x)
    {

    }
    void drawCentroid(img i)
    {
        int counter_x=i.returnCentroidX();
        int counter_y=i.returnCentroidY();
        int counter=i.returnCounter();
        image.draw_circle(counter_x/counter,counter_y/counter,3,red);
        CImgDisplay d(image);
        while(!d.is_closed())cimg::wait(20);
    }
};
int main()
{
    cimg::exception_mode(0);
    int input=1;
    cout<<"Dhairya Shah "<<endl;
    cout<<"***Centroid finder***\nNotes:\n 1)All images have to be closed and black-white\n 2)All images must be in bmp format."<<endl;
    A:;
    try{
    while(input)
    {
        cout<<"***************************************************************************"<<endl;
        cout<<"Welcome to centroid finder\n\tEnter 1 to find centroid\n\tEnter 0 to escape"<<endl;
        cin>>input;
           cout<<"***************************************************************************"<<endl;
        if(input){
        img i;
        cout<<"Calculating centroid...."<<endl;
        i.fillBlack();
        i.findCentroid();
        draw d(i.returnFileName());
        d.drawCentroid(i);}
    }}
    catch(CImgIOException &e)
    {
        cout<<"Error loading file, the file does not exist or is incorrect format"<<endl;
        goto A;
    }

}
