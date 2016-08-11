#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>


//5.3函数返回value值的二进制逆置后的值
unsigned int Reverse_Bits(unsigned int value)
{
	unsigned int answer = 0;
	unsigned int i = 1;

	for(;i != 0;i<<=1)
	{
		answer <<= 1;
		if(value&1)
		{
			answer |= 1;
		}
		
		value >>= 1;
	}

	return answer;
}


//4.7移去字符串中多余的空格,两个字符之间最多一个空格
char *Delblank(char *des,char *str)
{
	while(*str != '\0')
	{
		if(*str == ' ')
		{
			*des++ = *str++;
			while(*str == ' ')
			{
				str++;
			}
		}
		*des++ = *str++;
	}
	*des++ = '\0';
	return des;
}

//4.6把src第start个字符起后的len个字符，复制到des之后
char *Substr(char *des,const char *src,int start,int len)
{
	int n = 1;   //n用于寻找start（start从1开始）
	if(start<0 || len<0)
	{
		return des;
	}
	while(*des != '\0') 
	{
		des++;
	}

	while(n != start)
	{
		if(*src == '\0') //如果src第start为空，直接返回
		{
			return des;
		}
		n++;
		src++;
	}

	while(len)     //当len不为0，一个一个复制
	{
		*des++ = *src++;
		len--;
	}

	*des++ = '\0'; //des最后一个赋空

	return des;
}

//4.1，利用公式a(i+1)=(a(i)+(n/a(i)))/2,求n的平方根,根初始值为1
float SquareRoot(unsigned int n)
{
	float oldRoot =  0;                                                                             /*  上一次得到的根                 */
	float newRoot = 1;                                                                             /*  最新得到的根                    */
	                                                                                                           /*  两次值的差已经在             */
	while((oldRoot-newRoot>0.0000001) ||
		     (oldRoot-newRoot)<-0.00000001)                                          /*  float精度内认为根已得到   */
	{
		oldRoot = newRoot;
		newRoot = (newRoot + n/newRoot)/2;
	}

	return newRoot;
}

/*
//2.检查一个文件中大括号是否匹配
int CheckBraceMatching(const char *path)
{
	char ch;
	int total = 0;  //记录括号数目
	FILE *fr = fopen(path,"r");
	assert(fr != NULL);

	while( fread(&ch,sizeof(char),1,fr) )
	{
		if(ch == '{')
		{
			total++;
		}
		else if(ch == '}')
		{
			total--;
		}
		if(total < 0)         
		{
			return total;
		}
	}
	fclose(fr);

	return total;
}
*/

//1.2从标准输入读取几行，每行打印到标准输出上，前面要加上行号
//    对输入行的长度没有限制，（第一列输入q或Q表示退出程序）
void PrintTxt()
{
	int line = 1; //行号
	int flg = 1;  //是否为开头
	char ch;

	while((ch = getchar()) != 'EOF')
	{
		if(flg == 1)
		{
			if(ch == 'q' || ch == 'Q')
			{
				return;
			}
			printf("%d ",line++);
			flg = 0;
		}
		if('\n' == ch)
		{
			flg = 1;
		}
		putchar(ch);
	}
}


//1.3 ，从标准读取一些字符，回写到标准输出上，并计算检验和
int CheckSum()
{
	int ch;                            /*  保存每次获取的字符值       */
	signed char sum = -1;               /*  题中给定的初始值-1          */
	while((ch=getchar()) != '\n')
	{
		sum += ch;
		printf("%c",ch);
	}
	sum += '\n';                       /*  题中的示例要加这个  */
	printf("\n%d\n",sum);                      
	return sum;
}

void Show(char str[],int len)
{
	for(int i=0;i<len;++i)
	{
		if(str[i] == '\0')
		{
			break;
		}
		printf("%c",str[i]);
	}
	printf("\n");
}

int main()
{
	printf("%d\n",Reverse_Bits(25));

	/*
	char des[100];
	char *str = "H   e   l   l   o   w   o   r l   d    !";
	Delblank(des,str);
	Show(des,100);
	*/

	/*
	char des[100] = "abcdefg";
	char src[20] = "hijklmn";
	Substr(des,src,1,7);
	//Substr(des,src,1,-7);
	//Substr(des,src,-1,7);
	//Substr(des,src,7,7);
	//Substr(des,src,8,7);
	Show(des,100);
	*/

	//printf("%f\n",SquareRoot(4));
	//printf("%f\n",SquareRoot(5));
	//printf("%f\n",SquareRoot(9));
	//printf("%f\n",SquareRoot(0));
	//printf("%f\n",SquareRoot(-5));

	//PrintTxt();
	//CheckSum();

	/*
	char *path = "E:\\学习资料\\暑假\\C和指针\\C和指针编程题答案\\test11.cpp";
	int val = CheckBraceMatching(path);
	if(val == 0)
	{
		printf("括号匹配\n");
	}
	if(val > 0)
	{
		printf("左括号>右括号\n");
	}
	if(val < 0)
	{
		printf("左括号<右括号\n");
	}
	*/

	return 0;
}