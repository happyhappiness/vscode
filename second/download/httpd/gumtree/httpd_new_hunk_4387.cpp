            }
            break;
            
        case H2_PROXYS_ST_BUSY:
        case H2_PROXYS_ST_LOCAL_SHUTDOWN:
        case H2_PROXYS_ST_REMOTE_SHUTDOWN:
            have_written = send_loop(session);
            
            if (nghttp2_session_want_read(session->ngh2)) {
                status = h2_proxy_session_read(session, 0, 0);
                if (status == APR_SUCCESS) {
                    have_read = 1;
                }
