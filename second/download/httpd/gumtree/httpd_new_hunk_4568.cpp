                        break;
                    }
                    else {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
                    }
                }

                status = dispatch_master(session);
                if (status != APR_SUCCESS && status != APR_EAGAIN) {
                    break;
                }
                
                if (nghttp2_session_want_write(session->ngh2)) {
                    ap_update_child_status(session->c->sbh, SERVER_BUSY_WRITE, NULL);
                    status = h2_session_send(session);
                    if (status == APR_SUCCESS) {
                        status = h2_conn_io_flush(&session->io);
                    }
                    if (status != APR_SUCCESS) {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 
                                       H2_ERR_INTERNAL_ERROR, "writing");
                        break;
                    }
                }
