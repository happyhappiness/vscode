int32 read_varint(int f)
{
	union {
		char b[5];
		int32 x;
	} u;
	uchar ch;
	int extra;

	u.x = 0;
	ch = read_byte(f);
	extra = int_byte_extra[ch / 4];
	if (extra) {
		uchar bit = ((uchar)1<<(8-extra));
		if (extra >= (int)sizeof u.b) {
			rprintf(FERROR, "Overflow in read_varint()\n");
			exit_cleanup(RERR_STREAMIO);
		}
		read_buf(f, u.b, extra);
		u.b[extra] = ch & (bit-1);
	} else
		u.b[0] = ch;
#if CAREFUL_ALIGNMENT
	u.x = IVAL(u.b,0);
#endif
#if SIZEOF_INT32 > 4
	if (u.x & (int32)0x80000000)
		u.x |= ~(int32)0xffffffff;
#endif
	return u.x;
}