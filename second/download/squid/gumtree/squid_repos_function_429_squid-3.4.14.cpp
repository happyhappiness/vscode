static int
time_since(const struct timeval *when)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return timeval_diff(when, &now);
}