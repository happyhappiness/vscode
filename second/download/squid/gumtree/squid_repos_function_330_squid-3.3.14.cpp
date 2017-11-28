static const char *
LogTime()
{
    struct timeval now;
    static time_t last_t = 0;
    static char buf[128];

    gettimeofday(&now, NULL);
    if (now.tv_sec != last_t) {
        time_t *tmp = (time_t *) & now.tv_sec;
        struct tm *tm = localtime(tmp);
        strftime(buf, 127, "%Y/%m/%d %H:%M:%S", tm);
        last_t = now.tv_sec;
    }
    return buf;
}