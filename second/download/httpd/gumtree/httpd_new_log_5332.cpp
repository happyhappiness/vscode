ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
                  "h2_stream(%ld-%d): readx %s, len=%ld eos=%d",
                  stream->session->id, stream->id, src, (long)*plen, *peos);