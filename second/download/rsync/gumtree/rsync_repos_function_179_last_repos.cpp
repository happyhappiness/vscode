void write_longint(int f, int64 x)
{
	char b[12], * const s = b+4;

	SIVAL(s, 0, x);
	if (x <= 0x7FFFFFFF && x >= 0) {
		write_buf(f, s, 4);
		return;
	}

#if SIZEOF_INT64 < 8
	rprintf(FERROR, "Integer overflow: attempted 64-bit offset\n");
	exit_cleanup(RERR_UNSUPPORTED);
#else
	memset(b, 0xFF, 4);
	SIVAL(s, 4, x >> 32);
	write_buf(f, b, 12);
#endif
}