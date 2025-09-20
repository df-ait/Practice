#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <vector>
#include <fstream>

using namespace cv;
using namespace std;
using namespace dnn;

//加载类别名称函数
vector<string> load_class_names(const string& filepath){
    vector<string> classnames;
    ifstream ifs(filepath.c_str());
    string line;
    while (getline(ifs,line))
    {
        classnames.push_back(line);
    }
    return classnames;
}

//入口函数
int main(){
    //加载网络
    string model_config = "yolov3.cfg";
    string model_weight = "yolov3.weights";
    Net net = readNetFromDarknet(model_config,model_weight);
    net.setPreferableBackend(DNN_BACKEND_OPENCV);
    net.setPreferableTarget(DNN_TARGET_CPU);

    //加载类别名称
    vector<string> classnames = load_class_names("coco.names");

    //打开摄像头
    VideoCapture cap(0);
    if(!cap.isOpened()){
        cerr<<"无法打开摄像头"<<endl;
        return -1;
    }

    Mat frame,blob;
    vector<Mat> outputs;

    while (true)
    {
        cap>>frame;
        if(frame.empty()) break;

        //创建blob并且从网络获取输出
        blobFromImage(frame , blob ,1/255.0,Size(416,416),Scalar(0,0,0),true,false);
        net.setInput(blob);
        net.forward(outputs , net.getUnconnectedOutLayersNames());

        //处理输出
        vector<int> classIds;
        vector<float> confidences;
        vector<Rect> boxes;

        for(auto& output:outputs){
            auto* data = (float*)output.data;
            for(int i = 0;i < output.rows;i++,data+=output.cols){
                Mat scores = output.row(i).colRange(5,output.cols);
                Point class_id_point;
                double confidence;
                minMaxLoc(scores,0,&confidence,0,&class_id_point);

                if(confidence > 0.5){
                    int centerX = (int)(data[0] * frame.cols);
                    int centerY = (int)(data[1] * frame.rows);
                    int width = (int)(data[2] * frame.cols);
                    int height = (int)(data[3] * frame.rows);
                    int left = centerX - width/2;
                    int top = centerY - height/2;

                    classIds.push_back(class_id_point.x);
                    confidences.push_back((float)confidence);
                    boxes.push_back(Rect(left,top,width,height));

                }
            }
        }

        //非最大抑制
        vector<int>indices;
        NMSBoxes(boxes , confidences , 0.5 , 0.4 , indices);

        //绘制检测成果
        for(size_t i = 0 ; i<indices.size();i++){
            int idx = indices[i];
            Rect box = boxes[idx];
            string label = format("%s:%.2f",classnames[classIds[idx]].c_str(),confidences[idx]);
            rectangle(frame , box , Scalar(0,255,0),2);
            putText(frame,label,Point(box.x,box.y - 10),FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,255,0),2);
        }

        imshow("YOLO obiect detection",frame);

        if(waitKey(1) == 0) break;

    }
    
    return 0;

}