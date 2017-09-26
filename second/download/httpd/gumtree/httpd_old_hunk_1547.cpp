                                            c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, b);
            sent = tf->HeadLength;
        }

        sent += (apr_uint32_t)fsize;
#if APR_HAS_LARGE_FILES
        if (r->finfo.size > AP_MAX_SENDFILE) {
            /* APR_HAS_LARGE_FILES issue; must split into mutiple buckets,
             * no greater than MAX(apr_size_t), and more granular than that
             * in case the brigade code/filters attempt to read it directly.
             */
            b = apr_bucket_file_create(fd, tf->Offset, AP_MAX_SENDFILE,
                                       r->pool, c->bucket_alloc);
            while (fsize > AP_MAX_SENDFILE) {
                apr_bucket *bc;
                apr_bucket_copy(b, &bc);
                APR_BRIGADE_INSERT_TAIL(bb, bc);
                b->start += AP_MAX_SENDFILE;
                fsize -= AP_MAX_SENDFILE;
            }
            b->length = (apr_size_t)fsize; /* Resize just the last bucket */
        }
        else
#endif
            b = apr_bucket_file_create(fd, tf->Offset, (apr_size_t)fsize,
                                       r->pool, c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);

        if (tf->pTail && tf->TailLength) {
            sent += tf->TailLength;
            b = apr_bucket_transient_create((char*)tf->pTail,
                                            tf->TailLength, c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, b);
        }

        b = apr_bucket_flush_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        ap_pass_brigade(r->output_filters, bb);
        cid->response_sent = 1;

        /* Use tf->pfnHseIO + tf->pContext, or if NULL, then use cid->fnIOComplete
         * pass pContect to the HseIO callback.
         */
        if (tf->dwFlags & HSE_IO_ASYNC) {
            if (tf->pfnHseIO) {
                if (rv == OK) {
                    tf->pfnHseIO(cid->ecb, tf->pContext,
                                 ERROR_SUCCESS, sent);
                }
                else {
                    tf->pfnHseIO(cid->ecb, tf->pContext,
                                 ERROR_WRITE_FAULT, sent);
                }
            }
            else if (cid->completion) {
                if (rv == OK) {
                    cid->completion(cid->ecb, cid->completion_arg,
                                    sent, ERROR_SUCCESS);
                }
                else {
                    cid->completion(cid->ecb, cid->completion_arg,
                                    sent, ERROR_WRITE_FAULT);
                }
            }
        }
        return (rv == OK);
    }

    case HSE_REQ_REFRESH_ISAPI_ACL:
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ISAPI: ServerSupportFunction "
