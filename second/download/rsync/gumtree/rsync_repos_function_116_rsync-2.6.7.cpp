void write_shortint(int f, int x)
{
	uchar b[2];
	b[0] = x;
	b[1] = x >> 8;
	writefd(f, (char *)b, 2);
}