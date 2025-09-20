/*三维空间中的自旋转目标追踪*/
/*状态向量设计:x,y,z质心位置
             vx,vy,vz,质心速度
             wx,wy,wz质心角速度,常简化为一维旋转，所以就只用一个w即可
             radius旋转半径
角速度和半径要估计，其他都要初始化才行*/
             
//总状态一共10个，但是只能测量位置，也就是x,y,z;
/*测量点 = 质心位置 + 旋转偏移量*/
#include <iostream>
#include <Eigen/Dense>
#include <cmath>
#include <random>
using namespace Eigen;

template<int dim_a , int dim_v>//all view
class EKF
{
private:
    Matrix<double,dim_a,1> X;//状态矩阵
    Matrix<double,dim_a,dim_a> P;//状态协方差矩阵
    Matrix<double,dim_v,dim_a> H;//观测矩阵
    Matrix<double,dim_a,dim_a> F;//状态转移矩阵
    Matrix<double,dim_v,dim_v> R;//测量噪声
    Matrix<double,dim_a,dim_a> Q;//过程噪声
    Matrix<double,dim_a,dim_v> K;//卡尔曼增益
    double dt;//时间步长
public:
    //初始化
    EKF():X(Matrix<double,dim_a,1>::Zero()),
          P(Matrix<double,dim_a,dim_a>::Identity()),
          Q(Matrix<double,dim_v,dim_a>::Identity()),
          R(Matrix<double,dim_v,dim_v>::Identity()){}
    EKF(const Matrix<double,dim_v,dim_a> &Q0,const Matrix<double,dim_v,dim_v> &R0): 
          X(Matrix<double,dim_a,1>::Zero()),
          P(Matrix<double,dim_a,dim_a>::Identity()),
          Q(Q0),
          R(R0){}
    EKF(double init_x , double init_y,double init_z,
        double init_vx,double init_vy,double init_vz,
        double init_w,double radius){
            X = Matrix<double,dim_a,1>::Zero();
            X<<init_x,init_y,init_z,init_vx,,init_vy,init_vz,0,init_w,0,radius;
            //假设是绕着Y轴旋转则X,Z的角速度w为0
            
            //初始化P
            P = Matrix<double,dim_a,dim_a>::Identity();
            P.block<3,3>(0,0)*=0.1;//位置部分
            P.block<3,3>(3,3)*=0.05;//速度部分
            P.block<3,3>(6,6)*=0.01;//角速度部分
            p(9,9) = 0.001;//旋转半径

            //初始化R
            R = Matrix<double,dim_v,dim_v>::Identity()*0.02;

            //初始化H
            //因为只能测量位置，也就是x,y,z
            H = Matrix<double,dim_v,dim_a>::Zero();
            H(0,0) = 1;
            H(1,1) = 1;
            H(2,2) = 1;

            F = Matrix<double,dim_a,dim_a>::Indentity();
        }   
    //设置时间步长并且更新相关矩阵
    void set_time(double dt_in){
        F = Matrix<double,dim_a,dim_a>::Indentity();
        dt = dt_in;
        //因为是设置的匀速运动模型，所以v,w,r都不会有变化
        F(0,3) = dt;
        F(1,4) = dt;
        F(2,5) = dt;
        //设置过程噪声Q,设所有的噪声都独立
        Q = Matrix<double,dim_v,dim_a>::Identity();
        double pos_noi = dt*dt*0.1;
        double v_noi = dt*0.2;
        double omega_noi = dt*0.01;

        for (size_t i = 0; i < 3; i++)
        {
            Q(i,i) = pos_noi;
            Q(i+3,i+3) = v_noi;
            Q(i+6,i+6) = omega_noi;
        }
        //都设置完了还差一个就是旋转半径的过程噪声
        Q(9,9) = 0.0001;
    }
    //进行预测
    void predict(){
        //首先更新位置
        X.segment(0.0)+=dt*x.segement(0.3);
        //其次更新状态协方差矩阵
        p = F*p*F.transpose()+Q;
    }

    //进行更新(滤波操作)
    void update(const Matrix<double,1,dim_v> measure){
        //传入测量值
        //其次，旋转角度 = 角速度w*时间dt
        double angle = X(7)*dt;
        //计算偏移量
        Matrix<double,1,3> offset(X(9)*sin(angle),X(9)*cos(angle),0);//假设Z轴无偏移量
        //计算理想测量值
        Matrix3d expct_measure = X.segment(0.0) + angle.segment(0.3);
        //计算残差
        Matrix<double,1,dim_v> redisul= measure - expct_measure;
        //计算卡尔曼增益
        K = P*H.transpose()*(H*p*H.transpose() + R).inverse();
        //更新X
        X = X + K*redisul;
        //更新P
        P = (Matrix<double,dim_a,dim_a>::Identity() - K*H)*P;
    }

    //预测未来位置
    Matrix<double,1,dim_v> pred_impact_point(double bullet_time,double bullet_speed){
        //先计算当前位置
        Matrix<doouble,1,dim_v>index = x.segment(0,0) + x.segment(0,3)*bullet_time;
        //计算未来旋转角
        double angle_future = X(7)*bullet_time;
        //计算旋转后的打击点
        Matrix<double,1,dim_v> future_point = index + Matrix<double,1,dim_v>(X(9)*sin(angle_future),X(9)*cos(angle_future),0)
        return future_point;
    }

    Matrix<double,1,dim_v> get_pos(){return X.block<1,3>(0,0);}
    Matrix<double,1,dim_v> get_velc(){return X.block<1,3>(0,3);}
    double get_omega(){return X(7);}
    double get_radius(){return X(9);}
};

int main(){

}