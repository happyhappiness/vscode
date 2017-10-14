ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                          "h2_stream(%ld-%d): pseudo header %s too long", 
                          stream->session->id, stream->id, name);