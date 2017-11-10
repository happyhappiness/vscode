static const char *header_request_time(request_rec *r, char *a)
{
    return apr_psprintf(r->pool, "t=%" APR_TIME_T_FMT, r->request_time);
}