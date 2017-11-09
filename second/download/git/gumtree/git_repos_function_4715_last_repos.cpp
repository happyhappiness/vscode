static inline uint64_t highres_nanos(void)
{
	struct timespec ts;
	if (clock_gettime(CLOCK_MONOTONIC, &ts))
		return 0;
	return (uint64_t) ts.tv_sec * 1000000000 + ts.tv_nsec;
}