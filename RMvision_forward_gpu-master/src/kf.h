#ifndef __OPENRM_KALMAN_FILTER_KF_H__
#define __OPENRM_KALMAN_FILTER_KF_H__

#include <Eigen/Dense>
#include <opencv2/core/eigen.hpp>

template<int dimX, int dimY>
class KF {
public:
    using MatXX = Eigen::Matrix<double, dimX, dimX>;
    using MatXY = Eigen::Matrix<double, dimX, dimY>;
    using MatYX = Eigen::Matrix<double, dimY, dimX>;
    using MatYY = Eigen::Matrix<double, dimY, dimY>;
    using VecX = Eigen::Matrix<double, dimX, 1>;
    using VecY = Eigen::Matrix<double, dimY, 1>;
    
    KF():
        estimate_X(VecX::Zero()),
        P(MatXX::Identity()),
        Q(MatXX::Identity()),
        R(MatYY::Identity()) {}

    KF(const MatXX& Q0, const MatYY& R0):
        estimate_X(VecX::Zero()),
        P(MatXX::Identity()),
        Q(Q0),
        R(R0) {}

    void restart() {
        estimate_X = VecX::Zero();
        P = MatXX::Identity();
    }

    VecX estimate_X;//当前状态最优估计值
    VecX predict_X;//预测状态估计值
    MatXX A;//状态转移矩阵（线性系统动力学模型）
    MatYX H;//观测矩阵（状态到观测的线性映射）
    MatXX P;//状态估计协方差矩阵（不确定性量化）
    MatXX Q;//过程噪声协方差（模型误差）
    MatYY R;//观测噪音协方差矩阵（测量误差）
    MatXY K;//卡尔曼增益矩阵（决定预测与观测的权重）

    template<class Func>
    VecX predict(Func&& func) {
        
        func(A);// // 用户提供状态转移矩阵A
        predict_X = A * estimate_X;
        P = A * P * A.transpose() + Q;
        
        return predict_X;
    }

    template<class Func>
    VecX update(Func&& func, const VecY& Y) {
    
        func(H);// 用户提供观测矩阵H
        K = P * H.transpose() * (H * P * H.transpose() + R).inverse();
        estimate_X = predict_X + K * (Y - H * predict_X);
        P = (MatXX::Identity() - K * H) * P;
        
        return estimate_X;
    }
};

#endif
