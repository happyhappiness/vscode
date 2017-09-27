                               h2_proxy_request_done *done)
 {
     if (!h2_proxy_ihash_empty(session->streams)) {
         cleanup_iter_ctx ctx;
         ctx.session = session;
         ctx.done = done;
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03366)
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03519)
                       "h2_proxy_session(%s): terminated, %d streams unfinished",
                       session->id, (int)h2_proxy_ihash_count(session->streams));
         h2_proxy_ihash_iter(session->streams, done_iter, &ctx);
         h2_proxy_ihash_clear(session->streams);
     }
 }
