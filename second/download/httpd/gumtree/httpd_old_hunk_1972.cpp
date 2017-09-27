{
    void *rec = NULL;
    svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
    apr_status_t rv = APR_SUCCESS;
    const char *errmsg;

    if (!svr->persist) {
        /* Return a once-only connection */
        rv = dbd_construct(&rec, svr, s->process->pool);
        return (rv == APR_SUCCESS) ? arec : NULL;
    }

