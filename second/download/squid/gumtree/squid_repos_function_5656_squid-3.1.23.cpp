const char *
mkhttpdlogtime(const time_t * t)
{
    static char buf[128];

    struct tm *gmt = gmtime(t);

#ifndef USE_GMT
    int gmt_min, gmt_hour, gmt_yday, day_offset;
    size_t len;
    struct tm *lt;
    int min_offset;

    /* localtime & gmtime may use the same static data */
    gmt_min = gmt->tm_min;
    gmt_hour = gmt->tm_hour;
    gmt_yday = gmt->tm_yday;

    lt = localtime(t);

    day_offset = lt->tm_yday - gmt_yday;
    /* wrap round on end of year */
    if (day_offset > 1)
        day_offset = -1;
    else if (day_offset < -1)
        day_offset = 1;

    min_offset = day_offset * 1440 + (lt->tm_hour - gmt_hour) * 60
                 + (lt->tm_min - gmt_min);

    len = strftime(buf, 127 - 5, "%d/%b/%Y:%H:%M:%S ", lt);
    snprintf(buf + len, 128 - len, "%+03d%02d",
             (min_offset / 60) % 24,
             min_offset % 60);
#else /* USE_GMT */
    buf[0] = '\0';
    strftime(buf, 127, "%d/%b/%Y:%H:%M:%S -000", gmt);
#endif /* USE_GMT */

    return buf;
}