ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, msos->m->c,
                  "h2_stream(%ld-%d): prepare, len=%ld eos=%d, trailers=%s",
                  msos->m->id, sos->stream->id, (long)*plen, *peos,
                  msos->trailers? "yes" : "no");