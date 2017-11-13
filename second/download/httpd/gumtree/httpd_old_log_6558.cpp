ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                      "h2_from_h1(%d): header_only, cleanup output brigade", 
                      from_h1->stream_id);