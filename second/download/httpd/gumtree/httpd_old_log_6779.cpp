ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c, 
                              APLOGNO(03365)
                              "h2_proxy_session(%s): WAIT read, timeout=%fms", 
                              session->id, (float)session->wait_timeout/1000.0);