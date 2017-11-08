static void dispatch_event(h2_proxy_session *session, h2_proxys_event_t ev, 
                           int arg, const char *msg)
{
    switch (ev) {
        case H2_PROXYS_EV_INIT:
            ev_init(session, arg, msg);
            break;            
        case H2_PROXYS_EV_LOCAL_GOAWAY:
            ev_local_goaway(session, arg, msg);
            break;
        case H2_PROXYS_EV_REMOTE_GOAWAY:
            ev_remote_goaway(session, arg, msg);
            break;
        case H2_PROXYS_EV_CONN_ERROR:
            ev_conn_error(session, arg, msg);
            break;
        case H2_PROXYS_EV_PROTO_ERROR:
            ev_proto_error(session, arg, msg);
            break;
        case H2_PROXYS_EV_CONN_TIMEOUT:
            ev_conn_timeout(session, arg, msg);
            break;
        case H2_PROXYS_EV_NO_IO:
            ev_no_io(session, arg, msg);
            break;
        case H2_PROXYS_EV_STREAM_SUBMITTED:
            ev_stream_submitted(session, arg, msg);
            break;
        case H2_PROXYS_EV_STREAM_DONE:
            ev_stream_done(session, arg, msg);
            break;
        case H2_PROXYS_EV_STREAM_RESUMED:
            ev_stream_resumed(session, arg, msg);
            break;
        case H2_PROXYS_EV_DATA_READ:
            ev_data_read(session, arg, msg);
            break;
        case H2_PROXYS_EV_NGH2_DONE:
            ev_ngh2_done(session, arg, msg);
            break;
        case H2_PROXYS_EV_PRE_CLOSE:
            ev_pre_close(session, arg, msg);
            break;
        default:
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                          "h2_proxy_session(%s): unknown event %d", 
                          session->id, ev);
            break;
    }
}