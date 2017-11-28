static struct tm *
parse_date_elements(const char *day, const char *month, const char *year,
                    const char *aTime, const char *zone) {
    static struct tm tm;
    char *t;
    memset(&tm, 0, sizeof(tm));

    if (!day || !month || !year || !aTime || (zone && strcmp(zone, "GMT")))
        return NULL;
    tm.tm_mday = atoi(day);
    tm.tm_mon = make_month(month);
    if (tm.tm_mon < 0)
        return NULL;
    tm.tm_year = atoi(year);
    if (strlen(year) == 4)
        tm.tm_year -= 1900;
    else if (tm.tm_year < 70)
        tm.tm_year += 100;
    else if (tm.tm_year > 19000)
        tm.tm_year -= 19000;
    tm.tm_hour = make_num(aTime);
    t = strchr(aTime, ':');
    if (!t)
        return NULL;
    t++;
    tm.tm_min = atoi(t);
    t = strchr(t, ':');
    if (t)
        tm.tm_sec = atoi(t + 1);
    return tmSaneValues(&tm) ? &tm : NULL;
}