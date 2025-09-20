#列表list是一个可变的有序序列，能存储任意类型的数据(甚至混合类型)
#底层通过动态数组实现
#介绍基本操作‘

#######创建列表######
empty_list = []#创建空列表
#创建包含元素的列表
print("创建列表")
numbers = [1,2,3,4]
print(numbers)
mixed = [1,"apple",2,"banana"]
print(mixed)
nested_list = [[1,2,3],[4,5,6],[7,8,9]]
print(nested_list)

########访问元素######
print("访问列表元素")
fruits = ["apple","banana","orange"]#从左往右下标是:0  1  2
                                    #从右往左下标是-1 -2 -3
print(fruits)
print("This is the index 0：",fruits[0])
print("This is the index 1：",fruits[1])
print("This is the index 2：",fruits[2])
print("This is the index -1：",fruits[-1])
print("This is the index -2：",fruits[-2])
print("This is the index -3：",fruits[-3])

#####切片(提取子列表)########
print("切片(提取子列表)")
number = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
print(number)
print(number[1:4])#输出[2 ,3 ,4]从下标为1的地方开始，走四布但是左闭右开
print(number[:3])#输出[1，2，3]
print(number[2:])#输出[3 ,4 ,5 ，6  ,7 ,8 ,9 ,10 ,11 ,12 ,13 ,14 ,15]
print(number[:])#全部输出
print(number[::2])#输出[1,3,5,7,9,11,13,15]从下标为0的位置开始访问，但是步长为2

#######修改列表元素#########33
print("修改列表元素")
fruits = ["apple","banana","orange"]
print(fruits)
fruits[1] = "watermelon"#直接通过索引修改
print(fruits)

#########添加元素########
print("添加列表元素")
fruits = ["apple","banana","orange"]
print(fruits)
fruits.append("watermelon")#在列表末尾加了一个watermelon
print(fruits)
fruits.insert(1,"peach")#在指定位置插入元素
print(fruits)
fruits.extend(["pear","grape","mango"])#合并两个列表
print(fruits)

#####删除列表元素#########
print("删除列表元素")
print(fruits)
fruits.pop()#移除末尾元素
print(fruits)
fruits.pop(2)#移除下标为2的元素
print(fruits)
fruits.remove("grape")#删除指定值
print(fruits)
del fruits[2:4]#删除切片范围内的元素，依旧左闭右开，删除了下标为2 ，3 的元素
print(fruits)

#######列表推导式########
#生成平方数列表
print("列表推导式")
squares = [x**2 for x in [1,2,3,4]]
print(squares)
squares = [x**2 for x in range(4)]#这里是0 1 2 3
print(squares)

#带条件的推导式
evens = [x for x in range(10) if x % 2 == 0]#在[0,10)中，如果x%2==0,就放入列表中
print(evens)

######列表与循环结合########
print("列表与循环结合")
fruits = ["apple","banana","orange"]
for i,fruit in enumerate(fruits):
    print(f"第{i}个水果是{fruit}")

#######常用内置方法#######
X = [1,2,3,4,5,5,4,3,2,0]
print(X)
print(f"这个列表的长度为{len(X)}")
print(f"0在列表中出现的次数为{X.count(0)}")
print(f"7在列表中出现的次数为{X.count(7)}")
print(f"2在列表中出现的次数为{X.count(2)}")
#查找索引
print(f"数字2的下标为{X.index(2)}")
X.reverse()
print(f"翻转后的列表为",end="")
print(X)
X.sort()
print(f"排序后的列表为",end="")
print(X)

##内存原理:列表存储的是对象的引用，而非对象本身，类似于C中的指针
a = [7,6,5,4]
b = a#此时a,b其实是指向了同一个列表对象
print(f"这是a列表{a}")
print(f"这是b列表{b}")
b[0] = 99;
print(f"这是修改了b列表以后的a列表{a}")
#使用正确的拷贝方法就不会有这种情况
c = a[:]#c = a.copy() 或者用 c = a[:]
print(f"这是a列表{a}")
print(f"这是c列表{c}")
c[1]=100
print(f"这是修改了c列表以后的a列表{a}")
print(f"这是修改后的c列表{c}")


#########################################################
########实践：统计一段文本中每个单词的出现次数################
string_in = input("请输入一串英文文本:")
print(string_in)
words = string_in.split()#将一整段文本分割为列表
word_count = {}
for word in words:
    if word in word_count:
        word_count[word] += 1
    else:
        word_count[word] = 1
print(word_count)