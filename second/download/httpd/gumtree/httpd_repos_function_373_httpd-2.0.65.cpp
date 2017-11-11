static const char *log_request_duration_microseconds(request_rec *r, char *a)
{
    return apr_psprintf(r->pool, "%" APR_TIME_T_FMT, 
                        (apr_time_now() - r->request_time));
}