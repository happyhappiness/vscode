static void parseTime(const char *s, time_t *secs, time_t *start)
{
    double value;
    char unit;
    struct tm *ltime;
    int periodLength = 3600;

    *secs = 0;
    *start = time(NULL);
    ltime = localtime(start);

    sscanf(s, " %lf %c", &value, &unit);
    switch (unit) {
    case 's':
        periodLength = 1;
        break;
    case 'm':
        periodLength = 60;
        *start -= ltime->tm_sec;
        break;
    case 'h':
        periodLength = 3600;
        *start -= ltime->tm_min * 60 + ltime->tm_sec;
        break;
    case 'd':
        periodLength = 24 * 3600;
        *start -= ltime->tm_hour * 3600 + ltime->tm_min * 60 + ltime->tm_sec;
        break;
    case 'w':
        periodLength = 7 * 24 * 3600;
        *start -= ltime->tm_hour * 3600 + ltime->tm_min * 60 + ltime->tm_sec;
        *start -= ltime->tm_wday * 24 * 3600;
        *start += 24 * 3600;         // in europe, the week starts monday
        break;
    default:
        log_error("Wrong time unit \"%c\". Only \"m\", \"h\", \"d\", or \"w\" allowed.\n", unit);
        break;
    }

    *secs = (long)(periodLength * value);
}