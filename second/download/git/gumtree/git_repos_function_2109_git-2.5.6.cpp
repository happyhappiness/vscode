static inline unsigned int sha1hash(const unsigned char *sha1)
{
	/*
	 * Equivalent to 'return *(unsigned int *)sha1;', but safe on
	 * platforms that don't support unaligned reads.
	 */
	unsigned int hash;
	memcpy(&hash, sha1, sizeof(hash));
	return hash;
}