#include<stdio.h>  
#include<stdlib.h> 
#include<string.h> 
#include<assert.h>
#include<iostream>
#include<iomanip>
#include<queue>
//#include<windows.h>  //cls
using namespace std;

/*操作系统进程调度算法
	a.先来先服务算法
	b.短作业优先算法
	c.时间片轮转算法  
*/
typedef struct processNode  
{  
    char name;   
	char *state;           // 
	float rest;            //      
    float arrivetime;   
    float servetime;    
    float finishtime;  
    float roundtime;    
    float daiquantime;  
    //struct processNode *next;//
  
}processNode;   

typedef struct processNode process_FCFS;
typedef struct processNode process_TimeSlice;
 
process_TimeSlice *head;
process_FCFS a[100];

////////////////////////////函数声明/////////////////////////////////
void showChoice(); 
void getInfo(process_FCFS a[],int &n);
void showSliceProcInfo(process_FCFS a[],int n);
void showProcessInfo(process_FCFS a[],int n,float &t1, float &t2);

process_FCFS *sortArriveTime(process_FCFS a[],int n);   
process_FCFS *sortServeTime(process_FCFS a[],int n);  

void Fcfs(process_FCFS a[],int n,float &t1, float &t2);

int findSuitabllePro(process_FCFS a[],int *flag,int n);
void SPN(process_FCFS a[],int n,float &t1, float &t2);

process_TimeSlice *createQueue(int &n);     
//void RR(process_TimeSlice *head, int &n); 
/////////////////////////////////////////////////////////////////////

void showChoice()
{
	cout<<"########## 进程调度 ###########"<<endl;
	cout<<"#      a.先来先服务算法       #"<<endl;
	cout<<"#      b.短作业优先算法       #"<<endl;
	cout<<"#      c.时间片轮转算法       #"<<endl;
	cout<<"#      e.退  出  程  序       #"<<endl;
	cout<<"###############################"<<endl;
} 

void getInfo(process_FCFS a[],int &n)
{
	cout<<"请输入进程数：";  
	cin>>n;
	cout<<"请依次输入："<<n<<"个进程名  到达时间  服务时间"<<endl; 
    for(int i=0;i<n;i++)  
    {  
        cout<<i+1<<": ";
		cin>>a[i].name>>a[i].arrivetime>>a[i].servetime;  
		a[i].rest = a[i].servetime;//时间片轮转算法才会用到下面赋值 
		a[i].state = "ready";      //
	}  
}

//FcFs,SPN
void showProcessInfo(process_FCFS a[],int n,float &t1, float &t2)
{
	cout<<"进程名 "<<"到达时间  "<<"服务时间  "<<"完成时间  "<<"周转时间 "<<"带权周转时间"<<endl;
    for(int i=0;i<n;i++)  
    { 
        printf("%3c%10.2f%10.2f%10.2f%10.2f%10.2f\n",a[i].name,a[i].arrivetime,a[i].servetime,
												a[i].finishtime,a[i].roundtime,a[i].daiquantime); 
        t1 += a[i].roundtime;  
        t2 += a[i].daiquantime;  
    } 
}
  
//按到达时间进行冒泡排序  
process_FCFS *sortArriveTime(process_FCFS a[],int n)  
{  
    int i,j;  
    process_FCFS t;  
    int flag;  
    for(i=0;i<n;i++)  
    {  
        flag=0;  
        for(j=i+1;j<n;j++)  
        {  
            if(a[i].arrivetime>a[j].arrivetime)    //服务时间
            {  
                t=a[i];  
                a[i]=a[j];  
                a[j]=t;  
                flag=1; 
            }  
        }  
        if(flag==0)   
        {  
            break;  
        }  
    }  
 
    return a;   //返回排序后进程数组   
}  
  
//按服务时间进行冒泡排序  
process_FCFS *sortServeTime(process_FCFS a[],int n)  
{  
    int i,j;  
    process_FCFS t;    
    for(i=0;i<n;i++)  
    {  
        for(j=i+1;j<n;j++)  
        {  
            if(a[i].servetime>a[j].servetime)    //服务时间
            {  
                t=a[i];  
                a[i]=a[j];  
                a[j]=t;  
            }  
        }   
    }  
    return a;   //返回排序后进程数组  
}  

//先来先服务算法  
void Fcfs(process_FCFS a[],int n,float &t1, float &t2)  
{  
	a[0].finishtime=a[0].arrivetime+a[0].servetime; //完成时间=到达时间-服务时间  
    a[0].roundtime=a[0].finishtime-a[0].arrivetime; //周转时间=完成时间-提交时间  
    a[0].daiquantime=a[0].roundtime/a[0].servetime; //带权时间=周转时间/服务时间  
    
    //showProcessInfo(a,n,t1,t2);
    
    for(int i=1;i<n;i++)  
    {  
        if(a[i].arrivetime<a[i-1].finishtime)    
        {  
            a[i].finishtime=a[i-1].finishtime+a[i].servetime;      
        }  
        else    //上一个作业结束的时间 未达到 当前进程到达时间  
        {  
            a[i].finishtime=a[i].arrivetime+a[i].servetime;   
        }
		a[i].roundtime=a[i].finishtime-a[i].arrivetime;  
        a[i].daiquantime=a[i].roundtime/a[i].servetime;
  
    }
  	showProcessInfo(a,n,t1,t2);
}  

