#include <Math.h>



float round (double value)
{
   return  ((int)floor(value*100 + 0.5))/100.0;
}



float roundA(double value)
{
   return  (int)floor(value + 0.5);
}

int getP(double d)
{
    int i =0;

	while (pow(d,2) < 10)
	{
        d*= 10;
        i++;
    }
	return i;
}
