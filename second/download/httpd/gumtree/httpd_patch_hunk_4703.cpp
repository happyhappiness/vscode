                       m->id, (int)h2_ihash_count(m->shold));
         h2_ihash_iter(m->shold, unexpected_stream_iter, m);
     }
     
     H2_MPLX_LEAVE(m);
 
-    /* 5. unregister again, now that our workers are done */
-    h2_workers_unregister(m->workers, m);
-
     ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                   "h2_mplx(%ld): released", m->id);
 }
 
 apr_status_t h2_mplx_stream_cleanup(h2_mplx *m, h2_stream *stream)
 {
