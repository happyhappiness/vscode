         nghttp2_option_del(option);
         nghttp2_session_callbacks_del(cbs);
 
         ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03362)
                       "setup session for %s", p_conn->hostname);
     }
+    else {
+        h2_proxy_session *session = p_conn->data;
+        apr_interval_time_t age = apr_time_now() - session->last_frame_received;
+        if (age > apr_time_from_sec(1)) {
+            session->check_ping = 1;
+            nghttp2_submit_ping(session->ngh2, 0, (const uint8_t *)"nevergonnagiveyouup");
+        }
+    }
     return p_conn->data;
 }
 
 static apr_status_t session_start(h2_proxy_session *session) 
 {
     nghttp2_settings_entry settings[2];
