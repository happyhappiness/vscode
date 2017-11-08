int ppc_SHA1_Init(ppc_SHA_CTX *c)
{
	c->hash[0] = 0x67452301;
	c->hash[1] = 0xEFCDAB89;
	c->hash[2] = 0x98BADCFE;
	c->hash[3] = 0x10325476;
	c->hash[4] = 0xC3D2E1F0;
	c->len = 0;
	c->cnt = 0;
	return 0;
}