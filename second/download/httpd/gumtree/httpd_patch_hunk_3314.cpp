         if (ep->when > te->when) {
             inserted = 1;
             APR_RING_INSERT_BEFORE(ep, te, link);
             break;
         }
     }
-    
+
     if (!inserted) {
         APR_RING_INSERT_TAIL(&timer_ring, te, timer_event_t, link);
     }
 
     apr_thread_mutex_unlock(g_timer_ring_mtx);
 
     return APR_SUCCESS;
 }
 
+/*
+ * Close socket and clean up if remote closed its end while we were in
+ * lingering close.
+ * Only to be called in the listener thread;
+ * Pre-condition: cs is in one of the linger queues and in the pollset
+ */
+static void process_lingering_close(event_conn_state_t *cs, const apr_pollfd_t *pfd)
+{
+    apr_socket_t *csd = ap_get_conn_socket(cs->c);
+    char dummybuf[2048];
+    apr_size_t nbytes;
+    apr_status_t rv;
+    struct timeout_queue *q;
+    q = (cs->pub.state == CONN_STATE_LINGER_SHORT) ?  &short_linger_q : &linger_q;
+
+    /* socket is already in non-blocking state */
+    do {
+        nbytes = sizeof(dummybuf);
+        rv = apr_socket_recv(csd, dummybuf, &nbytes);
+    } while (rv == APR_SUCCESS);
+
+    if (!APR_STATUS_IS_EOF(rv)) {
+        return;
+    }
+
+    apr_thread_mutex_lock(timeout_mutex);
+    rv = apr_pollset_remove(event_pollset, pfd);
+    AP_DEBUG_ASSERT(rv == APR_SUCCESS);
+
+    rv = apr_socket_close(csd);
+    AP_DEBUG_ASSERT(rv == APR_SUCCESS);
+
+    TO_QUEUE_REMOVE(*q, cs);
+    apr_thread_mutex_unlock(timeout_mutex);
+    TO_QUEUE_ELEM_INIT(cs);
+
+    apr_pool_clear(cs->p);
+    ap_push_pool(worker_queue_info, cs->p);
+}
+
+/* call 'func' for all elements of 'q' with timeout less than 'timeout_time'.
+ * Pre-condition: timeout_mutex must already be locked
+ * Post-condition: timeout_mutex will be locked again
+ */
+static void process_timeout_queue(struct timeout_queue *q,
+                                  apr_time_t timeout_time,
+                                  int (*func)(event_conn_state_t *))
+{
+    int count = 0;
+    event_conn_state_t *first, *cs, *last;
+    apr_status_t rv;
+    if (!q->count) {
+        return;
+    }
+    AP_DEBUG_ASSERT(!APR_RING_EMPTY(&q->head, event_conn_state_t, timeout_list));
+
+    cs = first = APR_RING_FIRST(&q->head);
+    while (cs != APR_RING_SENTINEL(&q->head, event_conn_state_t, timeout_list)
+           && cs->expiration_time < timeout_time) {
+        last = cs;
+        rv = apr_pollset_remove(event_pollset, &cs->pfd);
+        if (rv != APR_SUCCESS && !APR_STATUS_IS_NOTFOUND(rv)) {
+            ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, cs->c, APLOGNO(00473)
+                          "apr_pollset_remove failed");
+        }
+        cs = APR_RING_NEXT(cs, timeout_list);
+        count++;
+    }
+    if (!count)
+        return;
+
+    APR_RING_UNSPLICE(first, last, timeout_list);
+    AP_DEBUG_ASSERT(q->count >= count);
+    q->count -= count;
+    apr_thread_mutex_unlock(timeout_mutex);
+    while (count) {
+        cs = APR_RING_NEXT(first, timeout_list);
+        TO_QUEUE_ELEM_INIT(first);
+        func(first);
+        first = cs;
+        count--;
+    }
+    apr_thread_mutex_lock(timeout_mutex);
+}
+
 static void * APR_THREAD_FUNC listener_thread(apr_thread_t * thd, void *dummy)
 {
     timer_event_t *ep;
     timer_event_t *te;
     apr_status_t rc;
     proc_info *ti = dummy;
     int process_slot = ti->pid;
     apr_pool_t *tpool = apr_thread_pool_get(thd);
     void *csd = NULL;
     apr_pool_t *ptrans;         /* Pool for per-transaction stuff */
     ap_listen_rec *lr;
     int have_idle_worker = 0;
-    conn_state_t *cs;
+    event_conn_state_t *cs;
     const apr_pollfd_t *out_pfd;
     apr_int32_t num = 0;
-    apr_time_t time_now = 0;
     apr_interval_time_t timeout_interval;
-    apr_time_t timeout_time;
+    apr_time_t timeout_time = 0, now, last_log;
     listener_poll_type *pt;
+    int closed = 0, listeners_disabled = 0;
 
+    last_log = apr_time_now();
     free(ti);
 
     /* the following times out events that are really close in the future
      *   to prevent extra poll calls
      *
      * current value is .1 second
