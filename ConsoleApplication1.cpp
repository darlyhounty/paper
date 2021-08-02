// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<math.h>
#include<iostream>
#include<iomanip>
#include<cmath>

using namespace std;
double x_end =1.;
int n = 1000;// 100 *
double h = x_end / n;// 0.0002

double *Y = new double [n+1];
double *X = new double [n+1];


double F(double x,double y,double Lambda) {
	return Lambda*y;
}
double real_sol(double x,double Lambda) {
	return exp(Lambda*x);
}
double F1(double x) {
	return cos(x);
}
double F2(double x) {
	return -sin(x);
}
double F_new(double x,double y, double Lambda) {
	return Lambda*(y - F1(x)) + F2(x);
}
double real_sol_new(double x, double Lambda) {
	return F1(x);
}
//y'=Lambda y    y(x)=e^-Lambda*x

double F_5_6_1(double t,double y1,double y2) {
	return -2 * y1 + y2 + 2 * sin(t);
}
double F_5_6_2(double t, double y1, double y2) {
	return 998 * y1 - 999 * y2 + 999 * (cos(t)-sin(t));
}
double F1_5_6_real(double t) {
	return -exp(-t) / 999 + exp(-1000 * t) / 999 + sin(t);
}
double F2_5_6_real(double t) {
	return -exp(-t) / 999 - 998* exp(-1000 * t) / 999 + cos(t);
}

void explicit_Adams_1(double Lambda) {
	double j = 0;
	Y[0] = 1;
	for (int i = 0; i < n; ++i) {
		Y[i + 1] = Y[i] +h*F(j,Y[i],Lambda);
		cout << Y[i] << "real:" << real_sol(j, Lambda) << "error:" << Y[i] - real_sol(j, Lambda) << endl;
		j += h;
	}
}
void explicit_Adams_2(double Lambda) {
	double j = 0;
	Y[0] = 1;
	Y[1] = real_sol(h,Lambda);
	for (int i = 0; i < n; ++i) {
		Y[i + 2] = Y[i+1]+h*(3*F(j+h,Y[i+1],Lambda)-F(j,Y[i],Lambda))/2;
		cout << Y[i] << "real:" << real_sol(j, Lambda) << "error:" << Y[i] - real_sol(j, Lambda) << endl;
		j += h;
	}
}
void explicit_Adams_3(double Lambda) {
	double j = 0;
	Y[0] = 1;
	Y[1] = real_sol(h, Lambda);
	Y[2] = real_sol(2*h, Lambda);
	for (int i = 0; i < n; ++i) {
		Y[i + 3] = Y[i + 2] + h*(23 * F(j + 2*h, Y[i + 2], Lambda) -16* F(j+h, Y[i+1], Lambda)+5*F(j,Y[i],Lambda)) / 12;
		//cout << Y[i] << "real:" << real_sol(j, Lambda) << "error:" << Y[i] - real_sol(j, Lambda) << endl;
		j += h;
	}
	//cout << Y[n-1] << "real:" << real_sol(j, Lambda) << "error:" << Y[i] - real_sol(j, Lambda) << endl;
}

void explicit_Adams_3_n(double Lambda, int n, double& error) {
	double h = x_end / (double)n;
	double x = 0;
	double Y0 = 1;
	double Y1 = real_sol(h, Lambda);
	double Y2 = real_sol(2 * h, Lambda);
	double Y3;
	for (int i = 0; i < n-2; ++i) {
		Y3 = Y2 + h*(23 * F(x + 2 * h, Y2, Lambda) - 16 * F(x + h, Y1, Lambda) + 5 * F(x, Y0, Lambda)) / 12.;
		Y0 = Y1;
		Y1 = Y2;
		Y2 = Y3;
		//cout << Y[i] << "real:" << real_sol(j, Lambda) << "error:" << Y[i] - real_sol(j, Lambda) << endl;
		x += h;
	}
	error = abs(real_sol(x_end, Lambda) - Y3);
	//cout << Y[n-1] << "real:" << real_sol(j, Lambda) << "error:" << Y[i] - real_sol(j, Lambda) << endl;
}


