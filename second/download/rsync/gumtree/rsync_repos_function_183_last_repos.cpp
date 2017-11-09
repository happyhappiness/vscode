void write_byte(int f, uchar c)
{
	write_buf(f, (char *)&c, 1);
}