#ifndef INC_01T_D_FILTER_T_D_FILTER_H
#define INC_01T_D_FILTER_T_D_FILTER_H

typedef struct
{
    double x1;
    double x2;
}T_D_Filter_st;

void T_D_Filter(double v,double h,double r,double h0);        //TD滤波器（输入信号，步长，速度因子，滤波因子）
double fhan(double x1,double x2,double r,double h);           //最速控制综合函数（输入信号，一阶信号，速度因子，滤波因子）
double sign(double err);                                      //符号函数
double fsg(double x,double a,double b);

extern T_D_Filter_st T_D_Filter_Data;

#endif //INC_01T_D_FILTER_T_D_FILTER_H