void explicit_Adams_4(double Lambda) {
	double j = 0;
	Y[0] = 1;
	Y[1] = real_sol(h, Lambda);
	Y[2] = real_sol(2 * h, Lambda);
	Y[3] = real_sol(3 * h, Lambda);
	for (int i = 0; i < n; ++i) {
		Y[i + 4] = Y[i +3] + h*(55 * F(j +3* h, Y[i + 3], Lambda) - F(j+2*h, Y[i+2], Lambda)+37*F(j+h,Y[i+1],Lambda)-9*F(j,Y[i],Lambda)) / 24;
		cout << Y[i] << "real:" << real_sol(j, Lambda) << "error:" << Y[i] - real_sol(j, Lambda) << endl;
		j += h;
	}
}
void Implicit_Adams_1(double Lambda) {
	double j = 0;
	Y[0] = 1;
	for (int i = 0; i < n; ++i) {
		Y[i + 1] = (Y[i]+h*F(j,Y[i],Lambda)/2) / (1 - h*Lambda/ 2);
		cout << Y[i] <<"real:"<< real_sol(j, Lambda) <<"error:"<< Y[i] - real_sol(j,Lambda) << endl;
		j+=h;
	}
}
void Implicit_Adams_2(double Lambda) {
	double j = 0;
	Y[0] = 1;
	Y[1]= real_sol(j+h,Lambda);
	for (int i = 0; i < n; ++i) {
		Y[i + 2] = (Y[i+1]-h*(8*F(j+h,Y[i+1],Lambda)-F(j,Y[i],Lambda))/12)/ (12 - 5*h*Lambda);
		cout << Y[i] << "real:" << real_sol(j, Lambda) << "error:" << Y[i] - real_sol(j, Lambda) << endl;
		j += h;
	}
}
void Implicit_Adams_3(double Lambda) {
	double j = 0;
	Y[0] = 1;
	Y[1] = real_sol(j + h, Lambda);
	Y[2] = real_sol(j + 2*h, Lambda);
	for (int i = 0; i < n; ++i) {
		Y[i + 3] = (Y[i+2]+h*(19*F(j+2*h,Y[i+2],Lambda)-5*F(j+h,Y[i+1],Lambda)+F(j,Y[i],Lambda))/24) / (24 - 9 * h*Lambda);
		cout << Y[i] << "real:" << real_sol(j, Lambda) << "error:" << Y[i] - real_sol(j, Lambda) << endl;
		j += h;
	}
}
void Implicit_Adams_4(double Lambda) {
	double j = 0;
	Y[0] = 1;
	Y[1] = real_sol(j + h, Lambda);
	Y[2] = real_sol(j + 2 * h, Lambda);
	Y[3] = real_sol(j + 3 * h, Lambda);
	for (int i = 0; i < n; ++i) {
		Y[i + 4] = (Y[i+3]+h*(646*F(j + 3 * h,Y[i+3], Lambda)-264*F(j + 2*h, Y[i +2], Lambda)+106*F(j +  h, Y[i + 1], Lambda)-19*F(j, Y[i], Lambda))/720) / (720 - 251 * h*Lambda);
		cout << Y[i] << "real:" << real_sol(j, Lambda) << "error:" << Y[i] - real_sol(j, Lambda) << endl;
		j += h;
	}
}
void Bdf_1(double Lambda) {
	double j = 0;
	Y[0] = 1;
	for (int i = 0; i < n; ++i) {
		Y[i + 1] = Y[i] / (1 - Lambda*h);
		cout << Y[i] << "real:" << real_sol(j, Lambda) << "error:" << Y[i] - real_sol(j, Lambda) << endl;
		j += h;
	}
}
void Bdf_2(double Lambda) {
	double j = 0;
	Y[0] = 1;
	Y[1] = real_sol(j + h, Lambda);
	for (int i = 0; i < n; ++i) {
		Y[i + 2] = (4*Y[i + 1] - Y[i]) / (3 - 2 * h*Lambda);
		cout << Y[i] << "real:" << real_sol(j, Lambda) << "error:" << Y[i] - real_sol(j, Lambda) << endl;
		j += h;
	}
}
void Bdf_3(double Lambda) {
	double j = 0;
	Y[0] = 1;
	Y[1] = real_sol(j + h, Lambda);
	Y[2] = real_sol(j + 2 * h, Lambda);
	for (int i = 0; i < n; ++i) {
		Y[i + 3] = (18 * Y[i + 2] - 9 * Y[i + 1] + 2 * Y[i]) / (11 - 6 * h*Lambda);
		cout << Y[i] << "real:" << real_sol(j, Lambda) << "error:" << Y[i] - real_sol(j, Lambda) << endl;
		j += h;
	}
}
void Bdf_4(double Lambda) {
	double j = 0;
	Y[0] = 1;
	Y[1] = real_sol(j + h, Lambda);
	Y[2] = real_sol(j + 2 * h, Lambda);
	Y[3] = real_sol(j + 3 * h, Lambda);
	for (int i = 0; i < n; ++i) {
		Y[i + 4] = (48 * Y[i + 3] - 36 * Y[i + 2] + 16 * Y[i+1]-3*Y[i]) / (25 - 12 * h*Lambda);
		cout << Y[i] << "real:" << real_sol(j, Lambda) << "error:" << Y[i] - real_sol(j, Lambda) << endl;
		j += h;
	}
}

