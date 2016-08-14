# CodePractice
一些编程代码

##一、Projects_c
- 这里包含《C语言程序设计》谭浩强版、《C和指针》课后习题以及一些相关的C编程练习题；

##二、Projects_c++

##三、Projects_DataStructer
- 一些数据结构：栈、队列、链表、二叉树、小根堆、 进程调度算法、赫夫曼编码等
- 后序将上传AVLtree、RBtree等

##四、Projects_Algorithm
- 常用算法

##五、memcached-1.4.20
- 这里包含对memcached-1.4.20源码剖析的一些注解</br>

###剖析方式
1.工具:[source insight](http://www.sourceinsight.com/)</br>
2.[安装使用memcached](http://www.cnblogs.com/luowei010101/archive/2012/09/01/2667046.html)</br>
3.从memcached.c的main函数开始，分模块剖析

###剖析的主要模块有：</br>
- 内存分配方式
- 事件处理流程
- 命令处理方式（状态机）
- consistent hashing算法

###内存分配方式:块页式
![](https://github.com/qinyuLT/Images/blob/master/memcached%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D1.png "内存分配方式")</br>

###内存分配函数调用过程
![](https://github.com/qinyuLT/Images/blob/master/memcached%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D%E6%80%BB%E7%BB%932.png "内存分配函数调用过程")</br>

###事件处理流程：主要对应于static void drive_machine(conn *c);//memcached.c
![](https://github.com/qinyuLT/Images/blob/master/memcache%20%E9%80%9A%E4%BF%A1%E6%95%B4%E4%BD%93%E6%B5%81%E7%A8%8B.png)</br>

###状态机思想：修改状态达到切换命令的目的
![](https://github.com/qinyuLT/Images/blob/master/%E7%8A%B6%E6%80%81%E6%9C%BA%E4%BB%A5%E5%8F%8A%E5%91%BD%E4%BB%A4%E5%A4%84%E7%90%86%E6%B5%81%E7%A8%8B.png)</br>
