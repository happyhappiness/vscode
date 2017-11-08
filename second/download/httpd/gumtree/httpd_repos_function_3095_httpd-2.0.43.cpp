static void SystemTimeToAprExpTime(apr_time_exp_t *xt, SYSTEMTIME *tm, BOOL lt)
{
    TIME_ZONE_INFORMATION tz;
    DWORD rc;
    static const int dayoffset[12] =
    {0, 31, 59, 90, 120, 151, 182, 212, 243, 273, 304, 334};

    /* XXX: this is a looser - can't forefit precision like this
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

    /* If this is a leap year, and we're past the 28th of Feb. (the
     * 58th day after Jan. 1), we'll increment our tm_yday by one.
     */
    if (IsLeapYear(tm->wYear) && (xt->tm_yday > 58))
        xt->tm_yday++;

    if (!lt) {
        xt->tm_isdst = 0;
        xt->tm_gmtoff = 0;
        return;
    }

    rc = GetTimeZoneInformation(&tz);
    switch (rc) {
    case TIME_ZONE_ID_UNKNOWN:
        xt->tm_isdst = 0;
        /* Bias = UTC - local time in minutes 
         * tm_gmtoff is seconds east of UTC
         */
        xt->tm_gmtoff = tz.Bias * -60;
        break;
    case TIME_ZONE_ID_STANDARD:
        xt->tm_isdst = 0;
        xt->tm_gmtoff = (tz.Bias + tz.StandardBias) * -60;
        break;
    case TIME_ZONE_ID_DAYLIGHT:
        xt->tm_isdst = 1;
        xt->tm_gmtoff = (tz.Bias + tz.DaylightBias) * -60;
        break;
    default:
        xt->tm_isdst = 0;
        xt->tm_gmtoff = 0;
    }
    return;
}