             * Calling ap_save_brigade with NULL as filter is OK, because
             * bb brigade already has been created and does not need to get
             * created by ap_save_brigade.
             */
            status = ap_save_brigade(NULL, &bb, &input_brigade, p);
            if (status != APR_SUCCESS) {
                return HTTP_INTERNAL_SERVER_ERROR;
            }

            header_brigade = NULL;
        }
        else {
            bb = input_brigade;
        }

        /* Once we hit EOS, we are ready to flush. */
        rv = pass_brigade(bucket_alloc, r, p_conn, origin, bb, seen_eos);
        if (rv != OK) {
            return rv ;
        }

        if (seen_eos) {
            break;
        }

        status = ap_get_brigade(r->input_filters, input_brigade,
                                AP_MODE_READBYTES, APR_BLOCK_READ,
                                HUGE_STRING_LEN);

        if (status != APR_SUCCESS) {
            return HTTP_BAD_REQUEST;
        }
    }

    if (bytes_streamed != cl_val) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "proxy: client %s given Content-Length did not match"
                     " number of body bytes read", r->connection->remote_ip);
        return HTTP_BAD_REQUEST;
    }

    if (header_brigade) {
        /* we never sent the header brigade since there was no request
         * body; send it now with the flush flag
         */
        bb = header_brigade;
        return(pass_brigade(bucket_alloc, r, p_conn, origin, bb, 1));
    }

    return OK;
}

static int spool_reqbody_cl(apr_pool_t *p,
                                     request_rec *r,
                                     proxy_conn_rec *p_conn,
                                     conn_rec *origin,
                                     apr_bucket_brigade *header_brigade,
                                     apr_bucket_brigade *input_brigade,
                                     int force_cl)
