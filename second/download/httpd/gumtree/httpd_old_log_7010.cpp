ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03069)
                  "session(%ld): sent GOAWAY, err=%d, msg=%s", 
                  session->id, error, msg? msg : "");