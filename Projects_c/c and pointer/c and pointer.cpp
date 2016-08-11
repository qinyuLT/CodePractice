#include <stdio.h>

//5.3 value的二进制值左右交换一下后的值
unsigned int Reversr_bits(unsigned int value) 
{
	unsigned int tmp = 0;
	unsigned i;

	for(i=1;i!=0;i<<=1)//i不为0就接着进行，循环与机器字长无关，从而避免了可移植性
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
