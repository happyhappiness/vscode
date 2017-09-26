            bb = apr_brigade_create(cid->r->pool, c->bucket_alloc);
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
