                else {
                    session->wait_timeout = H2MIN(apr_time_from_msec(100), 
                                                  2*session->wait_timeout);
                }
                
                status = h2_proxy_session_read(session, 1, session->wait_timeout);
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c, 
                              APLOGNO(03365)
                              "h2_proxy_session(%s): WAIT read, timeout=%fms", 
                              session->id, (float)session->wait_timeout/1000.0);
                if (status == APR_SUCCESS) {
                    have_read = 1;
                    dispatch_event(session, H2_PROXYS_EV_DATA_READ, 0, NULL);
