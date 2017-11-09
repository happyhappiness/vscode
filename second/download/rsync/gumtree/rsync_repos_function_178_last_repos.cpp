void write_varlong(int f, int64 x, uchar min_bytes)
{
	char b[9];
	uchar bit;
	int cnt = 8;

#if SIZEOF_INT64 >= 8
	SIVAL64(b, 1, x);
#else
	SIVAL(b, 1, x);
	if (x <= 0x7FFFFFFF && x >= 0)
		memset(b + 5, 0, 4);
	else {
		rprintf(FERROR, "Integer overflow: attempted 64-bit offset\n");
		exit_cleanup(RERR_UNSUPPORTED);
	}
#endif

	while (cnt > min_bytes && b[cnt] == 0)
		cnt--;
	bit = ((uchar)1<<(7-cnt+min_bytes));
	if (CVAL(b, cnt) >= bit) {
		cnt++;
		*b = ~(bit-1);
	} else if (cnt > min_bytes)
		*b = b[cnt] | ~(bit*2-1);
	else
		*b = b[cnt];

	write_buf(f, b, cnt);
}