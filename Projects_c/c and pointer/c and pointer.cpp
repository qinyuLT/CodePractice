#include <stdio.h>

//5.3 value�Ķ�����ֵ���ҽ���һ�º��ֵ
unsigned int Reversr_bits(unsigned int value) 
{
	unsigned int tmp = 0;
	unsigned i;

	for(i=1;i!=0;i<<=1)//i��Ϊ0�ͽ��Ž��У�ѭ��������ֳ��޹أ��Ӷ������˿���ֲ��
	{
		tmp <<= 1;
		if(value & 1)
		{
			tmp |= 1;
		}
		value >>= 1;
	}
	return tmp;
}
int main()
{
	printf("%lld\n",Reversr_bits(25));
	printf("%08x\n",Reversr_bits(25));
	return 0;
}
