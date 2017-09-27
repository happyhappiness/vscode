    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: got response from %pI (%s)",
                     conn->worker->cp->addr,
                     conn->worker->hostname);

        if (psf->error_override && ap_is_HTTP_ERROR(r->status)) {
            /* clear r->status for override error, otherwise ErrorDocument
             * thinks that this is a recursive error, and doesn't find the
             * custom error page
             */
            rv = r->status;
            r->status = HTTP_OK;
        } else {
            rv = OK;
        }
    }

    if (backend_failed) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                     "proxy: dialog to %pI (%s) failed",
                     conn->worker->cp->addr,
