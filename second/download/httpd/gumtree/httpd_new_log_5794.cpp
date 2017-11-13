ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, f->c,
                                  "h2_from_h1(%d): trailers filter, saving trailers",
                                  from_h1->stream_id);