ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                                  "h2_stream(%ld-%d): PUSH BEFORE2, weight=%d, "
                                  "depends=%d, returned=%d",
                                  session->id, id_parent, ps.weight, ps.stream_id, rv);