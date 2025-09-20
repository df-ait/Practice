//二维度的卡尔曼滤波可以引入Eigen库来简化矩阵运算
//这个库是C++中的线性代数库

#include <iostream>
#include <Eigen/Dense>
#include <random>
using namespace Eigen;

class KF2{
private:
    Vector4d X;//当前状态
    Matrix4d P;//状态协方差矩阵
    Matrix4d F;//状态转移矩阵
    Matrix<double , 2 , 4> H;//观测矩阵
    Matrix4d Q;//过程噪声协方差矩阵
    Matrix2d R;//测量噪声协方差矩阵
    Matrix<double , 4 , 2> K;//卡尔曼增益矩阵
public:
    KF2(double init_x , double init_v , double init_vx , double init_vy , 
        double process_noi_q , double measure_noi_r){
            //初始化当前状态
            X<<init_x,init_v,init_vx,init_vy;
            //初始化状态协方差矩阵
            P = Matrix4d::Identity();
            //初始化过程噪声协方差矩阵和观测噪声协方差
            Q = Matrix4d::Identity()*process_noi_q;
            R = Matrix2d::Identity()*measure_noi_r;
            //初始化观测矩阵，因为只能观测位置，也就是vx,vy
            H<<1,0,0,0,
               0,1,0,0; 
        }

    //设置时间步长
    void set_time(double dt){
        //设置状态转移矩阵
        F<<1,0,dt,0,
           0,1,0,dt,
           0,0,1,0,
           0,0,0,1;
        return; 
    }

    //进行预测
    void predict(){
        X = F*X;
        P = F*P*F.transpose()+Q;
        return;
    }

    //滤波更新
    void update(double true_x ,double true_y){
        Vector2d T_X;
        T_X<<true_x,true_y;
        //计算残差
        Vector2d residual = T_X - H*X;
        //先计算卡尔曼增益
        K = P*H.transpose()*(H*P*H.transpose()+R).inverse();
        //计算更新后的X
        X = X + K*residual;
        //更新状态协方差矩阵
        P = (Matrix4d::Identity() - K*H)*P;
        return;
    }

    //获取当前状态,单个数据or向量
    void get_state(double now_x , double now_y,double now_vx , double now_vy){
        now_x = X(0);
        now_y = X(1);
        now_vx = X(2);
        now_vy = X(3);
        return;
    }

    Vector4d get_state(){
        return X;
    }
};

int main(){
    //先弄随机噪声
    std::random_device generation;
    std::mt19937 gen(generation());
    std::normal_distribution distirb(0.0 , 1.0);

    //给定小车的真实速度和距离
    Vector4d true_car;
    true_car<<1.0,2.0,1.5,0.5;

    //给定卡尔曼滤波一开始的猜测值（初始化卡尔曼滤波）
    KF2 kalmen(0 ,0, 1.0 ,1.0 ,0.5 ,0.2);
    //别忘了要给时间步长
    double dt = 0.1;
    kalmen.set_time(dt);
    std::cout<<"times\t x\t y\t vx\t vy\t m_x\t m_y\t x*\t y*\t vx*\t vy*\n";

    //假设滤波20次
    for(int i = 0 ;i<20 ; i++){
        //更新小车的运动位置
        true_car(0) += dt*true_car(2);
        true_car(1) += dt*true_car(3);

        //传感器得到带有噪声的测量值
        double measure_x,measure_y;
        measure_x = true_car(0) + distirb(gen)*0.2;
        measure_y = true_car(1) + distirb(gen)*0.2;

        kalmen.predict();
        kalmen.update(measure_x,measure_y);

        Vector4d reuslt = kalmen.get_state();
        std::cout<<i+1<<"\t"<<true_car(0)<<"\t"<<true_car(1)<<"\t"<<true_car(2)<<"\t"<<true_car(3)<<"\t"
        <<measure_x<<"\t"<<measure_y<<"\t"
        <<reuslt(0)<<"\t"<<reuslt(1)<<"\t"<<reuslt(2)<<"\t"<<reuslt(3)<<std::endl;
    }

    return 0;
}