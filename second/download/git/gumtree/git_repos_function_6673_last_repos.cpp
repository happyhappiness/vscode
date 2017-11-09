static inline uint16_t get_be16(const void *ptr)
{
	const unsigned char *p = ptr;
	return	(uint16_t)p[0] << 8 |
		(uint16_t)p[1] << 0;
}