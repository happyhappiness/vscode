ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
                  "h2_stream(%ld-%d): read_to, len=%ld eos=%d",
                  stream->session->id, stream->id, (long)*plen, *peos);