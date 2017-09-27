                                     r->pool);
        if (cid->completed && (rv == APR_SUCCESS)) {
            rv = apr_thread_mutex_lock(cid->completed);
        }

        if (!cid->completed || (rv != APR_SUCCESS)) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ISAPI: Failed to create completion mutex");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }

    /* All right... try and run the sucker */
    rv = (*isa->HttpExtensionProc)(cid->ecb);

    /* Check for a log message - and log it */
    if (cid->ecb->lpszLogData && *cid->ecb->lpszLogData)
        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                      "ISAPI: %s: %s", r->filename, cid->ecb->lpszLogData);

    switch(rv) {
        case 0:  /* Strange, but MS isapi accepts this as success */
        case HSE_STATUS_SUCCESS:
        case HSE_STATUS_SUCCESS_AND_KEEP_CONN:
            /* Ignore the keepalive stuff; Apache handles it just fine without
