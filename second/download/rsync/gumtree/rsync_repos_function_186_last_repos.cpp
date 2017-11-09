int32 read_ndx(int f)
{
	static int32 prev_positive = -1, prev_negative = 1;
	int32 *prev_ptr, num;
	char b[4];

	if (protocol_version < 30)
		return read_int(f);

	read_buf(f, b, 1);
	if (CVAL(b, 0) == 0xFF) {
		read_buf(f, b, 1);
		prev_ptr = &prev_negative;
	} else if (CVAL(b, 0) == 0)
		return NDX_DONE;
	else
		prev_ptr = &prev_positive;
	if (CVAL(b, 0) == 0xFE) {
		read_buf(f, b, 2);
		if (CVAL(b, 0) & 0x80) {
			b[3] = CVAL(b, 0) & ~0x80;
			b[0] = b[1];
			read_buf(f, b+1, 2);
			num = IVAL(b, 0);
		} else
			num = (UVAL(b,0)<<8) + UVAL(b,1) + *prev_ptr;
	} else
		num = UVAL(b, 0) + *prev_ptr;
	*prev_ptr = num;
	if (prev_ptr == &prev_negative)
		num = -num;
	return num;
}