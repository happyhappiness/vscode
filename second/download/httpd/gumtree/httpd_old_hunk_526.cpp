                               "from HttpExtensionProc() is not supported: %s",
                               r->filename);
                 r->status = HTTP_INTERNAL_SERVER_ERROR;
            }
            break;

        case HSE_STATUS_ERROR:    
            /* end response if we have yet to do so.
             */
            r->status = HTTP_INTERNAL_SERVER_ERROR;
            break;

        default:
            /* TODO: log unrecognized retval for debugging 
             */
             ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                           "ISAPI: return code %d from HttpExtensionProc() "
                           "was not not recognized", rv);
            r->status = HTTP_INTERNAL_SERVER_ERROR;
            break;
    }

    /* Flush the response now, including headers-only responses */
    if (cid->headers_set) {
        conn_rec *c = r->connection;
        apr_bucket_brigade *bb;
        apr_bucket *b;
        apr_status_t rv;

        bb = apr_brigade_create(r->pool, c->bucket_alloc);
        b = apr_bucket_eos_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        b = apr_bucket_flush_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        rv = ap_pass_brigade(r->output_filters, bb);
        cid->response_sent = 1;

        return OK;  /* NOT r->status or cid->r->status, even if it has changed. */
    }
    
    /* As the client returned no error, and if we did not error out
     * ourselves, trust dwHttpStatusCode to say something relevant.
     */
    if (!ap_is_HTTP_SERVER_ERROR(r->status) && cid->ecb->dwHttpStatusCode) {
        r->status = cid->ecb->dwHttpStatusCode;
    }

    /* For all missing-response situations simply return the status.
     * and let the core deal respond to the client.
     */
    return r->status;
}

/**********************************************************
 *
