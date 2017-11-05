static apr_status_t handle_response(serf_request_t *request,
                                    serf_bucket_t *response,
                                    void *vbaton,
                                    apr_pool_t *pool)
{
    apr_status_t rv;
    s_baton_t *ctx = vbaton;
    const char *data;
    apr_size_t len;
    serf_status_line sl;

    if (response == NULL) {
        ctx->rstatus = HTTP_INTERNAL_SERVER_ERROR;
        return APR_EGENERAL;
    }

    /* XXXXXXX: Create better error message. */
    rv = serf_bucket_response_status(response, &sl);
    if (rv) {
        if (APR_STATUS_IS_EAGAIN(rv)) {
            return APR_SUCCESS;
        }

        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, ctx->r, "serf_bucket_response_status...");

        ctx->rstatus = HTTP_INTERNAL_SERVER_ERROR;

        if (mpm_supprts_serf) {
            ap_mpm_register_timed_callback(apr_time_from_msec(1),
                                           timed_cleanup_callback, ctx);
        }

        return rv;
    }
    
    /**
     * XXXXX: If I understood serf buckets better, it might be possible to not 
     * copy all of the data here, and better stream it to the client.
     **/

    do {
        apr_brigade_cleanup(ctx->tmpbb);
        rv = serf_bucket_read(response, AP_IOBUFSIZE, &data, &len);

        if (SERF_BUCKET_READ_ERROR(rv)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, ctx->r, "serf_bucket_read(response)");
            return rv;
        }

        if (!ctx->done_headers) {
            serf_bucket_t *hdrs;
            serf_status_line line;

            /* TODO: improve */
            serf_bucket_response_status(response, &line);
            ctx->r->status = line.code;
            
            hdrs = serf_bucket_response_get_headers(response);
            serf_bucket_headers_do(hdrs, copy_headers_out, ctx);
            ctx->done_headers = 1;
        }


        if (len > 0) {
            /* TODO: make APR bucket <-> serf bucket stuff more magical. */
            apr_brigade_write(ctx->tmpbb, NULL, NULL, data, len);
        }

        if (APR_STATUS_IS_EOF(rv)) {
            ctx->keep_reading = 0;

            ctx->rstatus = ap_pass_brigade(ctx->r->output_filters, ctx->tmpbb);

            if (mpm_supprts_serf) {
                ap_mpm_register_timed_callback(apr_time_from_msec(1),
                                               timed_cleanup_callback, ctx);
            }
            return APR_EOF;
        }

        ctx->rstatus = ap_pass_brigade(ctx->r->output_filters, ctx->tmpbb);

        /* XXXX: Should we send a flush now? */
        if (APR_STATUS_IS_EAGAIN(rv)) {
            return APR_SUCCESS;
        }

    } while (1);
}