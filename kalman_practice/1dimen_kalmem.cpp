#include <iostream>
#include <random>
#include <vector>
#include <cmath>

class KF
{
private:
    double X;//状态转移
    double P;//预测数据协方差
    double Q;//过程噪声协方差
    double R;//测量噪声协方差
    double K;//卡尔曼增益
public:
    KF(double est_x,double est_p,double process_noi_q ,double measure_noi_r):X(est_x),P(est_p),Q(process_noi_q),R(measure_noi_r){};

    //预测更新以后的值
    void predict(){
        //简单模型，假设状态不变
        X = X;
        P = P+Q;
        return;
    }

    //更新测量值
    void update(double measurement){
        //计算卡尔曼增益
        K = P/(P+R);
        //更新估计值
        X = X + K*(measurement - X);
        //更新协方差
        P = (1 - K)*P;
        return;
    }

    //获取当前状态值
    double get_state(){
        return X;
    }
};

//遵循正态分布的随机数生成器，用于生成随即噪声
double set_noise(double avg , double vari){
    //传入的是均值和方差
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution distrib(avg , vari);
    return distrib(gen);
}

int main(){
    //设置随即噪声
    
    //设置卡尔曼滤波器初始值和真实值
    double true_val = 25;//例如真实温度为25度
    double init_val = 20;//传递给卡尔曼滤波器的初始温度为20度
    //初始化卡尔曼滤波器
    KF kalmen(init_val , 1.0 , 0.01 , 1.0);

    std::cout<<"迭代次数 真实值\t测量值\t滤波值\n";
    //假设进行了20次迭代
    for (size_t i = 0; i < 20; i++)
    {
        double noise_Q = set_noise(0.0 , 1.0);
        double measure = true_val + noise_Q*2.0;
        //卡尔曼滤波预测
        kalmen.predict();
        //传入测量值给卡尔曼滤波进行更新
        kalmen.update(measure);
        //获取的预测值
        double now_x = kalmen.get_state();
        std::cout<<" "<<i+1<<"\t"<<true_val<<"\t"<<measure<<"\t"<<now_x<<std::endl;
    }    
    return 0;
}