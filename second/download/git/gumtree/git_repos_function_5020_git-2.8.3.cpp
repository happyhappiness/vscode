static void hmac_sha1(unsigned char *out,
		      const char *key_in, size_t key_len,
		      const char *text, size_t text_len)
{
	unsigned char key[HMAC_BLOCK_SIZE];
	unsigned char k_ipad[HMAC_BLOCK_SIZE];
	unsigned char k_opad[HMAC_BLOCK_SIZE];
	int i;
	git_SHA_CTX ctx;

	/* RFC 2104 2. (1) */
	memset(key, '\0', HMAC_BLOCK_SIZE);
	if (HMAC_BLOCK_SIZE < key_len) {
		git_SHA1_Init(&ctx);
		git_SHA1_Update(&ctx, key_in, key_len);
		git_SHA1_Final(key, &ctx);
	} else {
		memcpy(key, key_in, key_len);
	}

	/* RFC 2104 2. (2) & (5) */
	for (i = 0; i < sizeof(key); i++) {
		k_ipad[i] = key[i] ^ 0x36;
		k_opad[i] = key[i] ^ 0x5c;
	}

	/* RFC 2104 2. (3) & (4) */
	git_SHA1_Init(&ctx);
	git_SHA1_Update(&ctx, k_ipad, sizeof(k_ipad));
	git_SHA1_Update(&ctx, text, text_len);
	git_SHA1_Final(out, &ctx);

	/* RFC 2104 2. (6) & (7) */
	git_SHA1_Init(&ctx);
	git_SHA1_Update(&ctx, k_opad, sizeof(k_opad));
	git_SHA1_Update(&ctx, out, 20);
	git_SHA1_Final(out, &ctx);
}