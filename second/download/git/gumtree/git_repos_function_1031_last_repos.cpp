static inline int hashcmp(const unsigned char *sha1, const unsigned char *sha2)
{
	return memcmp(sha1, sha2, GIT_SHA1_RAWSZ);
}