ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03487) 
                              "h2_proxy_session(%s): got interim HEADERS, "
                              "status=%d, will forward=%d",
                              session->id, r->status, forward);