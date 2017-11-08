static const char *log_request_time(request_rec *r, char *a)
{
    apr_time_exp_t xt;

    /* ###  I think getting the time again at the end of the request
     * just for logging is dumb.  i know it's "required" for CLF.
     * folks writing log parsing tools don't realise that out of order
     * times have always been possible (consider what happens if one
     * process calculates the time to log, but then there's a context
     * switch before it writes and before that process is run again the
     * log rotation occurs) and they should just fix their tools rather
     * than force the server to pay extra cpu cycles.  if you've got
     * a problem with this, you can set the define.  -djg
     */
    if (a && *a) {              /* Custom format */
        /* The custom time formatting uses a very large temp buffer
         * on the stack.  To avoid using so much stack space in the
         * common case where we're not using a custom format, the code
         * for the custom format in a separate function.  (That's why
         * log_request_time_custom is not inlined right here.)
         */
#ifdef I_INSIST_ON_EXTRA_CYCLES_FOR_CLF_COMPLIANCE
        ap_explode_recent_localtime(&xt, apr_time_now());
#else
        ap_explode_recent_localtime(&xt, r->request_time);
#endif
        return log_request_time_custom(r, a, &xt);
    }
    else {                      /* CLF format */
        /* This code uses the same technique as ap_explode_recent_localtime():
         * optimistic caching with logic to detect and correct race conditions.
         * See the comments in server/util_time.c for more information.
         */
        cached_request_time* cached_time = apr_palloc(r->pool,
                                                      sizeof(*cached_time));
#ifdef I_INSIST_ON_EXTRA_CYCLES_FOR_CLF_COMPLIANCE
        apr_time_t request_time = apr_time_now();
#else
        apr_time_t request_time = r->request_time;
#endif
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
            timz = xt.tm_gmtoff;
            if (timz < 0) {
                timz = -timz;
                sign = '-';
            }
            else {
                sign = '+';
            }
            cached_time->t = t_seconds;
            apr_snprintf(cached_time->timestr, DEFAULT_REQUEST_TIME_SIZE,
                         "[%02d/%s/%d:%02d:%02d:%02d %c%.2d%.2d]",
                         xt.tm_mday, apr_month_snames[xt.tm_mon],
                         xt.tm_year+1900, xt.tm_hour, xt.tm_min, xt.tm_sec,
                         sign, timz / (60*60), (timz % (60*60)) / 60);
            cached_time->t_validate = t_seconds;
            request_time_cache[i] = *cached_time;
        }
        return cached_time->timestr;
    }
}