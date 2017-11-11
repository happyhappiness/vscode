unsigned short read_shortint(int f)
{
	char b[2];
	read_buf(f, b, 2);
	return (UVAL(b, 1) << 8) + UVAL(b, 0);
}