#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>


//5.3��������valueֵ�Ķ��������ú��ֵ
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


//4.7��ȥ�ַ����ж���Ŀո�,�����ַ�֮�����һ���ո�
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

//4.6��src��start���ַ�����len���ַ������Ƶ�des֮��
char *Substr(char *des,const char *src,int start,int len)
{
	int n = 1;   //n����Ѱ��start��start��1��ʼ��
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
		if(*src == '\0') //���src��startΪ�գ�ֱ�ӷ���
		{
			return des;
		}
		n++;
		src++;
	}

	while(len)     //��len��Ϊ0��һ��һ������
	{
		*des++ = *src++;
		len--;
	}

	*des++ = '\0'; //des���һ������

	return des;
}

//4.1�����ù�ʽa(i+1)=(a(i)+(n/a(i)))/2,��n��ƽ����,����ʼֵΪ1
float SquareRoot(unsigned int n)
{
	float oldRoot =  0;                                                                             /*  ��һ�εõ��ĸ�                 */
	float newRoot = 1;                                                                             /*  ���µõ��ĸ�                    */
	                                                                                                           /*  ����ֵ�Ĳ��Ѿ���             */
	while((oldRoot-newRoot>0.0000001) ||
		     (oldRoot-newRoot)<-0.00000001)                                          /*  float��������Ϊ���ѵõ�   */
	{
		oldRoot = newRoot;
		newRoot = (newRoot + n/newRoot)/2;
	}

	return newRoot;
}

/*
//2.���һ���ļ��д������Ƿ�ƥ��
int CheckBraceMatching(const char *path)
{
	char ch;
	int total = 0;  //��¼������Ŀ
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

//1.2�ӱ�׼�����ȡ���У�ÿ�д�ӡ����׼����ϣ�ǰ��Ҫ�����к�
//    �������еĳ���û�����ƣ�����һ������q��Q��ʾ�˳�����
void PrintTxt()
{
	int line = 1; //�к�
	int flg = 1;  //�Ƿ�Ϊ��ͷ
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


//1.3 ���ӱ�׼��ȡһЩ�ַ�����д����׼����ϣ�����������
int CheckSum()
{
	int ch;                            /*  ����ÿ�λ�ȡ���ַ�ֵ       */
	signed char sum = -1;               /*  ���и����ĳ�ʼֵ-1          */
	while((ch=getchar()) != '\n')
	{
		sum += ch;
		printf("%c",ch);
	}
	sum += '\n';                       /*  ���е�ʾ��Ҫ�����  */
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
	char *path = "E:\\ѧϰ����\\���\\C��ָ��\\C��ָ�������\\test11.cpp";
	int val = CheckBraceMatching(path);
	if(val == 0)
	{
		printf("����ƥ��\n");
	}
	if(val > 0)
	{
		printf("������>������\n");
	}
	if(val < 0)
	{
		printf("������<������\n");
	}
	*/

	return 0;
}