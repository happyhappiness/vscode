static inline uint64_t gettimeofday_nanos(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (uint64_t) tv.tv_sec * 1000000000 + tv.tv_usec * 1000;
}