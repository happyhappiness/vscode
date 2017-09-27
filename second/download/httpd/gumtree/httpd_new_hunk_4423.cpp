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
