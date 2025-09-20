import  numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def cal_cost(X,y,theta):
    inner = np.power((X*theta.T)-y,2)
    J = np.sum(inner)/(len(X)*2)
    return J

def gredience(X,y,theta,time,alpha):
    temp_thete = np.matrix(np.zeros(theta.shape))
    param = int(theta.shape[1])
    cost = np.zeros(time)
    for i in range(time):
        error = (X*theta.T)-y
        for j in range(param):
            term = np.multiply(error,X[:,j])
            temp_thete[0,j] = theta[0,j]-((alpha/len(X))*np.sum(term))
        theta = temp_thete
        cost[i] = cal_cost(X,y,theta)
    return theta,cost    
    
path = '../deepLearning_programe/exldatal.txt'
data = pd.read_csv(path,header=None,names=['population','profit'])
data.head()
data.describe()
data.plot(kind='scatter',x='population',y='profit')
plt.show()
data.insert(0,'ONES',1)
data.head()

cols = data.shape[1]
X = data.iloc[:,0:cols-1]
Y = data.iloc[:,cols-1:cols]
X.head()
Y.head()

X = np.matrix(X.values)
Y = np.matrix(Y.values)
theta = np.matrix(np.array([0,0]))
print(X.shape)
print(Y.shape)
print(theta.shape)
cost = cal_cost(X,Y,theta)

alpha = 0.01
time = 1000
newtheta,cost = gredience(X,Y,theta,time,alpha)
print(newtheta)
print(cost)
newcost = cal_cost(X,Y,newtheta)
print(newcost)

x = np.linspace(data.population.max(),data.population.min(),100)#抽样范围为dta数据中population那一栏的最大值到最小值之间，抽取100个样本
#定义一个类似于函数表达式的东西
f = newtheta[0,0] + (newtheta[0,1]*x)#就是函数表达式 y = b + w * x

fig,ax = plt.subplots(figsize = (12,8))#创建一个12*8的画布，并生成一个单独的子图，fig是存储画布的对象，而ax是存储子图的对象
ax.plot(x,f,'r',label = 'Prediction')#这是子图（arex）的方法，用于在子图上绘制折线图，传入x,y轴的数据，然后规定折线颜色和这条折线的图例标签
ax.scatter(data.population,data.profit,label = 'Training Data')#在子图上绘制散点图，传入每个点的X,Y轴坐标，然后给这些点规定图例标签
ax.legend(loc = 4)#在右下角设置标签
ax.set_xlabel('Population')
ax.set_ylabel('Profit')
ax.set_title('Predict profit size vs population')
plt.show()

fig,ax = plt.subplots(figsize = (12,8))
ax.plot(np.arange(time),cost,'r',label = 'Cost')
ax.set_xlabel('Times')
ax.set_ylabel('Cost')
ax.set_title('Cost vs Times')
plt.show()