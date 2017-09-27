        /* we treat this as a NOP */
        return APR_SUCCESS;
    }
    s = nghttp2_session_find_stream(session->ngh2, stream->id);
    if (!s) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                      H2_STRM_MSG(stream, "lookup of nghttp2_stream failed"));
        return APR_EINVAL;
    }
    
    s_parent = nghttp2_stream_get_parent(s);
    if (s_parent) {
        nghttp2_priority_spec ps;
