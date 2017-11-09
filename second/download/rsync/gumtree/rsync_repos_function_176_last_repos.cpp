void write_int(int f, int32 x)
{
	char b[4];
	SIVAL(b, 0, x);
	write_buf(f, b, 4);
}