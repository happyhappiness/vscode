        conn->close++;
        apr_brigade_destroy(input_brigade);
        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                     "proxy: read response failed from %pI (%s)",
                     conn->worker->cp->addr,
                     conn->worker->hostname);
        /*
         * This is only non fatal when we have not sent (parts) of a possible
         * request body so far (we do not store it and thus cannot sent it
         * again) and the method is idempotent. In this case we can dare to
         * retry it with a different worker if we are a balancer member.
         */
        if (!send_body && (is_idempotent(r) == METHOD_IDEMPOTENT)) {
            return HTTP_SERVICE_UNAVAILABLE;
        }
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    /* parse the reponse */
    result = ajp_parse_type(r, conn->data);
    output_brigade = apr_brigade_create(p, r->connection->bucket_alloc);

    /*
