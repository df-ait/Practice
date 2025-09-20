# print('hello world')
#
a=3
b=5
# print(a+b)
#
# #用逗号隔开就不换行
# print(a,b,a*b)
# #字符串拼接输出
# print('Now you will see a number',a,'\nyou see the number now')
#模板输出
print(f"你现在看见的数是{a}和{b},他们的和为{a+b}")

#input函数使用
# a=input('pls enter a：')
# b=input('pls enter b:')
#if-else语句感觉与C一样
# if a>b:
#     print('a is greater than b')
# else:
#     print('b is greater than a')
#
# c=input('pls enter c:')
# if a == b and a > c:
#     print('a equal b,but a is greater than c')
# else:
#     print('b is not equal a')

#for循环 基础语法
# name = input('pls enter your name:')
name = 'W'
print('hello ',end="")#用end=""来取消print自带的换行符
for x in name:
    print(x,end="")
print('\n')
#for循环 range语句 左闭右开的形式
num = 10
range(num)
print(range(num))#输出range(0,10)
for i in range(num):
    print(i,' ',end=" ")#输出0 1 2 3 4 5 6 7 8 9

num1 = 4
num2 = 7
range(num1,num2)
print(range(num1,num2))#输出range(4,7)
for i in range(num1,num2):
    print(i,' ',end=" ")#输出4 5 6

step = 2#规定的步长
num3 = 0
num4 = 14
range(num3,num4,step)
print(range(num3,num4,step)) #输出range(0,14,2)
for i in range(num3,num4,step):
    print(i,' ',end=" ") #输出0 2 4 6 8 10 12

i = 0
for i in range(10):
    print(i,end=' ')
print('\n',i)#循环过后 i 就变成9了

#while语句
i=20
while i>=10:#后面是循环进行的条件
    print(i,end=' ')
    i-=1
i = 20
print('\n')
while i>10:#后面是循环进行的条件
    print(i,end=' ')
    i-=1

#pass break continue
num = 10
if num == 10:
    pass #pass过(当不能直接在代码快中写上具体代码时，先用pass占位
    # continue和break其实就跟c++/c里是一样的

