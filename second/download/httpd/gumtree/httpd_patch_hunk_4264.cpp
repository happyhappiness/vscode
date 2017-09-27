 static void h2_session_ev_no_io(h2_session *session, int arg, const char *msg)
 {
     switch (session->state) {
         case H2_SESSION_ST_BUSY:
         case H2_SESSION_ST_LOCAL_SHUTDOWN:
         case H2_SESSION_ST_REMOTE_SHUTDOWN:
-            /* nothing for input and output to do. If we remain
-             * in this state, we go into a tight loop and suck up
-             * CPU cycles. Ideally, we'd like to do a blocking read, but that
-             * is not possible if we have scheduled tasks and wait
-             * for them to produce something. */
-            if (h2_conn_io_flush(&session->io) != APR_SUCCESS) {
-                dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
-            }
-            if (h2_ihash_is_empty(session->streams)) {
-                if (!is_accepting_streams(session)) {
-                    /* We are no longer accepting new streams and have
-                     * finished processing existing ones. Time to leave. */
-                    h2_session_shutdown(session, arg, msg, 0);
-                    transit(session, "no io", H2_SESSION_ST_DONE);
+            /* Nothing to READ, nothing to WRITE on the master connection.
+             * Possible causes:
+             * - we wait for the client to send us sth
+             * - we wait for started tasks to produce output
+             * - we have finished all streams and the client has sent GO_AWAY
+             */
+            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
+                          "h2_session(%ld): NO_IO event, %d streams open", 
+                          session->id, session->open_streams);
+            if (session->open_streams > 0) {
+                if (has_unsubmitted_streams(session) 
+                    || has_suspended_streams(session)) {
+                    /* waiting for at least one stream to produce data */
+                    transit(session, "no io", H2_SESSION_ST_WAIT);
                 }
                 else {
-                    apr_time_t now = apr_time_now();
-                    /* When we have no streams, no task event are possible,
-                     * switch to blocking reads */
-                    transit(session, "no io", H2_SESSION_ST_IDLE);
-                    session->idle_until = (session->remote.emitted_count? 
-                                           session->s->keep_alive_timeout : 
-                                           session->s->timeout) + now;
-                    session->keep_sync_until = now + apr_time_from_sec(1);
+                    /* we have streams open, and all are submitted and none
+                     * is suspended. The only thing keeping us from WRITEing
+                     * more must be the flow control.
+                     * This means we only wait for WINDOW_UPDATE from the 
+                     * client and can block on READ. */
+                    transit(session, "no io (flow wait)", H2_SESSION_ST_IDLE);
+                    session->idle_until = apr_time_now() + session->s->timeout;
+                    session->keep_sync_until = session->idle_until;
+                    /* Make sure we have flushed all previously written output
+                     * so that the client will react. */
+                    if (h2_conn_io_flush(&session->io) != APR_SUCCESS) {
+                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
+                        return;
+                    }
                 }
             }
-            else if (!has_unsubmitted_streams(session)
-                     && !has_suspended_streams(session)) {
-                /* none of our streams is waiting for a response or
-                 * new output data from task processing, 
-                 * switch to blocking reads. We are probably waiting on
-                 * window updates. */
-                transit(session, "no io", H2_SESSION_ST_IDLE);
-                session->idle_until = apr_time_now() + session->s->timeout;
-                session->keep_sync_until = session->idle_until;
+            else if (is_accepting_streams(session)) {
+                /* When we have no streams, but accept new, switch to idle */
+                apr_time_t now = apr_time_now();
+                transit(session, "no io (keepalive)", H2_SESSION_ST_IDLE);
+                session->idle_until = (session->remote.emitted_count? 
+                                       session->s->keep_alive_timeout : 
+                                       session->s->timeout) + now;
+                session->keep_sync_until = now + apr_time_from_sec(1);
             }
             else {
-                /* Unable to do blocking reads, as we wait on events from
-                 * task processing in other threads. Do a busy wait with
-                 * backoff timer. */
-                transit(session, "no io", H2_SESSION_ST_WAIT);
+                /* We are no longer accepting new streams and there are
+                 * none left. Time to leave. */
+                h2_session_shutdown(session, arg, msg, 0);
+                transit(session, "no io", H2_SESSION_ST_DONE);
             }
             break;
         default:
             /* nop */
             break;
     }
