                if (status == APR_SUCCESS) {
                    session->wait_us = 0;
                    dispatch_event(session, H2_SESSION_EV_DATA_READ, 0, NULL);
                }
                else if (APR_STATUS_IS_TIMEUP(status)) {
                    /* go back to checking all inputs again */
                    transit(session, "wait cycle", session->local.accepting? 
                            H2_SESSION_ST_BUSY : H2_SESSION_ST_DONE);
                }
                else if (APR_STATUS_IS_ECONNRESET(status) 
                         || APR_STATUS_IS_ECONNABORTED(status)) {
                    dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
                }
                else {
                    ap_log_cerror(APLOG_MARK, APLOG_WARNING, status, c,
				  APLOGNO(03404)
                                  "h2_session(%ld): waiting on conditional",
                                  session->id);
                    h2_session_shutdown(session, H2_ERR_INTERNAL_ERROR, 
                                        "cond wait error", 0);
                }
                break;
                
            default:
                ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, c,
                              APLOGNO(03080)
                              "h2_session(%ld): unknown state %d", session->id, session->state);
                dispatch_event(session, H2_SESSION_EV_PROTO_ERROR, 0, NULL);
                break;
        }

        if (!nghttp2_session_want_read(session->ngh2) 
                 && !nghttp2_session_want_write(session->ngh2)) {
