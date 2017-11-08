int32 read_int(int f)
{
	char b[4];
	readfd(f,b,4);
	return IVAL(b,0);
}