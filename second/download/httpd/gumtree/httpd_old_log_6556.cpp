ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, f->c,
                          "h2_from_h1(%d): eoc bucket passed", 
                          from_h1->stream_id);