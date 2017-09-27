        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                     "proxy: AJP: request failed to %pI (%s)",
                     conn->worker->cp->addr,
                     conn->worker->hostname);
        if (status == AJP_EOVERFLOW)
            return HTTP_BAD_REQUEST;
        else {
            /*
             * This is only non fatal when the method is idempotent. In this
             * case we can dare to retry it with a different worker if we are
             * a balancer member.
             */
            if (is_idempotent(r) == METHOD_IDEMPOTENT) {
