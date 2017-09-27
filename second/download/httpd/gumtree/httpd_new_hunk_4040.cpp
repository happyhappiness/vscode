        apr_table_t *trailers = h2_stream_get_trailers(stream);
        if (trailers && !apr_is_empty_table(trailers)) {
            h2_ngheader *nh;
            int rv;
            
            nh = h2_util_ngheader_make(stream->pool, trailers);
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03072)
                          "h2_stream(%ld-%d): submit %d trailers",
                          session->id, (int)stream_id,(int) nh->nvlen);
            rv = nghttp2_submit_trailer(ng2s, stream->id, nh->nv, nh->nvlen);
            if (rv < 0) {
                nread = rv;
            }
