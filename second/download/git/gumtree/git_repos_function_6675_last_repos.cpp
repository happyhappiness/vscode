static inline void put_be32(void *ptr, uint32_t value)
{
	unsigned char *p = ptr;
	p[0] = value >> 24;
	p[1] = value >> 16;
	p[2] = value >>  8;
	p[3] = value >>  0;
}