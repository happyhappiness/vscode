static unsigned int hash_obj(const unsigned char *sha1, unsigned int n)
{
	unsigned int hash;

	/*
	 * Since the sha1 is essentially random, we just take the
	 * required number of bits directly from the first
	 * sizeof(unsigned int) bytes of sha1.  First we have to copy
	 * the bytes into a properly aligned integer.  If we cared
	 * about getting consistent results across architectures, we
	 * would have to call ntohl() here, too.
	 */
	memcpy(&hash, sha1, sizeof(unsigned int));
	return hash & (n - 1);
}