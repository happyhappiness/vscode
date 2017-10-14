ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03068)
                      "h2_session(%ld): sent FRAME[%s], frames=%ld/%ld (r/s)",
                      session->id, buffer, (long)session->frames_received,
                     (long)session->frames_sent);