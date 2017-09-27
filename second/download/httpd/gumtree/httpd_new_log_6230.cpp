ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03202)
                                  "h2_stream(%ld-%d): PUSH BEFORE, weight=%d, "
                                  "depends=%d, returned=%d",
                                  session->id, id_parent, ps.weight, ps.stream_id, rv);