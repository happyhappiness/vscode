    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: got response from %pI (%s)",
                     conn->worker->cp->addr,
                     conn->worker->hostname);
        rv = OK;
    }

    if (backend_failed) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                     "proxy: dialog to %pI (%s) failed",
                     conn->worker->cp->addr,
