void mdfour_update(struct mdfour *md, unsigned char *in, uint32 n)
{
	uint32 M[16];

	m = md;

	if (n == 0) mdfour_tail(in, n);

	while (n >= 64) {
		copy64(M, in);
		mdfour64(M);
		in += 64;
		n -= 64;
		m->totalN += 64 << 3;
		if (m->totalN < 64 << 3) {
			m->totalN2++;
		}
	}

	if (n) mdfour_tail(in, n);
}