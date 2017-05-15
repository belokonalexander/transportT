#include <Math.h>
#include <unordered_map>
#include <vcl.h>

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

int getHash(std::vector<String> data){

	String str = "";

	for(int i =0; i<data.size(); i++){
		str+=data[i];
	}

	int s = 7;
	int n = str.Length();
	double h = 31;
	for(int i =0; i <= str.Length(); i++){
		if(str.SubString0(i,1)=="")
            continue;
		s = StrToInt(str.SubString0(i,1)) + s * h;
		}


	return s;
}
