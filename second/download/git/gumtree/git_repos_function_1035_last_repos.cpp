static inline void hashcpy(unsigned char *sha_dst, const unsigned char *sha_src)
{
	memcpy(sha_dst, sha_src, GIT_SHA1_RAWSZ);
}