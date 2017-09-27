            h2_mplx_reprioritize(session->mplx, stream_pri_cmp, session);
            session->reprioritize = 0;
        }
    }
    
out:
    if (trace) {
        ap_log_cerror( APLOG_MARK, APLOG_TRACE3, status, c,
                      "h2_session(%ld): [%s] process returns", 
                      session->id, state_name(session->state));
    }
    
    if ((session->state != H2_SESSION_ST_DONE)
        && (APR_STATUS_IS_EOF(status)
            || APR_STATUS_IS_ECONNRESET(status) 
            || APR_STATUS_IS_ECONNABORTED(status))) {
            dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
        }
