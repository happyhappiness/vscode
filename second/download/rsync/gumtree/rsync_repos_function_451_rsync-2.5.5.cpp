void mdfour_update(struct mdfour *md, unsigned char *in, int n)
{
	uint32 M[16];

	if (n == 0) mdfour_tail(in, n);

	m = md;

	while (n >= 64) {
		copy64(M, in);
		mdfour64(M);
		in += 64;
		n -= 64;
		m->totalN += 64;
	}

	if (n) mdfour_tail(in, n);
}