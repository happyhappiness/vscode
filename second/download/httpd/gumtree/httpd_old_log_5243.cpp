ap_log_cerror( APLOG_MARK, APLOG_INFO, status, session->c,
                              APLOGNO(02950) 
                              "h2_session(%ld): error reading, terminating",
                              session->id);