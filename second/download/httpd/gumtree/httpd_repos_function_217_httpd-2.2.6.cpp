static void dav_format_time(int style, apr_time_t sec, char *buf)
{
    apr_time_exp_t tms;

    /* ### what to do if fails? */
    (void) apr_time_exp_gmt(&tms, sec);

    if (style == DAV_STYLE_ISO8601) {
        /* ### should we use "-00:00" instead of "Z" ?? */

        /* 20 chars plus null term */
        sprintf(buf, "%.4d-%.2d-%.2dT%.2d:%.2d:%.2dZ",
               tms.tm_year + 1900, tms.tm_mon + 1, tms.tm_mday,
               tms.tm_hour, tms.tm_min, tms.tm_sec);
        return;
    }

    /* RFC 822 date format; as strftime '%a, %d %b %Y %T GMT' */

    /* 29 chars plus null term */
    sprintf(buf,
            "%s, %.2d %s %d %.2d:%.2d:%.2d GMT",
           apr_day_snames[tms.tm_wday],
           tms.tm_mday, apr_month_snames[tms.tm_mon],
           tms.tm_year + 1900,
           tms.tm_hour, tms.tm_min, tms.tm_sec);
}