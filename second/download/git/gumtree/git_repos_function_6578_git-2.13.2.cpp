static inline uint64_t git_bswap64(uint64_t x)
{
	union { uint64_t i64; uint32_t i32[2]; } tmp, result;
	if (__builtin_constant_p(x))
		result.i64 = default_bswap64(x);
	else {
		tmp.i64 = x;
		result.i32[0] = git_bswap32(tmp.i32[1]);
		result.i32[1] = git_bswap32(tmp.i32[0]);
	}
	return result.i64;
}