void write_longint(int f, int64 x)
{
	char b[8];

	if (x <= 0x7FFFFFFF) {
		write_int(f, (int)x);
		return;
	}

#if SIZEOF_INT64 < 8
	rprintf(FERROR, "Integer overflow: attempted 64-bit offset\n");
	exit_cleanup(RERR_UNSUPPORTED);
#else
	write_int(f, (int32)0xFFFFFFFF);
	SIVAL(b,0,(x&0xFFFFFFFF));
	SIVAL(b,4,((x>>32)&0xFFFFFFFF));

	writefd(f,b,8);
#endif
}