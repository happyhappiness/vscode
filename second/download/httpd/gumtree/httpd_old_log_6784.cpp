ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c, 
                      "h2_mplx(%ld-%d): marking stream as done.", 
                      m->id, stream->id);