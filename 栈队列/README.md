设置了两个类：stack ，order_team;分别为栈和队列；两个类均包含了DoubleLink 双向链表的类；将DoubleLink类放入Doublelink.h头文件中封装。在stack，和order_team,两个类中直接引用头文件"DoubleLink.h" ，来实现栈和队列的功能；
### 栈：
IsEmpty()//如果栈为空返回true，否则返回false  
size()//返回栈中元素的个数  
pop()//删除栈顶元素但不返回其值  
top()//返回栈顶的元素，但不删除该元素  
push(X)//在栈顶压入新元素 ，参数X为要压入的元素

### 队列:
IsEmpty()// 如果队列为空返回true，否则返回false  
size() // 返回队列中元素的个数  
pop()  //删除队列首元素但不返回其值  
front()  // 返回队首元素的值，但不删除该元素  
push(X) //在队尾压入新元素 ，X为要压入的元素
back() //返回队列尾元素的值，但不删除该元素  
