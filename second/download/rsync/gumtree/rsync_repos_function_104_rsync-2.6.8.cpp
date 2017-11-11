int64 read_longint(int f)
{
	int64 num;
	char b[8];
	num = read_int(f);

	if ((int32)num != (int32)0xffffffff)
		return num;

#if SIZEOF_INT64 < 8
	rprintf(FERROR, "Integer overflow: attempted 64-bit offset\n");
	exit_cleanup(RERR_UNSUPPORTED);
#else
	readfd(f,b,8);
	num = IVAL(b,0) | (((int64)IVAL(b,4))<<32);
#endif

	return num;
}