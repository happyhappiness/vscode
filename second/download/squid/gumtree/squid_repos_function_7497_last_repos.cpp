time_t getCurrentTime(void)
{
    struct timeval current_time;
#if GETTIMEOFDAY_NO_TZP
    gettimeofday(&current_time);
#else
    gettimeofday(&current_time, NULL);
#endif
    return current_time.tv_sec;
}