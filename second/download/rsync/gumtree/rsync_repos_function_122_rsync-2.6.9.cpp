void write_byte(int f, uchar c)
{
	writefd(f, (char *)&c, 1);
}