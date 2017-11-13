ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                  "h2_session(%ld-%d): consumed %ld bytes",
                  session->id, stream_id, (long)bytes_read);