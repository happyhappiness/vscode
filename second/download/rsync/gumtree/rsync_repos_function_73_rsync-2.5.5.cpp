unsigned char read_byte(int f)
{
	unsigned char c;
	read_buf (f, (char *)&c, 1);
	return c;
}