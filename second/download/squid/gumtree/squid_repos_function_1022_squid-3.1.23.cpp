static int
parseTimeUnits(const char *unit)
{
    if (!strncasecmp(unit, T_SECOND_STR, strlen(T_SECOND_STR)))
        return 1;

    if (!strncasecmp(unit, T_MINUTE_STR, strlen(T_MINUTE_STR)))
        return 60;

    if (!strncasecmp(unit, T_HOUR_STR, strlen(T_HOUR_STR)))
        return 3600;

    if (!strncasecmp(unit, T_DAY_STR, strlen(T_DAY_STR)))
        return 86400;

    if (!strncasecmp(unit, T_WEEK_STR, strlen(T_WEEK_STR)))
        return 86400 * 7;

    if (!strncasecmp(unit, T_FORTNIGHT_STR, strlen(T_FORTNIGHT_STR)))
        return 86400 * 14;

    if (!strncasecmp(unit, T_MONTH_STR, strlen(T_MONTH_STR)))
        return 86400 * 30;

    if (!strncasecmp(unit, T_YEAR_STR, strlen(T_YEAR_STR)))
        return static_cast<int>(86400 * 365.2522);

    if (!strncasecmp(unit, T_DECADE_STR, strlen(T_DECADE_STR)))
        return static_cast<int>(86400 * 365.2522 * 10);

    debugs(3, 1, "parseTimeUnits: unknown time unit '" << unit << "'");

    return 0;
}