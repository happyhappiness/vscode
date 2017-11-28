int
gettimeofday(struct timeval *pcur_time, void *tzp)
{
    struct _timeb current;
    struct timezone *tz = (struct timezone *) tzp;

    _ftime(&current);

    pcur_time->tv_sec = current.time;
    pcur_time->tv_usec = current.millitm * 1000L;
    if (tz) {
        tz->tz_minuteswest = current.timezone; /* minutes west of Greenwich  */
        tz->tz_dsttime = current.dstflag;      /* type of dst correction  */
    }
    return 0;
}