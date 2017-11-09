uint64_t getnanotime(void)
{
	static uint64_t offset;
	if (offset > 1) {
		/* initialization succeeded, return offset + high res time */
		return offset + highres_nanos();
	} else if (offset == 1) {
		/* initialization failed, fall back to gettimeofday */
		return gettimeofday_nanos();
	} else {
		/* initialize offset if high resolution timer works */
		uint64_t now = gettimeofday_nanos();
		uint64_t highres = highres_nanos();
		if (highres)
			offset = now - highres;
		else
			offset = 1;
		return now;
	}
}