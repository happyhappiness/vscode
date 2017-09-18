        conn_rec *c = r->connection;
        APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pool_create(cmd, strlen(cmd), r->pool, c->bucket_alloc));
        APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_flush_create(c->bucket_alloc));
        ap_pass_brigade(ftp_ctrl->output_filters, bb);

        /* strip off the CRLF for logging */
        apr_cpystrn(message, cmd, sizeof(message));
        if ((crlf = strchr(message, '\r')) != NULL ||
            (crlf = strchr(message, '\n')) != NULL)
            *crlf = '\0';
        if (strncmp(message,"PASS ", 5) == 0)
            strcpy(&message[5], "****");
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