void method_5_8(double Lambda,double a,double n,double& error) {
	double h = x_end / (double)n;
	double x = h;
	double y0 = 1;//f[0]
	double y1 = real_sol_new(h,Lambda);//f[1]
	double y2;
	double f0 = F_new(0, y0, Lambda);
	double f1 = F_new(h, y1, Lambda);
	double b0 = -(-4. + 5 * a) / 12.;
	double b1 = -2. * (a - 2) / 3.;
	double b2 = (4. + a) / 12.;
	//Y[1] = (1 + (h*belta / 2))*Y[0] / (1 - (h*belta / 2));

	for (int i = 0; i < n; ++i) {
		y2 =((1 - a)*y0 + a*y1+h*(b2*(F2(x)-Lambda*F1(x))+b1 *f1 + b0 *f0))/(1 - h*Lambda*b2);
	    //cout << "{" << x << "," << y2 << "},";
		//if (x > 100 && x <100.3) {
			//cout << x << endl;
			//cout << y2 << "real:" << real_sol_new(x, Lambda) << "error:" << y2 - real_sol_new(x, Lambda) << endl;
		//}
		//cout << y2 << "real:" << real_sol_new(x, Lambda) << "error:" << y2 - real_sol_new(x, Lambda) << endl;
		y0 = y1;
		y1 = y2;
		f0 = f1;
		f1 = F_new(x, y2, Lambda);
		x += h;
	}
	error = abs(real_sol_new(x_end, Lambda) - y2);
}
void method_4_3(double Lambda, double a, double b, double c, double belta0,double&error,int n) {
	double h = x_end / (double)n;
	double l = a*b + b*c + a*c;
	double m = a + b + c;
	double belta1 = -3 * belta0 + (m + 5 * l - 23 * a*b*c + 5) / 12;
	double belta2 =  3 * belta0 + (-8*m + 8 * l + 16 * a*b*c -16) / 12;
	double belta3 = - belta0 + (-5*m - l - 5 * a*b*c + 23) / 12;
	double j = 3*h;
	double y0 = 1;
	double y1 = real_sol_new(h, Lambda);
	double y2 = real_sol_new(2*h, Lambda);
	double y3 = real_sol_new(3* h, Lambda);
	double y4;
	double f0 = F_new(0, y0, Lambda);
	double f1 = F_new(h, y1, Lambda);
	double f2 = F_new(2*h, y2, Lambda);
	double f3 = F_new(3*h, y3, Lambda);
	for (int i = 0; i < n-2; ++i) {
	    y4 = (m + 1)*y3 - (m + l)*y2 + (l + a*b*c)*y1 -(a*b*c)*y0+h*(belta3*f3+ belta2*f2+ belta1*f1+ belta0*f0);
		j += h;
		//cout << "{" <<j << "," << y4 << "},";
		//cout << y4 << "__real:" << real_sol_new(j, Lambda) << "__error:" << y4 - real_sol_new(j, Lambda) << endl;// y4 - exp(Lambda*j) //exp(Lambda*j)
		y0 = y1;
		y1 = y2;
		y2 = y3;
		y3 = y4;
		f0 = f1;
		f1 = f2;
		f2 = f3;
		f3 = F_new(j + 2 * h, y4, Lambda);

	}
	error = abs(real_sol_new(j, Lambda)-y4);
}

