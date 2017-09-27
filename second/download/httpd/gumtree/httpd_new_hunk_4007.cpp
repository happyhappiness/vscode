             b = APR_BUCKET_NEXT(b))
        {
            if (AP_BUCKET_IS_EOR(b)) {
                /* FIXME: need a better test case than this.
                apr_table_setn(r->trailers_out, "X", "1"); */
                if (r->trailers_out && !apr_is_empty_table(r->trailers_out)) {
                    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, f->c, APLOGNO(03049)
                                  "h2_from_h1(%d): trailers filter, saving trailers",
                                  from_h1->stream_id);
                    h2_response_set_trailers(from_h1->response,
                                             apr_table_clone(from_h1->pool, 
                                                             r->trailers_out));
                }
