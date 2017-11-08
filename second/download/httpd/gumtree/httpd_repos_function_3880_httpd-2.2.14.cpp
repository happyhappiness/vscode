static void SystemTimeToAprExpTime(apr_time_exp_t *xt, SYSTEMTIME *tm)
{
    static const int dayoffset[12] =
    {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

    /* Note; the caller is responsible for filling in detailed tm_usec,
     * tm_gmtoff and tm_isdst data when applicable.
     */
    xt->tm_usec = tm->wMilliseconds * 1000;
    xt->tm_sec  = tm->wSecond;
    xt->tm_min  = tm->wMinute;
    xt->tm_hour = tm->wHour;
    xt->tm_mday = tm->wDay;
    xt->tm_mon  = tm->wMonth - 1;
    xt->tm_year = tm->wYear - 1900;
    xt->tm_wday = tm->wDayOfWeek;
    xt->tm_yday = dayoffset[xt->tm_mon] + (tm->wDay - 1);
    xt->tm_isdst = 0;
    xt->tm_gmtoff = 0;

    /* If this is a leap year, and we're past the 28th of Feb. (the
     * 58th day after Jan. 1), we'll increment our tm_yday by one.
     */
    if (IsLeapYear(tm->wYear) && (xt->tm_yday > 58))
        xt->tm_yday++;
}