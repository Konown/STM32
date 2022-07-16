#include "T_D_Filter.h"
#include <math.h>

T_D_Filter_st T_D_Filter_Data=
        {
            .x1=0,
            .x2=0,
        };

/**
 * @brief   TD滤波器：快速跟踪微分器
 * @param   v:输入信号
 * @param   h:步长
 * @param   r:速度因子 快慢因子 r 越大, 跟踪速度越快, 但噪声放大也越厉害
 * @param   h:滤波因子 滤波因子越大，滤波效果越好, 但跟踪信号的相位滞后也越大
 * @return
 *
 */
void T_D_Filter(double v,double h,double r,double h0)
{
    double u;

    u=fhan( T_D_Filter_Data.x1-v,T_D_Filter_Data.x2,r,h0 );
    T_D_Filter_Data.x1=T_D_Filter_Data.x1+h*T_D_Filter_Data.x2;
    T_D_Filter_Data.x2=T_D_Filter_Data.x2+h*u;
}

double fhan(double x1,double x2,double r,double h)
{
    double d=0,a0=0,y=0,a1=0,a2=0,sy=0,a=0,sa=0,result=0;

    d=r*h*h;
    a0=h*x2;
    y=x1+a0;
    a1=pow(d*(d+8*fabs(y)),0.5);
    a2=a0+sign(y)*(a1-d)/2;
    sy=fsg(y,-d,d);
    a=(a0+y-a2)*sy+a2;
    sa=fsg(a,-d,d);
    result=-r*(a/d-sign(a))*sa-r*sign(a);

    return result;
}

double sign(double err)
{
    if(err>0)
    {
        return 1;
    }
    else if(err<0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

double fsg(double x,double a,double b)
{
    return ( sign(x-a) - sign(x-b) )/ 2;
}

