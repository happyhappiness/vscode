ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->m->c,
                  "h2_stream(%ld-%d): prep_read %s, len=%ld eos=%d",
                  stream->m->id, stream->id, 
                  src, (long)*plen, *peos);