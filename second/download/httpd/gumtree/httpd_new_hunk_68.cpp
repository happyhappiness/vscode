	    b = apr_bucket_transient_create((char*) data_type + ate, 
                                           headlen - ate, c->bucket_alloc);
	    APR_BRIGADE_INSERT_TAIL(bb, b);
            b = apr_bucket_flush_create(c->bucket_alloc);
	    APR_BRIGADE_INSERT_TAIL(bb, b);
	    ap_pass_brigade(cid->r->output_filters, bb);
            cid->response_sent = 1;
        }
        return 1;
    }

    case HSE_REQ_DONE_WITH_SESSION:
        /* Signal to resume the thread completing this request,
         * leave it to the pool cleanup to dispose of our mutex.
         */
        if (cid->completed) {
            (void)apr_thread_mutex_unlock(cid->completed);
            return 1;
        }
        else if (cid->dconf.log_unsupported) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ISAPI: ServerSupportFunction "
                          "HSE_REQ_DONE_WITH_SESSION is not supported: %s",
                          r->filename);
        }
        SetLastError(ERROR_INVALID_PARAMETER);
        return 0;

    case HSE_REQ_MAP_URL_TO_PATH:
    {
        /* Map a URL to a filename */
        char *file = (char *)buf_data;
        apr_uint32_t len;