void method_5_8_56(double a,double n,double&error) {
	double h = x_end / (double)n;
	double t0 =2*h;
	double y1_0 = 0;//f[0]
	double y2_0 = 0;
	double y1_1 = F1_5_6_real(h);//f[1]
	double y2_1 = F2_5_6_real(h);
	double y2_2, y1_2;
	double f0_1 = F_5_6_1(t0,y1_0,y2_0);
	double f0_2 = F_5_6_2(t0,y1_0,y2_0);
	double f1_1 = F_5_6_1(t0 + h, y1_1, y2_1);
	double f1_2 = F_5_6_2(t0 + h, y1_1, y2_1);
	double b0 = -(-4. + 5 * a) / 12.;
	double b1 = -2. * (a - 2) / 3.;
	double b2 = (4. + a) / 12.;
	//Y[1] = (1 + (h*belta / 2))*Y[0] / (1 - (h*belta / 2));
	for (int i = 0; i < n-1; ++i) {
	    y2_2 = ((1 - a)*y2_0 + a*y2_1 + h*(b1 *f1_2 + b0 *f0_2)+999*h*b2*(cos(t0)-sin(t0))+(998*b2*h*(h*b2*2*sin(t0)+ (1 - a)*y1_0 + a*y1_1 + h*(b1 *f1_1 + b0 *f0_1)))/(1+2*h*b2))/(1+999*h*b2-(998*h*h*b2*b2)/(1+2*h*b2));
		y1_2 = (h*b2*(y2_2+2*sin(t0))+((1 - a)*y1_0 + a*y1_1 + h*(b1 *f1_1 + b0 *f0_1)))/(1+2*h*b2);
		//cout << y1_2 << "]real:" << F1_5_6_real(t0) << "]error:" << y1_2 - F1_5_6_real(t0) << endl;
		//cout << y2_2 << "]real:" << F2_5_6_real(t0) << "]error:" << y2_2 - F2_5_6_real(t0) << endl;
		//cout << y2_2 << "real:" << F2_5_6_real(t0) << "error:" << y2_2 - F2_5_6_real(t0) << endl;
		//cout << "{" << t0 << "," << y1_2 << "},";
		t0 += h;
		//make_step(t0, y1_0, y1_1, y1_2, y2_0, y2_1, y2_2, f0_1, f0_2, f1_1, f1_2);
		y1_0 = y1_1;
		y1_1 = y1_2;//
		f0_1 = f1_1;
		y2_0 = y2_1;
		y2_1 = y2_2;//
		f0_2 = f1_2;
		f1_1 = F_5_6_1(t0, y1_2,y2_1);
		f1_2 = F_5_6_2(t0, y1_2,y2_1);
	}
	error = abs(F2_5_6_real(x_end)-y2_2);
}
void method_4_3_56(double a, double b, double c, double belta0,int n,double&error) {
	double h = x_end / (double)n;
	double l = a*b + b*c + a*c;
	double m = a + b + c;
	double belta1 = -3 * belta0 + (m + 5 * l - 23 * a*b*c + 5) / 12;
	double belta2 = 3 * belta0 + (-8 * m + 8 * l + 16 * a*b*c - 16) / 12;
	double belta3 = -belta0 + (-5 * m - l - 5 * a*b*c + 23) / 12;
	double t = 4*h;
	double y1_0 = 0;//f[0]
	double y2_0 = 0;
	double y1_1 = F1_5_6_real(h);//f[1]
	double y2_1 = F2_5_6_real(h);
	double y1_2 = F1_5_6_real(2 * h);
	double y2_2 = F2_5_6_real(2 * h);
	double y1_3 = F1_5_6_real(3 * h);
	double y2_3 = F2_5_6_real(3 * h);
	double y1_4, y2_4;
	double f0_1 = F_5_6_1(0, y1_0, y2_0);
	double f0_2 = F_5_6_2(0, y1_0, y2_0);
	double f1_1 = F_5_6_1(h, y1_1, y2_1);
	double f1_2 = F_5_6_2(h, y1_1, y2_1);
	double f2_1 = F_5_6_1(2*h, y1_2, y1_2);
	double f2_2 = F_5_6_2(2*h, y1_2, y1_2);
	double f3_1 = F_5_6_1(3*h, y1_3, y2_3);
	double f3_2 = F_5_6_2(3*h, y1_3, y2_3);
	for (int i = 0; i < n-2; ++i) {
		y1_4 = (m + 1)*y1_3 - (m + l)*y1_2 + (l + a*b*c)*y1_1 - a*b*c*y1_0 + h*(belta3*f3_1+belta2*f2_1+belta1*f1_1+belta0*f0_1);
	    y2_4 = (m + 1)*y2_3 - (m + l)*y2_2 + (l + a*b*c)*y2_1 - a*b*c*y2_0 + h*(belta3*f3_2 + belta2*f2_2 + belta1*f1_2 + belta0*f0_2);
		//cout << y1_4 << "__real:" << F1_5_6_real(t) << "__error(f1):" << y1_4 - F1_5_6_real(t) << endl;// y4 - exp(Lambda*j) //exp(Lambda*j)
		//cout << y2_4 << "__real:" << F2_5_6_real(t) << "__error(f2):" << y2_4 - F2_5_6_real(t) << endl;//
		t += h;
		y1_0 = y1_1;
		y1_1 = y1_2;//
		y1_2 = y1_3;
		y1_3 = y1_4;
		y2_0 = y2_1;
		y2_1 = y2_2;//
		y2_2 = y2_3;
		y2_3 = y2_4;
		f0_1 = f1_1;
		f1_1 = f2_1;
		f2_1 = f3_1;
		f3_1 = F_5_6_1(t,y1_4,y2_4);
		f0_2 = f1_2;
		f1_2 = f2_2;
		f2_2 = f3_2;
		f3_2 = F_5_6_2(t, y1_4, y2_4);

	}
	error = abs(F1_5_6_real(x_end)- y1_4);
	//error = abs(F2_5_6_real(x_end)- y2_4);
}
void explicit_Adams_3_56(double&error,int n) {
	double h = x_end / (double)n;
	double j = 0;
	double Y0_1 = 0;
	double Y0_2 = 0;
	double Y1_1 = F1_5_6_real(h);
	double Y1_2 = F2_5_6_real(h);
	double Y2_1 = F1_5_6_real(2*h);
	double Y2_2 = F2_5_6_real(2*h);
	double Y3_1, Y3_2;
	for (int i = 0; i < n; ++i) {
		Y3_1 = Y2_1 + h*(23 * F_5_6_1(j + 2 * h, Y2_1, Y2_2) - 16 * F_5_6_1(j + h, Y1_1, Y1_2) + 5 * F_5_6_1(j, Y0_1, Y0_2)) / 12;
	    Y3_2 = Y2_2 + h*(23 * F_5_6_2(j + 2 * h, Y2_1, Y2_2) - 16 * F_5_6_2(j + h, Y1_1, Y1_2) + 5 * F_5_6_2(j, Y0_1, Y0_2)) / 12;
		//cout << Y3_1 << "F1 real:" << F1_5_6_real(j+3*h) << "F1 error:" << Y3_1 - F1_5_6_real(j + 3 * h) << endl;
		//cout << Y3_2 << "F2 real:" << F2_5_6_real(j + 3 * h) << "F2 error:" << Y3_2 - F2_5_6_real(j + 3 * h) << endl;
		//cout << "{" << j << "," << Y3_1 << "},";
		j += h;
		Y0_1 = Y1_1;
		Y0_2 = Y1_2;
		Y1_1 = Y2_1;
		Y1_2 = Y2_2;
		Y2_1 = Y3_1;
		Y2_2 = Y3_2;
	}
	error = abs(F1_5_6_real(x_end) - Y3_1);
}
void explicit_Adams_3_51(double Lambda) {
	double j = 0;
	double Y0 = 1;
	double Y1 = real_sol_new(h, Lambda);
	double Y2 = real_sol_new(2 * h, Lambda);
	for (int i = 0; i < n; ++i) {
		auto Y3 = Y2 + h*(23 * F_new(j + 2 * h,Y2, Lambda) - 16 * F_new(j + h, Y1, Lambda) + 5 * F_new(j, Y0, Lambda)) / 12;
		//cout << Y3 << "real:" << real_sol_new(j, Lambda) << "error:" << Y3 - real_sol_new(j, Lambda) << endl;
	//cout << "{" << j << "," << Y3 << "},";
		j += h;
		Y0 = Y1;
		Y1 = Y2;
		Y2 = Y3;
	}
}
int main()
{
	cout << setprecision(20);
	/*for (int i = 0; i <100; i++)
		X[i + 1] = X[i] + h;*/
	//explicit_Adams_1(-100);
	//explicit_Adams_2(-10);
	//explicit_Adams_3(-10);
	//explicit_Adams_4(-10);
	//Implicit_Adams_1(-100);
	//Implicit_Adams_2(-100);
	//Implicit_Adams_3(-10);
	//Implicit_Adams_4(-100);
	//Bdf_1(-100);
	//Bdf_2(-100);
	//Bdf_3(-100);
	//Bdf_4(-100);
   // method_5_8(-1000, 1.8);
	//method_4_3(-1000,0.9,0.9,0.9,-0.2);
	//method_4_3_56(0.99,0.99,0.99,0.000147);//对了
	//method_5_8_56(1.99);
	//cout << F1_5_6_real(0) << endl;
	//cout << F2_5_6_real(0) << endl;
	//method_5_8_1(1.99);
	/*for (int i = 1; i < 100; ++i) {
		double x = 0.001;
		double h = 0.001;
		cout << F2_5_6_real(x+i*h) << endl;
	}*/
	//explicit_Adams_3_56();
	//explicit_Adams_3_51(-1000);

	for (double i = 3; i < 13; i += 0.05)
	{
		double error;
		method_4_3_56(0.25, 0.25, 0.25,0.21,(int)pow(2,i),error);
		//method_5_8_56(1.8, (int)pow(2, i), error);
		//method_4_3(-100,0.99,0.99,0.99,0,error, (int)pow(2, i));
		//explicit_Adams_3_n(-100, (int) pow(2, i), error);
		//method_5_8(-100,1.99,(int)pow(2,i),error);
		//explicit_Adams_3_56(error,(int)pow(2,i));
		cout << "{-Log[10," << x_end/pow(2, i) << "], Log[10," << abs(error) << "]}, "<<endl;
		//cout << x_end / pow(2, i) << "-->" << error <<endl;
	}
	/*double error;
	method_5_8(-100, 1.8, 4, error);*/
	system("pause");
    return 0;
}

