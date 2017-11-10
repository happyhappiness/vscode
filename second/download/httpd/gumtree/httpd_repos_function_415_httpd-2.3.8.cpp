static const char *log_request_time(request_rec *r, char *a)
{
    apr_time_exp_t xt;
    apr_time_t request_time = r->request_time;
    int fmt_type = TIME_FMT_CUSTOM;
    char *fmt = a;

    if (fmt && *fmt) {
        if (!strncmp(fmt, "begin", 5)) {
            fmt += 5;
            if (!*fmt) {
                fmt_type = TIME_FMT_CLF;
            }
            else if (*fmt == ':') {
                fmt++;
                a = fmt;
            }
        }
        else if (!strncmp(fmt, "end", 3)) {
            fmt += 3;
            if (!*fmt) {
                request_time = get_request_end_time(r);
                fmt_type = TIME_FMT_CLF;
            }
            else if (*fmt == ':') {
                fmt++;
                a = fmt;
                request_time = get_request_end_time(r);
            }
        }
        if (!strncmp(fmt, "msec", 4)) {
            fmt += 4;
            if (!*fmt) {
                fmt_type = TIME_FMT_ABS_MSEC;
            }
            else if (!strcmp(fmt, "_frac")) {
                fmt_type = TIME_FMT_ABS_MSEC_FRAC;
            }
        }
        else if (!strncmp(fmt, "usec", 4)) {
            fmt += 4;
            if (!*fmt) {
                fmt_type = TIME_FMT_ABS_USEC;
            }
            else if (!strcmp(fmt, "_frac")) {
                fmt_type = TIME_FMT_ABS_USEC_FRAC;
            }
        }
        else if (!strcmp(fmt, "sec")) {
            fmt_type = TIME_FMT_ABS_SEC;
        }
        else if (!*fmt) {
            fmt_type = TIME_FMT_CLF;
        }
    }
    else {
        fmt_type = TIME_FMT_CLF;
    }

    if (fmt_type >= TIME_FMT_ABS_SEC) {      /* Absolute (micro-/milli-)second time
                                              * or msec/usec fraction
                                              */
        char* buf = apr_palloc(r->pool, 20);
        switch (fmt_type) {
        case TIME_FMT_ABS_SEC:
            apr_snprintf(buf, 20, "%" APR_TIME_T_FMT, apr_time_sec(request_time));
            break;
        case TIME_FMT_ABS_MSEC:
            apr_snprintf(buf, 20, "%" APR_TIME_T_FMT, apr_time_as_msec(request_time));
            break;
        case TIME_FMT_ABS_USEC:
            apr_snprintf(buf, 20, "%" APR_TIME_T_FMT, request_time);
            break;
        case TIME_FMT_ABS_MSEC_FRAC:
            apr_snprintf(buf, 20, "%03" APR_TIME_T_FMT, apr_time_msec(request_time));
            break;
        case TIME_FMT_ABS_USEC_FRAC:
            apr_snprintf(buf, 20, "%06" APR_TIME_T_FMT, apr_time_usec(request_time));
            break;
        default:
            return "-";
        }
        return buf;
    }
    else if (fmt_type == TIME_FMT_CUSTOM) {  /* Custom format */
        /* The custom time formatting uses a very large temp buffer
         * on the stack.  To avoid using so much stack space in the
         * common case where we're not using a custom format, the code
         * for the custom format in a separate function.  (That's why
         * log_request_time_custom is not inlined right here.)
         */
        ap_explode_recent_localtime(&xt, request_time);
        return log_request_time_custom(r, a, &xt);
    }
    else {                                   /* CLF format */
        /* This code uses the same technique as ap_explode_recent_localtime():
         * optimistic caching with logic to detect and correct race conditions.
         * See the comments in server/util_time.c for more information.
         */
        cached_request_time* cached_time = apr_palloc(r->pool,
                                                      sizeof(*cached_time));
        unsigned t_seconds = (unsigned)apr_time_sec(request_time);
        unsigned i = t_seconds & TIME_CACHE_MASK;
        *cached_time = request_time_cache[i];
        if ((t_seconds != cached_time->t) ||
            (t_seconds != cached_time->t_validate)) {

            /* Invalid or old snapshot, so compute the proper time string
             * and store it in the cache
             */
            char sign;
            int timz;

            ap_explode_recent_localtime(&xt, request_time);
  