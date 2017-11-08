static inline unsigned char *git_CC_HMAC(CCHmacAlgorithm alg,
		const void *key, int key_len,
		const unsigned char *data, size_t data_len,
		unsigned char *md, unsigned int *md_len)
{
	CCHmac(alg, key, key_len, data, data_len, md);
	return md;
}