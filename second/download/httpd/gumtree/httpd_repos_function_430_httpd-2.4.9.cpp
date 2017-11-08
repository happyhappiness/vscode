static const char *log_request_duration_microseconds(request_rec *r, char *a)
{
    return apr_psprintf(r->pool, "%" APR_TIME_T_FMT,
                        (get_request_end_time(r) - r->request_time));
}