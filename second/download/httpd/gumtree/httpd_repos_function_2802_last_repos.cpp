void h2_session_event(h2_session *session, h2_session_event_t ev, 
                             int err, const char *msg)
{
    dispatch_event(session, ev, err, msg);
}