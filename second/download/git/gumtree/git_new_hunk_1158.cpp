#endif

#ifdef DOSTORESTATE79
SHA1_RECOMPRESS(79)
#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif

static void sha1_recompression_step(uint32_t step, uint32_t ihvin[5], uint32_t ihvout[5], const uint32_t me2[80], const uint32_t state[5])
{
	switch (step)
	{
#ifdef DOSTORESTATE0
	case 0:
