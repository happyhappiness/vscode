static int
tmSaneValues(struct tm *tm)
{
    if (tm->tm_sec < 0 || tm->tm_sec > 59)
        return 0;
    if (tm->tm_min < 0 || tm->tm_min > 59)
        return 0;
    if (tm->tm_hour < 0 || tm->tm_hour > 23)
        return 0;
    if (tm->tm_mday < 1 || tm->tm_mday > 31)
        return 0;
    if (tm->tm_mon < 0 || tm->tm_mon > 11)
        return 0;
    return 1;
}