int ppc_SHA1_Final(unsigned char *hash, ppc_SHA_CTX *c)
{
	unsigned int cnt = c->cnt;

	c->buf.b[cnt++] = 0x80;
	if (cnt > 56) {
		if (cnt < 64)
			memset(&c->buf.b[cnt], 0, 64 - cnt);
		ppc_sha1_core(c->hash, c->buf.b, 1);
		cnt = 0;
	}
	if (cnt < 56)
		memset(&c->buf.b[cnt], 0, 56 - cnt);
	c->buf.l[7] = c->len;
	ppc_sha1_core(c->hash, c->buf.b, 1);
	memcpy(hash, c->hash, 20);
	return 0;
}