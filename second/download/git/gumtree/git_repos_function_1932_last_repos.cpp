static inline void copy_array(void *dst, const void *src, size_t n, size_t size)
{
	if (n)
		memcpy(dst, src, st_mult(size, n));
}