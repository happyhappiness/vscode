unsigned int memhash(const void *buf, size_t len)
{
	unsigned int hash = FNV32_BASE;
	unsigned char *ucbuf = (unsigned char *) buf;
	while (len--) {
		unsigned int c = *ucbuf++;
		hash = (hash * FNV32_PRIME) ^ c;
	}
	return hash;
}