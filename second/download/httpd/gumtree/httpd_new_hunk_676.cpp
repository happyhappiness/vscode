         */
        apr_ssize_t ate = send_response_header(cid, shi->pszStatus,
                                               shi->pszHeader,
                                               shi->cchStatus,
                                               shi->cchHeader);
        if (ate < 0) {
            SetLastError(ERROR_INVALID_PARAMETER);
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
            ap_pass_brigade(cid->r->output_filters, bb);
            cid->response_sent = 1;
        }
        return 1;
    }

    case HSE_REQ_CLOSE_CONNECTION:  /* Added after ISAPI 4.0 */
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ISAPI: ServerSupportFunction "
                          "HSE_REQ_CLOSE_CONNECTION "
                          "is not supported: %s", r->filename);
        SetLastError(ERROR_INVALID_PARAMETER);
        return 0;

    case HSE_REQ_IS_CONNECTED:  /* Added after ISAPI 4.0 */
        /* Returns True if client is connected c.f. MSKB Q188346
         * assuming the identical return mechanism as HSE_REQ_IS_KEEP_CONN
         */
