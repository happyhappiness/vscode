static const char *log_request_duration(request_rec *r, char *a)
{
    apr_time_t duration = apr_time_now() - r->request_time;
    return apr_psprintf(r->pool, "%" APR_TIME_T_FMT, apr_time_sec(duration));
}