int findSuitabllePro(process_FCFS a[],int *flag,int n)
{
	int i,procNumber;
	for(i=0;i<n;++i)
	{
		if(flag[i] != 0)
		{
			procNumber=i;
		}		
	}
	for(i=0;i<n;++i)//寻找没有执行的进程中最先到达的进程 
	{
		//cout<<flag[i]<<" ";
		if(flag[i]== 1 && a[procNumber].arrivetime > a[i].arrivetime)
		{
			procNumber = i;
		}
	}
	//cout<<endl;
	return procNumber;//返回找到的进程号 
}


//短作业优先算法  
void SPN(process_FCFS a[],int n,float &t1, float &t2)  
{   
	int i=0,number=0,j; 
	int *flag = (int*)malloc(sizeof(int)*n);//flag数组用来标记n个进程是否已经被执行 
	float time = 0;

	for(i=0;i<n;++i)
		flag[i]=1;       //开始都赋值1，表示都没有执行 
		
	while(number < n)
	{
		for(j=0;j<n;++j)
		{
			if(flag[j] == 1)
			{
				i = j;
				break;
			}
		}
		//cout<<"time = "<<time<<endl;
		if(time < a[i].arrivetime)
		{
			i = findSuitabllePro(a,flag,n);//寻找合适的（即已经到达的）
		}
		//cout<<"i= "<<i<<endl;

		if(a[i].arrivetime == 0)
			a[i].finishtime = a[i].servetime;
		else if(a[i].arrivetime < time)
			a[i].finishtime = time+a[i].servetime;
		else
			a[i].finishtime = a[i].servetime + a[i].arrivetime;
        
		a[i].roundtime=a[i].finishtime-a[i].arrivetime;   
        a[i].daiquantime=a[i].roundtime/a[i].servetime;       
        time = a[i].finishtime;
		flag[i] = 0;
		number++;
	}
    showProcessInfo(a,n,t1,t2);
    free(flag); 
}  

void RR(process_FCFS an[],int n)
{
	process_FCFS *p,*t,*r;  
    float slice = 0.0f;  
    float temp = 0.0f;  
    float time = 0.0f ;
    float sum_zhouzhuan = 0.0f, sum_daiquan = 0.0f; 
	int i=0;
   
	cout<<"请输入时间块大小: "; 
	cin>>slice;

	queue<process_FCFS *> activeQue;
	activeQue.push(&an[i++]);

	while(!activeQue.empty())
	{
		p = activeQue.front();
		t = p;

		time += slice;
		temp = p->rest; 
        p->rest = p->rest - slice;    //剩余时间
		p->state = "running";

		if(i < n)
			activeQue.push(&an[i++]);
		
		if(p->rest <= 0) //剩余时间为0，删除
		{
			time = time - slice + temp;          //进程完成时间  
            p->roundtime = time - p->arrivetime;
            p->daiquantime = p->roundtime/(p->servetime);
            sum_zhouzhuan += p->roundtime;
            sum_daiquan += p->daiquantime;
            p->rest = 0; 
			
			cout<<"\n********************************************************************************\n";   

			cout<<"进程名 "<<"到达时间  "<<"服务时间  "<<"剩余时间 "<<"进程状态 "<<"完成时间  "<<"周转时间 "<<"带权周转时间"<<endl;
			
			printf("%3c%10.2f%10.2f%10.2f%10s%",p->name,p->arrivetime,p->servetime,p->rest,p->state);  
            cout<<setw(8)<<time<<setw(10)<<p->roundtime<<setw(10)<<p->daiquantime<<endl;
		
			activeQue.pop();
		}
		if(p->rest > 0)//有剩余时间，继续插入
		{
			r = activeQue.front();
			activeQue.pop();
			activeQue.push(r);
		}	
	} 
    cout<<"\n总周转时间： "<<sum_zhouzhuan;
    cout<<"\n总带权周转时间： "<<sum_daiquan;
    cout<<"\n平均周转时间： "<<sum_zhouzhuan/n;
    cout<<"\n平均带权周转时间： "<<sum_daiquan/n<<endl;
}

int main()  
{  
    float t1 = 0.0f;       //总周转时间  
    float t2 = 0.0f;       //总带权周转时间  
    int n;                 //n：进程个数 
    char choice = ' ';     //选择算法变量标识  

	while (choice != 'e' && choice != 'E')  //不为退出标识，保持循环  
    {  
		showChoice();
        cout<<endl<<"请输入选择字符 : ";
		cin>>choice; 
		
		switch(choice)
		{
			case 'a':
			case 'A':
				cout<<"\n\n*****************先来先服务算法*****************\n\n";  
				getInfo(a,n); 
            	sortArriveTime(a, n);   //按照到达时间先后排序
            	Fcfs(a,n,t1,t2);        //先来先服务算法  
				cout<<endl<<"平均周转时间为："<<t1 / n<<endl;  
				cout<<"平均带权周转时间为："<<t2 / n<<endl;
				break;
				
			case 'b':
			case 'B':
				cout<<"\n\n*****************短作业优先算法*****************\n\n";  
				getInfo(a,n);  
           		sortServeTime(a, n);    //按照服务时间短到长排序
           	    SPN(a,n,t1,t2);         //短作业优先算法  
           		cout<<endl<<"平均周转时间为："<<t1 / n<<endl;  
				cout<<"平均带权周转时间为："<<t2 / n<<endl;  
				break;
				
			case 'c':
			case 'C':
				cout<<"\n\n*****************时间片轮转算法*****************\n\n"; 
				getInfo(a,n);  
           		sortArriveTime(a, n);   //按照到达时间先后排序
				RR(a,n);
				break;
				
			case 'e':
			case 'E':
				exit(1);
				break;
			default:
				cout<<"输入有误！"<<endl;
				break;
		}
		cout<<endl;
    }  
    return 0;
}  