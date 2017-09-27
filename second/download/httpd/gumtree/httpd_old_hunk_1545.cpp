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
