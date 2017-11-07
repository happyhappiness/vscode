static inline unsigned int hash_sha1(const unsigned char *sha1)
{
	unsigned int hash;
	memcpy(&hash, sha1, sizeof(hash));
	return hash;
}