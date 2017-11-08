static void mdfour_tail(unsigned char *in, int n)
{
	unsigned char buf[128];
	uint32 M[16];
	uint32 b;

	m->totalN += n;

	b = m->totalN * 8;

	memset(buf, 0, 128);
	if (n) memcpy(buf, in, n);
	buf[n] = 0x80;

	if (n <= 55) {
		copy4(buf+56, b);
		copy64(M, buf);
		mdfour64(M);
	} else {
		copy4(buf+120, b); 
		copy64(M, buf);
		mdfour64(M);
		copy64(M, buf+64);
		mdfour64(M);
	}
}