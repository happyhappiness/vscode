    /* allocate an AJP message to store the data of the buckets */
    bufsiz = maxsize;
    status = ajp_alloc_data_msg(r->pool, &buff, &bufsiz, &msg);
    if (status != APR_SUCCESS) {
        /* We had a failure: Close connection to backend */
        conn->close++;
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00869)
                      "ajp_alloc_data_msg failed");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* read the first bloc of data */
    input_brigade = apr_brigade_create(p, r->connection->bucket_alloc);
    tenc = apr_table_get(r->headers_in, "Transfer-Encoding");
    if (tenc && (strcasecmp(tenc, "chunked") == 0)) {
        /* The AJP protocol does not want body data yet */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00870) "request is chunked");
    } else {
        /* Get client provided Content-Length header */
        content_length = get_content_length(r);
        status = ap_get_brigade(r->input_filters, input_brigade,
                                AP_MODE_READBYTES, APR_BLOCK_READ,
                                maxsize - AJP_HEADER_SZ);

        if (status != APR_SUCCESS) {
            /* We had a failure: Close connection to backend */
            conn->close++;
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00871)
                          "ap_get_brigade failed");
            apr_brigade_destroy(input_brigade);
            return HTTP_BAD_REQUEST;
        }

        /* have something */
        if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(input_brigade))) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00872) "APR_BUCKET_IS_EOS");
        }

        /* Try to send something */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00873)
                      "data to read (max %" APR_SIZE_T_FMT
                      " at %" APR_SIZE_T_FMT ")", bufsiz, msg->pos);

        status = apr_brigade_flatten(input_brigade, buff, &bufsiz);
        if (status != APR_SUCCESS) {
            /* We had a failure: Close connection to backend */
            conn->close++;
            apr_brigade_destroy(input_brigade);
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00874)
                          "apr_brigade_flatten");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        apr_brigade_cleanup(input_brigade);

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00875)
                      "got %" APR_SIZE_T_FMT " bytes of data", bufsiz);
        if (bufsiz > 0) {
            status = ajp_send_data_msg(conn->sock, msg, bufsiz);
            ajp_msg_log(r, msg, "First ajp_send_data_msg: ajp_ilink_send packet dump");
            if (status != APR_SUCCESS) {
                /* We had a failure: Close connection to backend */
                conn->close++;
                apr_brigade_destroy(input_brigade);
                ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00876)
                              "send failed to %pI (%s)",
                              conn->worker->cp->addr,
                              conn->worker->s->hostname);
                /*
                 * It is fatal when we failed to send a (part) of the request
                 * body.
                 */
                return HTTP_INTERNAL_SERVER_ERROR;
            }
            conn->worker->s->transferred += bufsiz;
            send_body = 1;
        }
        else if (content_length > 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00877)
                          "read zero bytes, expecting"
                          " %" APR_OFF_T_FMT " bytes",
                          content_length);
            /*
             * We can only get here if the client closed the connection
             * to us without sending the body.
             * Now the connection is in the wrong state on the backend.
             * Sending an empty data msg doesn't help either as it does
             * not move this connection to the correct state on the backend
