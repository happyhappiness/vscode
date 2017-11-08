int32 read_int(int f)
{
	char b[4];
	int32 num;

	readfd(f,b,4);
	num = IVAL(b,0);
	if (num == (int32)0xffffffff)
		return -1;
	return num;
}