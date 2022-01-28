#include "stdio.h"
#include "math.h"
#include "stdlib.h"

int main(){

long double arr[6][2],x,y,z,x1,y1,z1,bir,iki;
long double sx,sy,sz,sx1,sy1,sz1;
long int red;
char r=0,b;
long double e1,e2,e3,e4,e5,e6,e7,e8,e9;

printf("Triangle #1:\n");

if((red = scanf(" %c [ %Lf ; %Lf ] , [ %Lf ; %Lf ] , [ %Lf ; %Lf ] }%c",&b,&arr[0][0],&arr[0][1],&arr[1][0],&arr[1][1],&arr[2][0],&arr[2][1],&r))==8)
{

	if (b!='{')
	{
		printf("Invalid input.\n" );
		return 0;
	}

	sx=(double)(arr[1][1]-arr[0][1])/(double)(arr[1][0]-arr[0][0]);

	sy=(double)(arr[1][1]-arr[2][1])/(double)(arr[1][0]-arr[2][0]);

	sz=(double)(arr[0][1]-arr[2][1])/(double)(arr[0][0]-arr[2][0]);

	x=sqrt((arr[0][0]-arr[1][0])*(arr[0][0]-arr[1][0])+(arr[0][1]-arr[1][1])*(arr[0][1]-arr[1][1]));

	y=sqrt((arr[1][0]-arr[2][0])*(arr[1][0]-arr[2][0])+(arr[1][1]-arr[2][1])*(arr[1][1]-arr[2][1]));	

	z=sqrt((arr[2][0]-arr[0][0])*(arr[2][0]-arr[0][0])+(arr[2][1]-arr[0][1])*(arr[2][1]-arr[0][1]));
		
	sx=floor(10000000*sx)/10000000;
	sy=floor(10000000*sy)/10000000;
	sz=floor(10000000*sz)/10000000;

	bir=(double)(x+y+z);

	if (fabs(sx-sy)<1e-12 && fabs(sy-sz)<1e-12)
	{
		printf("Invalid triangle.\n");
		return 0;
	}
}

else if((red = scanf(" %Lf , %Lf , %Lf }%c",&x,&y,&z,&r))==4)
{
	if(b!='{'){
      printf("Invalid input.\n");
      return 0;
    }
  bir=(double)(x+y+z);
}
else{
	printf("Invalid input.\n" );
    return 0;
}

  if(x+y-z<=1e-12*z || x+z-y<=1e-12*y || y+z-x<=1e-12*x)
  {
    printf("Invalid triangle.\n");
    return 0;
  }


printf("Triangle #2:\n");

 if((red = scanf(" %c [ %Lf ; %Lf ] , [ %Lf ; %Lf ] , [ %Lf ; %Lf ] }%c",&b,&arr[3][0],&arr[3][1],&arr[4][0],&arr[4][1],&arr[5][0],&arr[5][1],&r))==8)
{

	if (b!='{')
	{
		printf("Invalid input.\n" );
			return 0;
	}

	sx1=(double)(arr[4][1]-arr[3][1])/(double)(arr[4][0]-arr[3][0]);

	sy1=(double)(arr[5][1]-arr[4][1])/(double)(arr[5][0]-arr[4][0]);

	sz1=(double)(arr[3][1]-arr[5][1])/(double)(arr[3][0]-arr[5][0]);

	x1=sqrt((arr[3][0]-arr[4][0])*(arr[3][0]-arr[4][0])+(arr[3][1]-arr[4][1])*(arr[3][1]-arr[4][1]));

	y1=sqrt((arr[4][0]-arr[5][0])*(arr[4][0]-arr[5][0])+(arr[4][1]-arr[5][1])*(arr[4][1]-arr[5][1]));

	z1=sqrt((arr[5][0]-arr[3][0])*(arr[5][0]-arr[3][0])+(arr[5][1]-arr[3][1])*(arr[5][1]-arr[3][1]));

	sx1=floor(10000*sx1)/10000;

	sy1=floor(10000*sy1)/10000;

	sz1=floor(10000*sz1)/10000;

	iki=(double)(x1+y1+z1);

	if (sx1==sy1 && sy1==sz1)
	{
		printf("Invalid triangle.\n");
		return 0;
	}		
}
else if((red = scanf(" %Lf , %Lf , %Lf }%c",&x1,&y1,&z1,&r))==4)
{

	if(b!='{'){
		printf("Invalid input.\n");
		return 0;
	}
	iki=(double)(x1+y1+z1);
}
else{
	printf("Invalid input.\n" );
    return 0;
}

if(x1+y1-z1<=1e-12*z1 || x1+z1-y1<=1e-12*y1 || y1+z1-x1<=1e-12*x1)
{
	printf("Invalid triangle.\n");
	return 0;
}

e1=(x<x1) ? x : x1;
e2=(x<y1) ? x : y1;
e3=(x<z1) ? x : z1;
e4=(y<x1) ? y : x1;
e5=(y<y1) ? y : y1;
e6=(y<z1) ? y : z1;
e7=(z<x1) ? z : x1;
e8=(z<y1) ? z : y1;
e9=(z<z1) ? z : z1;

if (fabs(x-x1)<1e-12*e1 && fabs(y-y1)<1e-12*e5 && fabs(z-z1)<1e-12*e9)
{
	printf("The triangles are identical.\n");
	return 0;
}
			
if (fabs(x-x1)<1e-12*e1 && fabs(y-z1)<1e-12*e6 && fabs(z-x1)<1e-12*e7)
{
				printf("The triangles are identical.\n");
	return 0;
}

if (fabs(x-z1)<1e-12*e3 && fabs(y-y1)<1e-12*e5 && fabs(z-x1)<1e-12*e7)
{
	printf("The triangles are identical.\n");
	return 0;
}

if (fabs(x-y1)<1e-12*e2 && fabs(y-x1)<1e-12*e4 && fabs(z-z1)<1e-12*e9)
{
	printf("The triangles are identical.\n");
	return 0;
}

if (fabs(x-x1)<1e-12*e1 && fabs(y-z1)<1e-12*e6 && fabs(z-y1)<1e-12*e8)
{
	printf("The triangles are identical.\n");
	return 0;
}

if (fabs(x-z1)<1e-12*e3 && fabs(y-x1)<1e-12*e4 && fabs(z-y1)<1e-12*e8)
	{
	printf("The triangles are identical.\n");
	return 0;
}

if (bir==iki)
{
	printf("The triangles are not identical, however, they have the same circumference.\n");
	return 0;
}
else if (bir>iki)
{
	printf("Triangle #1 has a longer circumference.\n");
	return 0;
}
else if (iki>bir)
{
	printf("Triangle #2 has a longer circumference.\n");
	return 0;
}
  return 0;
}
