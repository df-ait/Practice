#元组是一个不可修改的，有序的序列。一旦创建就不能修改其中的元素
print("创建元组")
#法1:使用圆括号
my_tuple = (1,2,3,'hello')
print(my_tuple)
#法2:不使用括号，但是用逗号隔开
tuple_1 = 4,5,6,'world'
print(tuple_1)
#创建单个元素的元组(注意结尾逗号)
single_tuple = (42,)
not_tuple = (42)
print(single_tuple)
print(type(single_tuple))
print(type(not_tuple))
#如果不加逗号，那他就只是一个整数42
#空元组
empty_tuple = ()

print("访问元组元素")
fruit = ("apple","banana","orange",47,82,'c')
#          0        1         2    3   4  5
#         -6        -5        -4   -3  -2  -1
#索引访问
print(fruit[0])
print(fruit[1])
print(fruit[2])
print(fruit[-1])
print(fruit[-2])
print(fruit[-3])
#切片索引
print(fruit[1:3])
print(fruit[1:])
print(fruit[:2])
print(fruit[0:5:2])
print(fruit[:])
#元组和列表最大的区别就是，元组是不可变的
print('元组的基本操作')
print('连接元组')
tuple1 = 2,3,4,5,6,7
tuple2 = 'name','home','person'
print(tuple1)
print(tuple2)
combine = tuple1 + tuple2
print(combine)

print('重复元组')
repeat = combine*2
print(repeat)
print(tuple2*3)

print('成员检测')
if 2 in tuple1:
    print("yes")
if 3 in tuple2:
    print("yes!")
else:
    print("no")
print(f"tuple1 max {max(tuple1)}")
print(f"tuple2 max {max(tuple2)}")
print(f"tuple1 min {min(tuple1)}")
print(f"tuple2 min {min(tuple2)}")
print(f"tuple1 size {len(tuple1)}")
print(f"tuple2 size {len(tuple2)}")

print("元组解包")
#基本解包
point = (10,20)
print(point)
x,y = point
print(f"x={x},y={y}")
#交换变量
a,b = 5 , 10
print(f"a={a},b={b}")
a,b = b,a#实际上是创建了一个元组(b,a)然后解包
print(f"a={a},b={b}")

#使用*收集多余元素
first,*middle,last = 1,2,3,4,5
print(f"first={first},middle={middle},last={last}")

print("列表--->元组")
my_list = [1,2,3,4,5]
print(my_list)
my_tuple = tuple(my_list)
print(my_tuple)

print("元组--->列表")
tuple_a = 4,5,7,8,1,
print(tuple_a)
llist_a = list(tuple_a)
print(llist_a)

print("元组常用方法")
print(my_tuple)
print(f"my_tuple 2 in this times = {my_tuple.count(2)}")
print(f"my_tuple 2 in this index = {my_tuple.index(4)}")
