static int log_after(request_rec *r)
{
    fcfg *cfg = ap_get_module_config(r->server->module_config,
                                     &log_forensic_module);
    const char *id = ap_get_module_config(r->request_config,
                                          &log_forensic_module);
    char *s;
    apr_size_t l, n;
    apr_status_t rv;

    if (!cfg->fd) {
        return DECLINED;
    }

    s = apr_pstrcat(r->pool, "-", id, "\n", NULL);
    l = n = strlen(s);
    rv = apr_file_write(cfg->fd, s, &n);
    ap_assert(rv == APR_SUCCESS && n == l);

    return OK;
}