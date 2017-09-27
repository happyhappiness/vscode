          * we have, but no longer accept new ones. Report the max stream
          * we have received and discard all new ones. */
     }
     nghttp2_submit_goaway(session->ngh2, NGHTTP2_FLAG_NONE, 
                           session->local.accepted_max, 
                           error, (uint8_t*)msg, msg? strlen(msg):0);
+    session->local.accepting = 0;
+    session->local.shutdown = 1;
     status = nghttp2_session_send(session->ngh2);
     if (status == APR_SUCCESS) {
         status = h2_conn_io_flush(&session->io);
     }
     ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03069)
                   "session(%ld): sent GOAWAY, err=%d, msg=%s", 
                   session->id, error, msg? msg : "");
     dispatch_event(session, H2_SESSION_EV_LOCAL_GOAWAY, error, msg);
     
     if (force_close) {
+        apr_brigade_cleanup(session->bbtmp);
         h2_mplx_abort(session->mplx);
     }
     
     return status;
 }
 
