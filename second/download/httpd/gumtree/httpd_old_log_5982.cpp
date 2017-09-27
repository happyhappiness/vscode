ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                          "h2_session:  stream(%ld-%d): PRIORITY frame "
                          " weight=%d, dependsOn=%d, exclusive=%d", 
                          session->id, (int)frame->hd.stream_id,
                          frame->priority.pri_spec.weight,
                          frame->priority.pri_spec.stream_id,
                          frame->priority.pri_spec.exclusive);