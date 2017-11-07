ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                  "h2_stream(%ld-%d): cleanup by EOS bucket destroy", 
                  session->id, stream->id);