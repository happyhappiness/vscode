         */
        apr_ssize_t ate = send_response_header(cid, shi->pszStatus,
                                               shi->pszHeader,
                                               shi->cchStatus,
                                               shi->cchHeader);
        if (ate < 0) {
            apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
            return 0;
        }
        else if ((apr_size_t)ate < shi->cchHeader) {
            apr_bucket_brigade *bb;
            apr_bucket *b;
            bb = apr_brigade_create(cid->r->pool, c->bucket_alloc);
            b = apr_bucket_transient_create(shi->pszHeader + ate,
                                            shi->cchHeader - ate,
                                            c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, b);
            b = apr_bucket_flush_create(c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, b);
            rv = ap_pass_brigade(cid->r->output_filters, bb);
            cid->response_sent = 1;
            if (rv != APR_SUCCESS)
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                              "ISAPI: ServerSupport function "
                              "HSE_REQ_SEND_RESPONSE_HEADER_EX "
                              "ap_pass_brigade failed: %s", r->filename);
            return (rv == APR_SUCCESS);
        }
        /* Deliberately hold off sending 'just the headers' to begin to
         * accumulate the body and speed up the overall response, or at
         * least wait for the end the session.
         */
        return 1;
    }

    case HSE_REQ_CLOSE_CONNECTION:  /* Added after ISAPI 4.0 */
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ISAPI: ServerSupportFunction "
                          "HSE_REQ_CLOSE_CONNECTION "
                          "is not supported: %s", r->filename);
        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
        return 0;

    case HSE_REQ_IS_CONNECTED:  /* Added after ISAPI 4.0 */
        /* Returns True if client is connected c.f. MSKB Q188346
         * assuming the identical return mechanism as HSE_REQ_IS_KEEP_CONN
         */
