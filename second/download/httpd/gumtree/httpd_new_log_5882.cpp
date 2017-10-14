ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
                  "h2_stream(%ld-%d): prep_read %s, len=%ld eos=%d, trailers=%s",
                  stream->session->id, stream->id, src, (long)*plen, *peos,
                  trailers? "yes" : "no");