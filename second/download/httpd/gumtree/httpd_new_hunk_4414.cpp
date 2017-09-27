        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                      "h2_session(%ld): feeding %ld bytes to nghttp2",
                      session->id, (long)len);
        n = nghttp2_session_mem_recv(session->ngh2, (const uint8_t *)data, len);
        if (n < 0) {
            if (nghttp2_is_fatal((int)n)) {
                dispatch_event(session, H2_SESSION_EV_PROTO_ERROR, (int)n, nghttp2_strerror((int)n));
                return APR_EGENERAL;
            }
        }
        else {
            *readlen = n;
            session->io.bytes_read += n;
