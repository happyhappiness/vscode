void mdfour_update(md_context *md, const uchar *in, uint32 length)
{
	uint32 M[16];

	m = md;

	if (length == 0)
		mdfour_tail(in, length);

	while (length >= 64) {
		copy64(M, in);
		mdfour64(M);
		in += 64;
		length -= 64;
		m->totalN += 64 << 3;
		if (m->totalN < 64 << 3)
			m->totalN2++;
	}

	if (length)
		mdfour_tail(in, length);
}