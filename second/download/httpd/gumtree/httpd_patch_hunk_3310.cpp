     apr_signal(SIGPIPE, SIG_IGN);
 #endif /* SIGPIPE */
 
 #endif
 }
 
-/*****************************************************************
- * Child process main loop.
+/*
+ * close our side of the connection
+ * Pre-condition: cs is not in any timeout queue and not in the pollset,
+ *                timeout_mutex is not locked
+ * return: 0 if connection is fully closed,
+ *         1 if connection is lingering
+ * may be called by listener or by worker thread
  */
+static int start_lingering_close(event_conn_state_t *cs)
+{
+    apr_status_t rv;
+
+    cs->c->sbh = NULL;  /* prevent scoreboard updates from the listener 
+                         * worker will loop around and set SERVER_READY soon
+                         */
 
+    if (ap_start_lingering_close(cs->c)) {
+        apr_pool_clear(cs->p);
+        ap_push_pool(worker_queue_info, cs->p);
+        return 0;
+    }
+    else {
+        apr_socket_t *csd = ap_get_conn_socket(cs->c);
+        struct timeout_queue *q;
+
+#ifdef AP_DEBUG
+        {
+            rv = apr_socket_timeout_set(csd, 0);
+            AP_DEBUG_ASSERT(rv == APR_SUCCESS);
+        }
+#else
+        apr_socket_timeout_set(csd, 0);
+#endif
+        /*
+         * If some module requested a shortened waiting period, only wait for
+         * 2s (SECONDS_TO_LINGER). This is useful for mitigating certain
+         * DoS attacks.
+         */
+        if (apr_table_get(cs->c->notes, "short-lingering-close")) {
+            cs->expiration_time =
+                apr_time_now() + apr_time_from_sec(SECONDS_TO_LINGER);
+            q = &short_linger_q;
+            cs->pub.state = CONN_STATE_LINGER_SHORT;
+        }
+        else {
+            cs->expiration_time =
+                apr_time_now() + apr_time_from_sec(MAX_SECS_TO_LINGER);
+            q = &linger_q;
+            cs->pub.state = CONN_STATE_LINGER_NORMAL;
+        }
+        apr_thread_mutex_lock(timeout_mutex);
+        TO_QUEUE_APPEND(*q, cs);
+        cs->pfd.reqevents = APR_POLLIN | APR_POLLHUP | APR_POLLERR;
+        rv = apr_pollset_add(event_pollset, &cs->pfd);
+        apr_thread_mutex_unlock(timeout_mutex);
+        if (rv != APR_SUCCESS && !APR_STATUS_IS_EEXIST(rv)) {
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
+                         "start_lingering_close: apr_pollset_add failure");
+            apr_thread_mutex_lock(timeout_mutex);
+            TO_QUEUE_REMOVE(*q, cs);
+            apr_thread_mutex_unlock(timeout_mutex);
+            apr_socket_close(cs->pfd.desc.s);
+            apr_pool_clear(cs->p);
+            ap_push_pool(worker_queue_info, cs->p);
+            return 0;
+        }
+    }
+    return 1;
+}
+
+/*
+ * forcibly close a lingering connection after the lingering period has
+ * expired
+ * Pre-condition: cs is not in any timeout queue and not in the pollset
+ * return: irrelevant (need same prototype as start_lingering_close)
+ */
+static int stop_lingering_close(event_conn_state_t *cs)
+{
+    apr_status_t rv;
+    apr_socket_t *csd = ap_get_conn_socket(cs->c);
+    ap_log_error(APLOG_MARK, APLOG_TRACE4, 0, ap_server_conf,
+                 "socket reached timeout in lingering-close state");
+    rv = apr_socket_close(csd);
+    if (rv != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf, APLOGNO(00468) "error closing socket");
+        AP_DEBUG_ASSERT(0);
+    }
+    apr_pool_clear(cs->p);
+    ap_push_pool(worker_queue_info, cs->p);
+    return 0;
+}
+
+/*
+ * process one connection in the worker
+ * return: 1 if the connection has been completed,
+ *         0 if it is still open and waiting for some event
+ */
 static int process_socket(apr_thread_t *thd, apr_pool_t * p, apr_socket_t * sock,
-                          conn_state_t * cs, int my_child_num,
+                          event_conn_state_t * cs, int my_child_num,
                           int my_thread_num)
 {
     conn_rec *c;
-    listener_poll_type *pt;
     long conn_id = ID_FROM_CHILD_THREAD(my_child_num, my_thread_num);
     int rc;
     ap_sb_handle_t *sbh;
 
     ap_create_sb_handle(&sbh, p, my_child_num, my_thread_num);
 
     if (cs == NULL) {           /* This is a new connection */
-
-        cs = apr_pcalloc(p, sizeof(conn_state_t));
-
-        pt = apr_pcalloc(p, sizeof(*pt));
-
+        listener_poll_type *pt = apr_pcalloc(p, sizeof(*pt));
+        cs = apr_pcalloc(p, sizeof(event_conn_state_t));
         cs->bucket_alloc = apr_bucket_alloc_create(p);
         c = ap_run_create_connection(p, ap_server_conf, sock,
                                      conn_id, sbh, cs->bucket_alloc);
+        if (!c) {
+            apr_bucket_alloc_destroy(cs->bucket_alloc);
+            apr_pool_clear(p);
+            ap_push_pool(worker_queue_info, p);
+            return 1;
+        }
+        apr_atomic_inc32(&connection_count);
+        apr_pool_cleanup_register(c->pool, NULL, decrement_connection_count, apr_pool_cleanup_null);
         c->current_thread = thd;
         cs->c = c;
-        c->cs = cs;
+        c->cs = &(cs->pub);
         cs->p = p;
         cs->pfd.desc_type = APR_POLL_SOCKET;
         cs->pfd.reqevents = APR_POLLIN;
         cs->pfd.desc.s = sock;
         pt->type = PT_CSD;
-        pt->bypass_push = 1;
         pt->baton = cs;
         cs->pfd.client_data = pt;
-        APR_RING_ELEM_INIT(cs, timeout_list);
+        TO_QUEUE_ELEM_INIT(cs);
 
         ap_update_vhost_given_ip(c);
 
         rc = ap_run_pre_connection(c, sock);
         if (rc != OK && rc != DONE) {
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
-                         "process_socket: connection aborted");
+            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(00469)
+                          "process_socket: connection aborted");
             c->aborted = 1;
         }
 
         /**
          * XXX If the platform does not have a usable way of bundling
          * accept() with a socket readability check, like Win32,
