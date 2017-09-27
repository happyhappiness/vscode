
    /* allocate an AJP message to store the data of the buckets */
    bufsiz = maxsize;
    status = ajp_alloc_data_msg(r->pool, &buff, &bufsiz, &msg);
    if (status != APR_SUCCESS) {
        /* We had a failure: Close connection to backend */
        conn->close = 1;
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00869)
                      "ajp_alloc_data_msg failed");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* read the first bloc of data */
