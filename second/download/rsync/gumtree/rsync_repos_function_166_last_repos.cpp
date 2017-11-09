int64 read_longint(int f)
{
#if SIZEOF_INT64 >= 8
	char b[9];
#endif
	int32 num = read_int(f);

	if (num != (int32)0xffffffff)
		return num;

#if SIZEOF_INT64 < 8
	rprintf(FERROR, "Integer overflow: attempted 64-bit offset\n");
	exit_cleanup(RERR_UNSUPPORTED);
#else
	read_buf(f, b, 8);
	return IVAL(b,0) | (((int64)IVAL(b,4))<<32);
#endif
}