static void *x_create_server_config(apr_pool_t *p, server_rec *s)
{

    x_cfg *cfg;
    char *sname = s->server_hostname;

    /*
     * As with the x_create_dir_config() reoutine, we allocate and fill
     * in an empty record.
     */
    cfg = (x_cfg *) apr_pcalloc(p, sizeof(x_cfg));
    cfg->local = 0;
    cfg->congenital = 0;
    cfg->cmode = CONFIG_MODE_SERVER;
    /*
     * Note that we were called in the trace list.
     */
    sname = (sname != NULL) ? sname : "";
    cfg->loc = apr_pstrcat(p, "SVR(", sname, ")", NULL);
    trace_add(s, NULL, cfg, "x_create_server_config()");
    return (void *) cfg;
}