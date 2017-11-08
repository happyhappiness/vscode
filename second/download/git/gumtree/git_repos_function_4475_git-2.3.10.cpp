static void flush_one_hunk(unsigned char *result, git_SHA_CTX *ctx)
{
	unsigned char hash[20];
	unsigned short carry = 0;
	int i;

	git_SHA1_Final(hash, ctx);
	git_SHA1_Init(ctx);
	/* 20-byte sum, with carry */
	for (i = 0; i < 20; ++i) {
		carry += result[i] + hash[i];
		result[i] = carry;
		carry >>= 8;
	}
}