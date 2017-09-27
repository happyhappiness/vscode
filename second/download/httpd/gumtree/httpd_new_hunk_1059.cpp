        rv = apr_dbd_check_conn(svr->conn->driver, pool, svr->conn->handle);
        if ((rv != APR_SUCCESS) && (rv != APR_ENOTIMPL)) {
            errmsg = apr_dbd_error(arec->driver, arec->handle, rv);
            if (!errmsg) {
                errmsg = "(unknown)";
            }
            ap_log_perror(APLOG_MARK, APLOG_ERR, rv, pool,
                          "DBD[%s] Error: %s", svr->name, errmsg);
            svr->conn = NULL;
        }
    }
/* We don't have a connection right now, so we'll open one */
    if (!svr->conn) {
