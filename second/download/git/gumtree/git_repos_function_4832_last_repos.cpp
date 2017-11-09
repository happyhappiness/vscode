long xdl_bogosqrt(long n) {
	long i;

	/*
	 * Classical integer square root approximation using shifts.
	 */
	for (i = 1; n > 0; n >>= 2)
		i <<= 1;

	return i;
}