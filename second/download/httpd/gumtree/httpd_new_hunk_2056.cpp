            return HTTP_BAD_REQUEST;
        else
            return HTTP_SERVICE_UNAVAILABLE;
    }

    /* allocate an AJP message to store the data of the buckets */
    bufsiz = maxsize;
    status = ajp_alloc_data_msg(r->pool, &buff, &bufsiz, &msg);
    if (status != APR_SUCCESS) {
        /* We had a failure: Close connection to backend */
        conn->close++;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: ajp_alloc_data_msg failed");
