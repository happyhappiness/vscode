int read_shortint(int f)
{
	uchar b[2];
	readfd(f, (char *)b, 2);
	return (b[1] << 8) + b[0];
}