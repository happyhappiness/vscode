static const char *log_request_duration_scaled(request_rec *r, char *a)
{
    apr_time_t duration = get_request_end_time(r) - r->request_time;
    if (*a == '\0' || !strcasecmp(a, "s")) {
        duration = apr_time_sec(duration);
    }
    else if (!strcasecmp(a, "ms")) {
        duration = apr_time_as_msec(duration);
    }
    else if (!strcasecmp(a, "us")) {
    }
    else {
        /* bogus format */
        return a;
    }
    return apr_psprintf(r->pool, "%" APR_TIME_T_FMT, duration);
}