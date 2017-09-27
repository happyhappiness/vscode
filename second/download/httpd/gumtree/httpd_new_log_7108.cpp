ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                          "h2_stream(%ld-%d): consumed %ld bytes, window now %d/%d",
                          session->id, stream->id, (long)amount, 
                          cur_size, stream->in_window_size);