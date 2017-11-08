static const char *header_request_duration(request_rec *r, char *a)
{
    return apr_psprintf(r->pool, "D=%" APR_TIME_T_FMT,
                        (apr_time_now() - r->request_time));
}