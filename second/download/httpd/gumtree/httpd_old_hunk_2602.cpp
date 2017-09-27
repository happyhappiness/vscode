    errmsg = apr_dbd_error(rec->driver, rec->handle, 0);
    if (!errmsg) {
        errmsg = "(unknown)";
    }

    svr = ap_get_module_config(s->module_config, &dbd_module);
    ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                 "DBD [%s] Error: %s", svr->cfg->name, errmsg);
    return rv;
}

DBD_DECLARE_NONSTD(ap_dbd_t*) ap_dbd_open(apr_pool_t *pool, server_rec *s)
{
