static uint64_t
parseTimeUnits(const char *unit, bool allowMsec)
{
    if (allowMsec && !strncasecmp(unit, T_MILLISECOND_STR, strlen(T_MILLISECOND_STR)))
        return 1;

    if (!strncasecmp(unit, T_SECOND_STR, strlen(T_SECOND_STR)))
        return 1000;

    if (!strncasecmp(unit, T_MINUTE_STR, strlen(T_MINUTE_STR)))
        return 60 * 1000;

    if (!strncasecmp(unit, T_HOUR_STR, strlen(T_HOUR_STR)))
        return 3600 * 1000;

    if (!strncasecmp(unit, T_DAY_STR, strlen(T_DAY_STR)))
        return 86400 * 1000;

    if (!strncasecmp(unit, T_WEEK_STR, strlen(T_WEEK_STR)))
        return 86400 * 7 * 1000;

    if (!strncasecmp(unit, T_FORTNIGHT_STR, strlen(T_FORTNIGHT_STR)))
        return 86400 * 14 * 1000;

    if (!strncasecmp(unit, T_MONTH_STR, strlen(T_MONTH_STR)))
        return static_cast<uint64_t>(86400) * 30 * 1000;

    if (!strncasecmp(unit, T_YEAR_STR, strlen(T_YEAR_STR)))
        return static_cast<uint64_t>(86400 * 1000 * 365.2522);

    if (!strncasecmp(unit, T_DECADE_STR, strlen(T_DECADE_STR)))
        return static_cast<uint64_t>(86400 * 1000 * 365.2522 * 10);

    debugs(3, DBG_IMPORTANT, "parseTimeUnits: unknown time unit '" << unit << "'");

    return 0;
}