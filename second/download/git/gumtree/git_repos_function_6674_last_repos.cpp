static inline uint32_t get_be32(const void *ptr)
{
	const unsigned char *p = ptr;
	return	(uint32_t)p[0] << 24 |
		(uint32_t)p[1] << 16 |
		(uint32_t)p[2] <<  8 |
		(uint32_t)p[3] <<  0;
}