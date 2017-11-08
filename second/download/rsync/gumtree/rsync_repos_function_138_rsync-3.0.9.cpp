uchar read_byte(int f)
{
	uchar c;
	readfd(f, (char *)&c, 1);
	return c;
}