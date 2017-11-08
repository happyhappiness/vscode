static inline int ewah_bit_ctz64(uint64_t x)
{
	int n = 0;
	if ((x & 0xffffffff) == 0) { x >>= 32; n += 32; }
	if ((x &     0xffff) == 0) { x >>= 16; n += 16; }
	if ((x &       0xff) == 0) { x >>=  8; n +=  8; }
	if ((x &        0xf) == 0) { x >>=  4; n +=  4; }
	if ((x &        0x3) == 0) { x >>=  2; n +=  2; }
	if ((x &        0x1) == 0) { x >>=  1; n +=  1; }
	return n + !x;
}