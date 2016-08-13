#include<stdio.h>  
#include<stdlib.h> 
#include<string.h> 
#include<assert.h>
#include<iostream>
#include<iomanip>
#include<queue>
//#include<windows.h>  //cls
using namespace std;

/*����ϵͳ���̵����㷨
	a.�����ȷ����㷨
	b.����ҵ�����㷨
	c.ʱ��Ƭ��ת�㷨  
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

////////////////////////////��������/////////////////////////////////
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
	cout<<"########## ���̵��� ###########"<<endl;
	cout<<"#      a.�����ȷ����㷨       #"<<endl;
	cout<<"#      b.����ҵ�����㷨       #"<<endl;
	cout<<"#      c.ʱ��Ƭ��ת�㷨       #"<<endl;
	cout<<"#      e.��  ��  ��  ��       #"<<endl;
	cout<<"###############################"<<endl;
} 

void getInfo(process_FCFS a[],int &n)
{
	cout<<"�������������";  
	cin>>n;
	cout<<"���������룺"<<n<<"��������  ����ʱ��  ����ʱ��"<<endl; 
    for(int i=0;i<n;i++)  
    {  
        cout<<i+1<<": ";
		cin>>a[i].name>>a[i].arrivetime>>a[i].servetime;  
		a[i].rest = a[i].servetime;//ʱ��Ƭ��ת�㷨�Ż��õ����渳ֵ 
		a[i].state = "ready";      //
	}  
}

//FcFs,SPN
void showProcessInfo(process_FCFS a[],int n,float &t1, float &t2)
{
	cout<<"������ "<<"����ʱ��  "<<"����ʱ��  "<<"���ʱ��  "<<"��תʱ�� "<<"��Ȩ��תʱ��"<<endl;
    for(int i=0;i<n;i++)  
    { 
        printf("%3c%10.2f%10.2f%10.2f%10.2f%10.2f\n",a[i].name,a[i].arrivetime,a[i].servetime,
												a[i].finishtime,a[i].roundtime,a[i].daiquantime); 
        t1 += a[i].roundtime;  
        t2 += a[i].daiquantime;  
    } 
}
  
//������ʱ�����ð������  
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
            if(a[i].arrivetime>a[j].arrivetime)    //����ʱ��
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
 
    return a;   //����������������   
}  
  
//������ʱ�����ð������  
process_FCFS *sortServeTime(process_FCFS a[],int n)  
{  
    int i,j;  
    process_FCFS t;    
    for(i=0;i<n;i++)  
    {  
        for(j=i+1;j<n;j++)  
        {  
            if(a[i].servetime>a[j].servetime)    //����ʱ��
            {  
                t=a[i];  
                a[i]=a[j];  
                a[j]=t;  
            }  
        }   
    }  
    return a;   //����������������  
}  

//�����ȷ����㷨  
void Fcfs(process_FCFS a[],int n,float &t1, float &t2)  
{  
	a[0].finishtime=a[0].arrivetime+a[0].servetime; //���ʱ��=����ʱ��-����ʱ��  
    a[0].roundtime=a[0].finishtime-a[0].arrivetime; //��תʱ��=���ʱ��-�ύʱ��  
    a[0].daiquantime=a[0].roundtime/a[0].servetime; //��Ȩʱ��=��תʱ��/����ʱ��  
    
    //showProcessInfo(a,n,t1,t2);
    
    for(int i=1;i<n;i++)  
    {  
        if(a[i].arrivetime<a[i-1].finishtime)    
        {  
            a[i].finishtime=a[i-1].finishtime+a[i].servetime;      
        }  
        else    //��һ����ҵ������ʱ�� δ�ﵽ ��ǰ���̵���ʱ��  
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
	for(i=0;i<n;++i)//Ѱ��û��ִ�еĽ��������ȵ���Ľ��� 
	{
		//cout<<flag[i]<<" ";
		if(flag[i]== 1 && a[procNumber].arrivetime > a[i].arrivetime)
		{
			procNumber = i;
		}
	}
	//cout<<endl;
	return procNumber;//�����ҵ��Ľ��̺� 
}


//����ҵ�����㷨  
void SPN(process_FCFS a[],int n,float &t1, float &t2)  
{   
	int i=0,number=0,j; 
	int *flag = (int*)malloc(sizeof(int)*n);//flag�����������n�������Ƿ��Ѿ���ִ�� 
	float time = 0;

	for(i=0;i<n;++i)
		flag[i]=1;       //��ʼ����ֵ1����ʾ��û��ִ�� 
		
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
			i = findSuitabllePro(a,flag,n);//Ѱ�Һ��ʵģ����Ѿ�����ģ�
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
   
	cout<<"������ʱ����С: "; 
	cin>>slice;

	queue<process_FCFS *> activeQue;
	activeQue.push(&an[i++]);

	while(!activeQue.empty())
	{
		p = activeQue.front();
		t = p;

		time += slice;
		temp = p->rest; 
        p->rest = p->rest - slice;    //ʣ��ʱ��
		p->state = "running";

		if(i < n)
			activeQue.push(&an[i++]);
		
		if(p->rest <= 0) //ʣ��ʱ��Ϊ0��ɾ��
		{
			time = time - slice + temp;          //�������ʱ��  
            p->roundtime = time - p->arrivetime;
            p->daiquantime = p->roundtime/(p->servetime);
            sum_zhouzhuan += p->roundtime;
            sum_daiquan += p->daiquantime;
            p->rest = 0; 
			
			cout<<"\n********************************************************************************\n";   

			cout<<"������ "<<"����ʱ��  "<<"����ʱ��  "<<"ʣ��ʱ�� "<<"����״̬ "<<"���ʱ��  "<<"��תʱ�� "<<"��Ȩ��תʱ��"<<endl;
			
			printf("%3c%10.2f%10.2f%10.2f%10s%",p->name,p->arrivetime,p->servetime,p->rest,p->state);  
            cout<<setw(8)<<time<<setw(10)<<p->roundtime<<setw(10)<<p->daiquantime<<endl;
		
			activeQue.pop();
		}
		if(p->rest > 0)//��ʣ��ʱ�䣬��������
		{
			r = activeQue.front();
			activeQue.pop();
			activeQue.push(r);
		}	
	} 
    cout<<"\n����תʱ�䣺 "<<sum_zhouzhuan;
    cout<<"\n�ܴ�Ȩ��תʱ�䣺 "<<sum_daiquan;
    cout<<"\nƽ����תʱ�䣺 "<<sum_zhouzhuan/n;
    cout<<"\nƽ����Ȩ��תʱ�䣺 "<<sum_daiquan/n<<endl;
}

int main()  
{  
    float t1 = 0.0f;       //����תʱ��  
    float t2 = 0.0f;       //�ܴ�Ȩ��תʱ��  
    int n;                 //n�����̸��� 
    char choice = ' ';     //ѡ���㷨������ʶ  

	while (choice != 'e' && choice != 'E')  //��Ϊ�˳���ʶ������ѭ��  
    {  
		showChoice();
        cout<<endl<<"������ѡ���ַ� : ";
		cin>>choice; 
		
		switch(choice)
		{
			case 'a':
			case 'A':
				cout<<"\n\n*****************�����ȷ����㷨*****************\n\n";  
				getInfo(a,n); 
            	sortArriveTime(a, n);   //���յ���ʱ���Ⱥ�����
            	Fcfs(a,n,t1,t2);        //�����ȷ����㷨  
				cout<<endl<<"ƽ����תʱ��Ϊ��"<<t1 / n<<endl;  
				cout<<"ƽ����Ȩ��תʱ��Ϊ��"<<t2 / n<<endl;
				break;
				
			case 'b':
			case 'B':
				cout<<"\n\n*****************����ҵ�����㷨*****************\n\n";  
				getInfo(a,n);  
           		sortServeTime(a, n);    //���շ���ʱ��̵�������
           	    SPN(a,n,t1,t2);         //����ҵ�����㷨  
           		cout<<endl<<"ƽ����תʱ��Ϊ��"<<t1 / n<<endl;  
				cout<<"ƽ����Ȩ��תʱ��Ϊ��"<<t2 / n<<endl;  
				break;
				
			case 'c':
			case 'C':
				cout<<"\n\n*****************ʱ��Ƭ��ת�㷨*****************\n\n"; 
				getInfo(a,n);  
           		sortArriveTime(a, n);   //���յ���ʱ���Ⱥ�����
				RR(a,n);
				break;
				
			case 'e':
			case 'E':
				exit(1);
				break;
			default:
				cout<<"��������"<<endl;
				break;
		}
		cout<<endl;
    }  
    return 0;
}  