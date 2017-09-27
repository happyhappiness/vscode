     * we're in better shape.
     */
    if (!ctx) {
        char *token;
        const char *encoding;

        /* We have checked above that bb is not empty */
        e = APR_BRIGADE_LAST(bb);
        if (APR_BUCKET_IS_EOS(e)) {
            /*
             * If we already know the size of the response, we can skip
             * compression on responses smaller than the compression overhead.
             * However, if we compress, we must initialize deflate_out before
             * calling ap_pass_brigade() for the first time.  Otherwise the
             * headers will be sent to the client without
             * "Content-Encoding: gzip".
             */
            e = APR_BRIGADE_FIRST(bb);
            while (1) {
                apr_status_t rc;
                if (APR_BUCKET_IS_EOS(e)) {
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                                  "Not compressing very small response of %"
                                  APR_SIZE_T_FMT " bytes", len);
                    ap_remove_output_filter(f);
                    return ap_pass_brigade(f->next, bb);
                }
                if (APR_BUCKET_IS_METADATA(e)) {
                    e = APR_BUCKET_NEXT(e);
                    continue;
                }

                rc = apr_bucket_read(e, &data, &blen, APR_BLOCK_READ);
                if (rc != APR_SUCCESS)
                    return rc;
                len += blen;
                /* 50 is for Content-Encoding and Vary headers and ETag suffix */
                if (len > sizeof(gzip_header) + VALIDATION_SIZE + 50)
                    break;

                e = APR_BUCKET_NEXT(e);
            }
        }

        ctx = f->ctx = apr_pcalloc(r->pool, sizeof(*ctx));

        /*
         * Only work on main request, not subrequests,
         * that are not a 204 response with no content
         * and are not tagged with the no-gzip env variable
         * and not a partial response to a Range request.
         */
        if ((r->main != NULL) || (r->status == HTTP_NO_CONTENT) ||
            apr_table_get(r->subprocess_env, "no-gzip") ||
            apr_table_get(r->headers_out, "Content-Range")
           ) {
            if (APLOG_R_IS_LEVEL(r, APLOG_TRACE1)) {
                const char *reason =
                    (r->main != NULL)                           ? "subrequest" :
                    (r->status == HTTP_NO_CONTENT)              ? "no content" :
                    apr_table_get(r->subprocess_env, "no-gzip") ? "no-gzip" :
                    "content-range";
                ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                              "Not compressing (%s)", reason);
            }
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        /* Some browsers might have problems with content types
         * other than text/html, so set gzip-only-text/html
