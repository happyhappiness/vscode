static void flush_one_hunk(struct object_id *result, git_SHA_CTX *ctx)
{
	unsigned char hash[GIT_MAX_RAWSZ];
	unsigned short carry = 0;
	int i;

	git_SHA1_Final(hash, ctx);
	git_SHA1_Init(ctx);
	/* 20-byte sum, with carry */
	for (i = 0; i < GIT_SHA1_RAWSZ; ++i) {
		carry += result->hash[i] + hash[i];
		result->hash[i] = carry;
		carry >>= 8;
	}
}