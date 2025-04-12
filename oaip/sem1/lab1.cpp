#include <iostream>
#include <math.h>

int main() 
{
    double x,y,z,a,b,c,h;
    std::cout <<"Vvedite x:";
      std::  cin >>x;
       std:: cout <<"Vvedite y:";
        std:: cin >>y;
        std:: cout <<"Vvedite z:";
        std:: cin >>z;
        a = log(pow(y, - sqrt(fabs (x))));
        b = x - y / 2;
        c = pow(sin(atan(z)), 2);
        h = a * b + c;
        std::cout << "Result h="<<h << std::endl;

       
   
    return 0;
    
}

