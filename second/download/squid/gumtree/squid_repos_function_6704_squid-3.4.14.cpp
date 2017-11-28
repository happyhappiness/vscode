static struct tm *
parse_date(const char *str) {
    struct tm *tm;
    static char tmp[64];
    char *t;
    char *wday = NULL;
    char *day = NULL;
    char *month = NULL;
    char *year = NULL;
    char *timestr = NULL;
    char *zone = NULL;

    xstrncpy(tmp, str, 64);

    for (t = strtok(tmp, ", "); t; t = strtok(NULL, ", ")) {
        if (xisdigit(*t)) {
            if (!day) {
                day = t;
                t = strchr(t, '-');
                if (t) {
                    *t++ = '\0';
                    month = t;
                    t = strchr(t, '-');
                    if (!t)
                        return NULL;
                    *t++ = '\0';
                    year = t;
                }
            } else if (strchr(t, ':'))
                timestr = t;
            else if (!year)
                year = t;
            else
                return NULL;
        } else if (!wday)
            wday = t;
        else if (!month)
            month = t;
        else if (!zone)
            zone = t;
        else
            return NULL;
    }
    tm = parse_date_elements(day, month, year, timestr, zone);

    return tm;
}