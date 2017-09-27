 static void close_connection(struct connection * c);
 
 /* --------------------------------------------------------- */
 
 /* simple little function to write an error string and exit */
 
-static void err(char *s)
+static void err(const char *s)
 {
     fprintf(stderr, "%s\n", s);
     if (done)
         printf("Total of %d requests completed\n" , done);
     exit(1);
 }
 
 /* simple little function to write an APR error string and exit */
 
-static void apr_err(char *s, apr_status_t rv)
+static void apr_err(const char *s, apr_status_t rv)
 {
     char buf[120];
 
     fprintf(stderr,
         "%s: %s (%d)\n",
         s, apr_strerror(rv, buf, sizeof buf), rv);
     if (done)
         printf("Total of %d requests completed\n" , done);
     exit(rv);
 }
 
+static void set_polled_events(struct connection *c, apr_int16_t new_reqevents)
+{
+    apr_status_t rv;
+
+    if (c->pollfd.reqevents != new_reqevents) {
+        if (c->pollfd.reqevents != 0) {
+            rv = apr_pollset_remove(readbits, &c->pollfd);
+            if (rv != APR_SUCCESS) {
+                apr_err("apr_pollset_remove()", rv);
+            }
+        }
+
+        if (new_reqevents != 0) {
+            c->pollfd.reqevents = new_reqevents;
+            rv = apr_pollset_add(readbits, &c->pollfd);
+            if (rv != APR_SUCCESS) {
+                apr_err("apr_pollset_add()", rv);
+            }
+        }
+    }
+}
+
+static void set_conn_state(struct connection *c, connect_state_e new_state)
+{
+    apr_int16_t events_by_state[] = {
+        0,           /* for STATE_UNCONNECTED */
+        APR_POLLOUT, /* for STATE_CONNECTING */
+        APR_POLLIN,  /* for STATE_CONNECTED; we don't poll in this state,
+                      * so prepare for polling in the following state --
+                      * STATE_READ
+                      */
+        APR_POLLIN   /* for STATE_READ */
+    };
+
+    c->state = new_state;
+
+    set_polled_events(c, events_by_state[new_state]);
+}
+
 /* --------------------------------------------------------- */
 /* write out request to a connection - assumes we can write
  * (small) request out in one go into our new socket buffer
  *
  */
 #ifdef USE_SSL
