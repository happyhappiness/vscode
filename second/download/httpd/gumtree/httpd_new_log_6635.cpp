ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
                  "h2_stream(%ld-%d): unpexected header status %d, stream rst", 
                  session->id, stream->id, headers->status);