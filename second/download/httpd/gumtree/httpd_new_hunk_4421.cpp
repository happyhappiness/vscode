                    }
                }
                
                /* trigger window updates, stream resumes and submits */
                status = h2_mplx_dispatch_master_events(session->mplx, 
                                                        on_stream_resume,
                                                        session);
                if (status != APR_SUCCESS) {
                    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, status, c,
                                  "h2_session(%ld): dispatch error", 
                                  session->id);
                    dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 
