static void mdfour_tail(const uchar *in, uint32 length)
{
	uchar buf[128];
	uint32 M[16];
	extern int protocol_version;

	/*
	 * Count total number of bits, modulo 2^64
	 */
	m->totalN += length << 3;
	if (m->totalN < (length << 3))
		m->totalN2++;
	m->totalN2 += length >> 29;

	memset(buf, 0, 128);
	if (length)
		memcpy(buf, in, length);
	buf[length] = 0x80;

	if (length <= 55) {
		copy4(buf+56, m->totalN);
		/*
		 * Prior to protocol version 27 only the number of bits
		 * modulo 2^32 was included.  MD4 requires the number
		 * of bits modulo 2^64, which was fixed starting with
		 * protocol version 27.
		 */
		if (protocol_version >= 27)
			copy4(buf+60, m->totalN2);
		copy64(M, buf);
		mdfour64(M);
	} else {
		copy4(buf+120, m->totalN); 
		/*
		 * Prior to protocol version 27 only the number of bits
		 * modulo 2^32 was included.  MD4 requires the number
		 * of bits modulo 2^64, which was fixed starting with
		 * protocol version 27.
		 */
		if (protocol_version >= 27)
			copy4(buf+124, m->totalN2); 
		copy64(M, buf);
		mdfour64(M);
		copy64(M, buf+64);
		mdfour64(M);
	}
}