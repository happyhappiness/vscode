static void ping_arrived(h2_proxy_session *session)
{
    if (!h2_proxy_ihash_empty(session->streams)) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03470)
                      "h2_proxy_session(%s): ping arrived, unblocking streams",
                      session->id);
        h2_proxy_ihash_iter(session->streams, ping_arrived_iter, &session);
    }
}