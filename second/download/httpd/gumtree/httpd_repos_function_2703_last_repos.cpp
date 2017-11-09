static void transit(h2_proxy_session *session, const char *action, 
                    h2_proxys_state nstate)
{
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03345)
                  "h2_proxy_session(%s): transit [%s] -- %s --> [%s]", session->id,
                  state_name(session->state), action, state_name(nstate));
    session->state = nstate;
}