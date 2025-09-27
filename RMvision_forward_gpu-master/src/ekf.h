#ifndef __EKF_H__
#define __EKF_H__

#include <Eigen/Dense>
#include <ceres/jet.h>
#include <opencv2/core/eigen.hpp>

// state-space equations:
//      x_{k+1} = Fx_k + w 
//      y_k = Hx_k + v  

template <int dimX, int dimY>
class EKF
{
public:
//协方差描述了不同特征之间的相关情况，通过计算协方差，
//可以判断一组数据的不同特征之间是否存在关联关系，正负表示两个特征是否为正相关或负相关
//协方差为0,则样本不相关

//dimx:状态变量维度，状态变量个数
//dimy:观测变量维度，测量的变量个数
    using MatXX = Eigen::Matrix<double, dimX, dimX>;// 状态协方差矩阵
    using MatXY = Eigen::Matrix<double, dimX, dimY>;
    using MatYX = Eigen::Matrix<double, dimY, dimX>;
    using MatYY = Eigen::Matrix<double, dimY, dimY>;
    using VecX = Eigen::Matrix<double, dimX, 1>;// 状态向量
    using VecY = Eigen::Matrix<double, dimY, 1>;

    EKF() : estimate_X(VecX::Zero()),
            P(MatXX::Identity()),
            Q(MatXX::Identity()),
            R(MatYY::Identity()) {}

    EKF(const MatXX &Q0, const MatYY &R0) : estimate_X(VecX::Zero()),
                                            P(MatXX::Identity()),
                                            Q(Q0),
                                            R(R0) {}

    void restart()
    {
        estimate_X = VecX::Zero();
        P = MatXX::Identity();//identity()是创建单位矩阵，zero()是创建零矩阵
    }

    VecX estimate_X;//​​当前状态估计值​​
    VecX predict_X;//预测状态估计值
    VecY predict_Y;//预测观测值
    MatXX jacobi_F;//状态转移雅可比矩阵​​
    MatYX jacobi_H;//观测模型的雅可比矩阵​​
    MatXX P;//状态估计协方差矩阵
    MatXX Q;//过程噪声协方差
    MatYY R;//观测噪音协方差矩阵
    MatXY K;//卡尔曼增益矩阵

    template <class Func>
    VecX predict(Func &&func)
    {
        ceres::Jet<double, dimX> estimate_jet_X[dimX];// 用于自动微分的Jet类型数组
        /*每个jet对象包含两部分: .a 函数值(实际数值)；.v 导数向量(梯度信息)*/
        for (int i = 0; i < dimX; i++)
        {
            estimate_jet_X[i].a = estimate_X[i];
            estimate_jet_X[i].v[i] = 1;
        }

        ceres::Jet<double, dimX> predict_jet_X[dimX];

        func(estimate_jet_X, predict_jet_X);//// 调用用户定义的非线性函数

        for (int i = 0; i < dimX; i++)
        {
            predict_X[i] = predict_jet_X[i].a;//// 提取预测状态值
            jacobi_F.block(i, 0, 1, dimX) = predict_jet_X[i].v.transpose();
        }

        P = jacobi_F * P * jacobi_F.transpose() + Q;//预测状态协方差矩阵的表达式

        return predict_X;
    }

    //通过观测数据修正状态估计，并更新状态协方差矩阵
    template <class Func>
    VecX update(Func &&func, const VecY &Y)
    {
        ceres::Jet<double, dimX> predict_jet_X[dimX];

        for (int i = 0; i < dimX; i++)
        {
            predict_jet_X[i].a = predict_X[i];
            predict_jet_X[i].v[i] = 1;
        }

        ceres::Jet<double, dimX> predict_jet_Y[dimY];

        func(predict_jet_X, predict_jet_Y);

        for (int i = 0; i < dimY; i++)
        {
            predict_Y[i] = predict_jet_Y[i].a;
            jacobi_H.block(i, 0, 1, dimX) = predict_jet_Y[i].v.transpose();
        }

        K = P * jacobi_H.transpose() * (jacobi_H * P * jacobi_H.transpose() + R).inverse();//计算卡尔曼增益
        estimate_X = predict_X + K * (Y - predict_Y);//更新状态估计
        P = (MatXX::Identity() - K * jacobi_H) * P;//更新状态协方差矩阵

        return estimate_X;
    }
};

#endif