ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_session:  stream(%ld-%d): on_data_chunk for unknown stream",
                      session->id, (int)stream_id);