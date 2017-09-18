         * option is valid only for HSE_IO_SEND_HEADERS - we are a bit
         * more flexible and assume with the flag, pHead are the
         * response headers, and without, pHead simply contains text
         * (handled after this case).
         */
        if ((tf->dwFlags & HSE_IO_SEND_HEADERS) && tf->pszStatusCode) {
            ate = send_response_header(cid, tf->pszStatusCode,
                                            (char*)tf->pHead,
                                            strlen(tf->pszStatusCode),
                                            tf->HeadLength);
        }
        else if (!cid->headers_set && tf->pHead && tf->HeadLength
                                   && *(char*)tf->pHead) {
            ate = send_response_header(cid, NULL, (char*)tf->pHead,
                                            0, tf->HeadLength);
            if (ate < 0)
            {
                apr_brigade_destroy(bb);
                apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
                return 0;
            }
        }

        if (tf->pHead && (apr_size_t)ate < tf->HeadLength) {
            b = apr_bucket_transient_create((char*)tf->pHead + ate,
                                            tf->HeadLength - ate,
                                            c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, b);
            sent = tf->HeadLength;
        }

        sent += (apr_uint32_t)fsize;
        brigade_insert_file(bb, fd, tf->Offset, fsize, r->pool);

        if (tf->pTail && tf->TailLength) {
            sent += tf->TailLength;
            b = apr_bucket_transient_create((char*)tf->pTail,
                                            tf->TailLength, c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, b);
        }

        b = apr_bucket_flush_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        rv = ap_pass_brigade(r->output_filters, bb);
        cid->response_sent = 1;
        if (rv != APR_SUCCESS)
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                          "ISAPI: ServerSupport function "
                          "HSE_REQ_TRANSMIT_FILE "
                          "ap_pass_brigade failed: %s", r->filename);

        /* Use tf->pfnHseIO + tf->pContext, or if NULL, then use cid->fnIOComplete
         * pass pContect to the HseIO callback.
         */
        if (tf->dwFlags & HSE_IO_ASYNC) {
            if (tf->pfnHseIO) {
                if (rv == APR_SUCCESS) {
                    tf->pfnHseIO(cid->ecb, tf->pContext,
                                 ERROR_SUCCESS, sent);
                }
                else {
                    tf->pfnHseIO(cid->ecb, tf->pContext,
                                 ERROR_WRITE_FAULT, sent);
                }
            }
            else if (cid->completion) {
                if (rv == APR_SUCCESS) {
                    cid->completion(cid->ecb, cid->completion_arg,
                                    sent, ERROR_SUCCESS);
                }
                else {
                    cid->completion(cid->ecb, cid->completion_arg,
                                    sent, ERROR_WRITE_FAULT);
                }
            }
        }
        return (rv == APR_SUCCESS);
    }

    case HSE_REQ_REFRESH_ISAPI_ACL:
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ISAPI: ServerSupportFunction "
