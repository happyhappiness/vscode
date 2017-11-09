uchar read_byte(int f)
{
	uchar c;
	read_buf(f, (char*)&c, 1);
	return c;
}