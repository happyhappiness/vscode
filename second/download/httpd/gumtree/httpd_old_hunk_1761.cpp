        conn->close++;
        apr_brigade_destroy(input_brigade);
        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                     "proxy: read response failed from %pI (%s)",
                     conn->worker->cp->addr,
                     conn->worker->hostname);
        return HTTP_SERVICE_UNAVAILABLE;
    }
    /* parse the reponse */
    result = ajp_parse_type(r, conn->data);
    output_brigade = apr_brigade_create(p, r->connection->bucket_alloc);

    /*
