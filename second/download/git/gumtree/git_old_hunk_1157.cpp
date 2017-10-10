	if (t <= 77) HASHCLASH_SHA1COMPRESS_ROUND4_STEP(d, e, a, b, c, me2, 77); \
	if (t <= 78) HASHCLASH_SHA1COMPRESS_ROUND4_STEP(c, d, e, a, b, me2, 78); \
	if (t <= 79) HASHCLASH_SHA1COMPRESS_ROUND4_STEP(b, c, d, e, a, me2, 79); \
	ihvout[0] = ihvin[0] + a; ihvout[1] = ihvin[1] + b; ihvout[2] = ihvin[2] + c; ihvout[3] = ihvin[3] + d; ihvout[4] = ihvin[4] + e; \
}

#ifdef DOSTORESTATE0
SHA1_RECOMPRESS(0)
#endif

#ifdef DOSTORESTATE1
SHA1_RECOMPRESS(1)
