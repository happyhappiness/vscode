static _Bool timeout_reached(struct timespec timeout)
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return (now.tv_sec >= timeout.tv_sec && now.tv_usec >= (timeout.tv_nsec / 1000));
}