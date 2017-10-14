static apr_status_t dbd_check(apr_pool_t *pool, server_rec *s, ap_dbd_t *rec)
{
    svr_cfg *svr;
    apr_status_t rv = apr_dbd_check_conn(rec->driver, pool, rec->handle);
    const char *errmsg;

    if ((rv == APR_SUCCESS) || (rv == APR_ENOTIMPL)) {
        return APR_SUCCESS;
    }

    errmsg = apr_dbd_error(rec->driver, rec->handle, rv);
    if (!errmsg) {
        errmsg = "(unknown)";
    }

    svr = ap_get_module_config(s->module_config, &dbd_module);
    ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                 "DBD [%s] Error: %s", svr->cfg->name, errmsg);
    return rv;
}