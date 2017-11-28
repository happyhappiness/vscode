static int
timeval_diff(const struct timeval *a, const struct timeval *b)
{
    return (b->tv_sec - a->tv_sec) * 1000000 + (b->tv_usec - a->tv_usec);
}