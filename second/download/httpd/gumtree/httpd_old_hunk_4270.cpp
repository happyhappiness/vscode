                    }
                    else {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
                    }
                }
                
                if (!h2_ihash_is_empty(session->streams)) {
                    /* resume any streams for which data is available again */
                    h2_session_resume_streams_with_data(session);
                    /* Submit any responses/push_promises that are ready */
                    status = h2_session_submit(session);
                    if (status == APR_SUCCESS) {
                        have_written = 1;
                    }
                    else if (status != APR_EAGAIN) {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 
                                         H2_ERR_INTERNAL_ERROR, "submit error");
                        break;
                    }
                    /* send out window updates for our inputs */
                    status = h2_mplx_in_update_windows(session->mplx);
                    if (status != APR_SUCCESS && status != APR_EAGAIN) {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 
                                         H2_ERR_INTERNAL_ERROR, "window update error");
                        break;
                    }
                }
                
                if (nghttp2_session_want_write(session->ngh2)) {
                    ap_update_child_status(session->c->sbh, SERVER_BUSY_WRITE, NULL);
                    status = h2_session_send(session);
                    if (status == APR_SUCCESS) {
                        have_written = 1;
                    }
                    else {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 
                                         H2_ERR_INTERNAL_ERROR, "writing");
                        break;
                    }
                }
                
                if (have_read || have_written) {
                    if (session->wait_us) {
                        session->wait_us = 0;
                    }
                }
                else if (!nghttp2_session_want_write(session->ngh2)) {
                    dispatch_event(session, H2_SESSION_EV_NO_IO, 0, NULL);
