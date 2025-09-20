#dict就是字典，相当于STL中的map
#键必须不可变(字符串，数字，元组等)，值可以是任意类型

#####基本操作
##########创建字典######3
print('创建字典')
#创建一个空字典
empty_dict = {}
#创建带初始值的字典
user = {"name":"ALICE","age":18,"birth":20061106}
scores = {"chinese":91,"math":150,"Eng":121}
#使用dict的构造函数
user2 = dict(name = "Bob",age = 21)
print(user)
print(user2)
print(scores)

######访问元素######
print("访问元素")
#通过键访问
print(user2["name"])
print(user2["age"])
#安全访问，使用get,避免KeyError
print(user2.get("birth"))#输出NONE,因为没有给user2定义生日
print(user2.get("gender","xx"))#输出xx
print(user.get("birth"))
#检查键是否存在
if "age" in user:
    age = user.get("age")
    print(f"age involved in user ,age is {age}")


#########添加/修改元素########
print("添加/修改元素")
fruit = {"apple":1,"banana":2,"orange":3}
#添加新键值对
print(fruit)
fruit["pear"] = 4
print(fruit)
#修改已有的值
fruit["orange"] = 5
print(fruit)
#批量更新
fruit.update({"city":"chongqing","total_price":150})
print(fruit)

########删除元素#########
print("删除元素")
print(fruit)
#删除并返回值
delete = fruit.pop("banana")
print(delete)
print(fruit)
#直接删除
del fruit["pear"]
print(fruit)
#请空字典
fruit.clear()
print(fruit)

##########遍历字典#########
print("遍历字典")
fruit = {"apple":1,"banana":2,"orange":3}
print(fruit)
#遍历键
for key in fruit:
    print(f"key-{key}->board-{fruit[key]}")
#键值对遍历
for key,value in fruit.items():
    print(f"{key}->{value}")

#####字典推导式########
print("字典推导式")
#快速创建字典
square = {x:x**2 for x in range(5)}
print(f"square:{square}")
even_square = {x:x**2 for x in range(1,11) if x%2==0}
print(f"even_square:{even_square}")

#####嵌套字典######
students = {
    "001":{
        "name":"Bob",
        "age":18,
        "scores":{"chinese":105,"math":150,"Eng":121},
    },
    "002":{
        "name":"Alice",
        "age":19,
        "scores":{"chinese":95,"math":150,"Eng":121}
    }
}
# print(students)
#访问嵌套数据
math = students["001"]["scores"]["math"]
print(math)