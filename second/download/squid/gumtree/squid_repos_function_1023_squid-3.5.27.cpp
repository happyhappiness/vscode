static const char *
debugLogTime(void)
{

    time_t t = getCurrentTime();

    struct tm *tm;
    static char buf[128];
    static time_t last_t = 0;

    if (Debug::Level() > 1) {
        char buf2[128];
        tm = localtime(&t);
        strftime(buf2, 127, "%Y/%m/%d %H:%M:%S", tm);
        buf2[127] = '\0';
        snprintf(buf, 127, "%s.%03d", buf2, (int) current_time.tv_usec / 1000);
        last_t = t;
    } else if (t != last_t) {
        tm = localtime(&t);
        strftime(buf, 127, "%Y/%m/%d %H:%M:%S", tm);
        last_t = t;
    }

    buf[127] = '\0';
    return buf;
}