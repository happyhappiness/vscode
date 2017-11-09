int32 read_int(int f)
{
	char b[4];
	int32 num;

	read_buf(f, b, 4);
	num = IVAL(b, 0);
#if SIZEOF_INT32 > 4
	if (num & (int32)0x80000000)
		num |= ~(int32)0xffffffff;
#endif
	return num;
}