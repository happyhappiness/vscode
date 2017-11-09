unsigned int memihash_cont(unsigned int hash_seed, const void *buf, size_t len)
{
	unsigned int hash = hash_seed;
	unsigned char *ucbuf = (unsigned char *) buf;
	while (len--) {
		unsigned int c = *ucbuf++;
		if (c >= 'a' && c <= 'z')
			c -= 'a' - 'A';
		hash = (hash * FNV32_PRIME) ^ c;
	}
	return hash;
}