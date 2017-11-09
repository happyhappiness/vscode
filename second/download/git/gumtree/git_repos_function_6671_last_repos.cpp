static inline uint64_t git_bswap64(uint64_t x)
{
	uint64_t result;
	if (__builtin_constant_p(x))
		result = default_bswap64(x);
	else
		__asm__("bswap %q0" : "=r" (result) : "0" (x));
	return result;
}