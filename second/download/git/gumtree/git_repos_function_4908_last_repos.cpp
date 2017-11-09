static inline uint32_t ewah_bit_popcount64(uint64_t x)
{
	x = (x & 0x5555555555555555ULL) + ((x >>  1) & 0x5555555555555555ULL);
	x = (x & 0x3333333333333333ULL) + ((x >>  2) & 0x3333333333333333ULL);
	x = (x & 0x0F0F0F0F0F0F0F0FULL) + ((x >>  4) & 0x0F0F0F0F0F0F0F0FULL);
	return (x * 0x0101010101010101ULL) >> 56;
}