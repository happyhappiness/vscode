static const char *log_request_time_custom(request_rec *r, char *a,
                                           apr_time_exp_t *xt)
{
    apr_size_t retcode;
    char tstr[MAX_STRING_LEN];
    apr_strftime(tstr, &retcode, sizeof(tstr), a, xt);
    return apr_pstrdup(r->pool, tstr);
}