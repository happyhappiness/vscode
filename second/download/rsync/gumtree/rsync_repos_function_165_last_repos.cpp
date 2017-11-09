int64 read_varlong(int f, uchar min_bytes)
{
	union {
		char b[9];
		int64 x;
	} u;
	char b2[8];
	int extra;

#if SIZEOF_INT64 < 8
	memset(u.b, 0, 8);
#else
	u.x = 0;
#endif
	read_buf(f, b2, min_bytes);
	memcpy(u.b, b2+1, min_bytes-1);
	extra = int_byte_extra[CVAL(b2, 0) / 4];
	if (extra) {
		uchar bit = ((uchar)1<<(8-extra));
		if (min_bytes + extra > (int)sizeof u.b) {
			rprintf(FERROR, "Overflow in read_varlong()\n");
			exit_cleanup(RERR_STREAMIO);
		}
		read_buf(f, u.b + min_bytes - 1, extra);
		u.b[min_bytes + extra - 1] = CVAL(b2, 0) & (bit-1);
#if SIZEOF_INT64 < 8
		if (min_bytes + extra > 5 || u.b[4] || CVAL(u.b,3) & 0x80) {
			rprintf(FERROR, "Integer overflow: attempted 64-bit offset\n");
			exit_cleanup(RERR_UNSUPPORTED);
		}
#endif
	} else
		u.b[min_bytes + extra - 1] = CVAL(b2, 0);
#if SIZEOF_INT64 < 8
	u.x = IVAL(u.b,0);
#elif CAREFUL_ALIGNMENT
	u.x = IVAL64(u.b,0);
#endif
	return u.x;
}