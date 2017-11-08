static const char *log_ttfb(request_rec *r, char *a)
{
    logio_req_t *rconf = ap_get_module_config(r->request_config,
                                           &logio_module);

    if (!rconf || !rconf->ttfb) { 
        return "-";
    }

    return apr_psprintf(r->pool, "%" APR_TIME_T_FMT, rconf->ttfb);
}