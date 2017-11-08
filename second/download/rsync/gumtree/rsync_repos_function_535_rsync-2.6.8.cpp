static void mdfour_tail(unsigned char *in, uint32 n)
{
	unsigned char buf[128];
	uint32 M[16];
	extern int protocol_version;

	/*
	 * Count total number of bits, modulo 2^64
	 */
	m->totalN += n << 3;
	if (m->totalN < (n << 3)) {
		m->totalN2++;
	}
	m->totalN2 += n >> 29;

	memset(buf, 0, 128);
	if (n) memcpy(buf, in, n);
	buf[n] = 0x80;

	if (n <= 55) {
		copy4(buf+56, m->totalN);
		/*
		 * Prior to protocol version 27 only the number of bits
		 * modulo 2^32 was included.  MD4 requires the number
		 * of bits modulo 2^64, which was fixed starting with
		 * protocol version 27.
		 */
		if (protocol_version >= 27) {
			copy4(buf+60, m->totalN2);
		}
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
		if (protocol_version >= 27) {
			copy4(buf+124, m->totalN2); 
		}
		copy64(M, buf);
		mdfour64(M);
		copy64(M, buf+64);
		mdfour64(M);
	}
}