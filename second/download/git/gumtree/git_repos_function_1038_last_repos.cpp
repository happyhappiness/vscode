static inline void hashclr(unsigned char *hash)
{
	memset(hash, 0, GIT_SHA1_RAWSZ);
}