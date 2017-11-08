static uint32_t clamp32(uintmax_t n)
{
	const uintmax_t max = 0xffffffff;
	return (n < max) ? n : max;
}