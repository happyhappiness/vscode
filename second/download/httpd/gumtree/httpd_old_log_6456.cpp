ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, msos->m->c,
                  "h2_stream(%ld-%d): readx, len=%ld eos=%d",
                  msos->m->id, sos->stream->id, (long)*plen, *peos);