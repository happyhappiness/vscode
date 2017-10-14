void h2_proxy_session_cancel_all(h2_proxy_session *session)
{
    if (!h2_proxy_ihash_empty(session->streams)) {
        cleanup_iter_ctx ctx;
        ctx.session = session;
        ctx.done = session->done;
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03366)
                      "h2_proxy_session(%s): cancel  %d streams",
                      session->id, (int)h2_proxy_ihash_count(session->streams));
        h2_proxy_ihash_iter(session->streams, cancel_iter, &ctx);
        session_shutdown(session, 0, NULL);
    }
}