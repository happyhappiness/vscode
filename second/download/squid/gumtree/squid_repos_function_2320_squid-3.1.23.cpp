const char *
accessLogTime(time_t t)
{

    struct tm *tm;
    static char buf[128];
    static time_t last_t = 0;

    if (t != last_t) {
        tm = localtime(&t);
        strftime(buf, 127, "%Y/%m/%d %H:%M:%S", tm);
        last_t = t;
    }

    return buf;
}