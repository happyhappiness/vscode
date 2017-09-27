}


void h2_proxy_session_update_window(h2_proxy_session *session, 
                                    conn_rec *c, apr_off_t bytes)
{
    if (session->streams && !h2_ihash_empty(session->streams)) {
        win_update_ctx ctx;
        ctx.session = session;
        ctx.c = c;
        ctx.bytes = bytes;
        ctx.updated = 0;
        h2_ihash_iter(session->streams, win_update_iter, &ctx);
        
        if (!ctx.updated) {
            /* could not find the stream any more, possibly closed, update
             * the connection window at least */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 
                          "h2_proxy_session(%s): win_update conn %ld bytes",
