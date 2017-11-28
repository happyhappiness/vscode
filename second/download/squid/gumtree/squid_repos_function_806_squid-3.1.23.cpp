time_t
getCurrentTime(void)
{
#if GETTIMEOFDAY_NO_TZP
    gettimeofday(&current_time);
#else

    gettimeofday(&current_time, NULL);
#endif

    current_dtime = (double) current_time.tv_sec +
                    (double) current_time.tv_usec / 1000000.0;
    return squid_curtime = current_time.tv_sec;
}