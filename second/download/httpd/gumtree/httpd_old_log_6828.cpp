ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, session->c,
                      "h2_stream(%ld-%d): writing frame header",
                      session->id, (int)stream_id);