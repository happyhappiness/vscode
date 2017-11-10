static inline void mput_char(char c, unsigned int num)
{
	while(num--)
		putchar(c);
}