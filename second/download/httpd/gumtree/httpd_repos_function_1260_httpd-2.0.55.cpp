static apr_status_t stream_reqbody_cl(apr_pool_t *p,
                                      request_rec *r,
                                      proxy_http_conn_t *p_conn,
                                      conn_rec *origin,
                                      apr_bucket_brigade *header_brigade,
                                      apr_bucket_brigade *input_brigade,
                                      const char *old_cl_val)
{
    int seen_eos = 0;
    apr_status_t status = APR_SUCCESS;
    apr_bucket_alloc_t *bucket_alloc = r->connection->bucket_alloc;
    apr_bucket_brigade *bb;
    apr_bucket *e;
    apr_off_t cl_val = 0;
    apr_off_t bytes;
    apr_off_t bytes_streamed = 0;

    if (old_cl_val) {
        add_cl(p, bucket_alloc, header_brigade, old_cl_val);
        cl_val = atol(old_cl_val);
    }
    terminate_headers(bucket_alloc, header_brigade);

    while (!APR_BUCKET_IS_EOS(APR_BRIGADE_FIRST(input_brigade)))
    {
        apr_brigade_length(input_brigade, 1, &bytes);
        bytes_streamed += bytes;

        /* If this brigade contains EOS, either stop or remove it. */
        if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(input_brigade))) {
            seen_eos = 1;

            /* We can't pass this EOS to the output_filters. */
            e = APR_BRIGADE_LAST(input_brigade);
            apr_bucket_delete(e);
        }

        /* C-L < bytes streamed?!?
         * We will error out after the body is completely
         * consumed, but we can't stream more bytes at the
         * back end since they would in part be interpreted
         * as another request!  If nothing is sent, then
         * just send nothing.
         *
         * Prevents HTTP Response Splitting.
         */
        if (bytes_streamed > cl_val)
             continue;

        if (header_brigade) {
            /* we never sent the header brigade, so go ahead and
             * take care of that now
             */
            bb = header_brigade;
            APR_BRIGADE_CONCAT(bb, input_brigade);
            header_brigade = NULL;
        }
        else {
            bb = input_brigade;
        }
        
        /* Once we hit EOS, we are ready to flush. */
        status = pass_brigade(bucket_alloc, r, p_conn, origin, bb, seen_eos);
        if (status != APR_SUCCESS) {
            return status;
        }

        if (seen_eos) {
            break;
        }

        status = ap_get_brigade(r->input_filters, input_brigade,
                                AP_MODE_READBYTES, APR_BLOCK_READ,
                                HUGE_STRING_LEN);

        if (status != APR_SUCCESS) {
            return status;
        }
    }
    
    if (bytes_streamed != cl_val) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "proxy: client %s given Content-Length did not match"
                     " number of body bytes read", r->connection->remote_ip);
        return APR_EOF;
    }

    if (header_brigade) {
        /* we never sent the header brigade since there was no request
         * body; send it now with the flush flag
         */
        bb = header_brigade;
        status = pass_brigade(bucket_alloc, r, p_conn, origin, bb, 1);
    }
    return status;
}