static unsigned msb(unsigned long val)
{
	unsigned r = 0;
	while (val >>= 1)
		r++;
	return r;
}