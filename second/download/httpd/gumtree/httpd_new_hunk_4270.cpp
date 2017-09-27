                    }
                    else {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
                    }
                }
                
                /* trigger window updates, stream resumes and submits */
                status = h2_mplx_dispatch_master_events(session->mplx, 
                                                        on_stream_resume,
                                                        on_stream_response, 
                                                        session);
                if (status != APR_SUCCESS) {
                    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, status, c,
                                  "h2_session(%ld): dispatch error", 
                                  session->id);
                    dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 
                                   H2_ERR_INTERNAL_ERROR, 
                                   "dispatch error");
                    break;
                }
                
                if (nghttp2_session_want_write(session->ngh2)) {
                    ap_update_child_status(session->c->sbh, SERVER_BUSY_WRITE, NULL);
                    status = h2_session_send(session);
                    if (status != APR_SUCCESS) {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 
                                       H2_ERR_INTERNAL_ERROR, "writing");
                        break;
                    }
                }
                
                if (session->have_read || session->have_written) {
                    if (session->wait_us) {
                        session->wait_us = 0;
                    }
                }
                else if (!nghttp2_session_want_write(session->ngh2)) {
                    dispatch_event(session, H2_SESSION_EV_NO_IO, 0, NULL);
