static char *current_logtime(request_rec *r)
{
    apr_time_exp_t t;
    char tstr[80];
    apr_size_t len;

    apr_time_exp_lt(&t, apr_time_now());

    apr_strftime(tstr, &len, sizeof(tstr), "[%d/%b/%Y:%H:%M:%S ", &t);
    apr_snprintf(tstr+len, sizeof(tstr)-len, "%c%.2d%.2d]",
                 t.tm_gmtoff < 0 ? '-' : '+',
                 t.tm_gmtoff / (60*60), t.tm_gmtoff % (60*60));

    return apr_pstrdup(r->pool, tstr);
}