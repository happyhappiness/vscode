void write_shortint(int f, unsigned short x)
{
	char b[2];
	b[0] = (char)x;
	b[1] = (char)(x >> 8);
	write_buf(f, b, 2);
}