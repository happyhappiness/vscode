static inline void *xalloc_flex(size_t base_len, size_t offset,
				const void *src, size_t src_len)
{
	unsigned char *ret = xcalloc(1, st_add3(base_len, src_len, 1));
	memcpy(ret + offset, src, src_len);
	return ret;
}