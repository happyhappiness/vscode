     if (APLOGrtrace5(r)) {
         ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r,
                       "Request received from client: %s",
                       ap_escape_logitem(r->pool, r->the_request));
     }
 
-    /* we've probably got something to do, ignore graceful restart requests */
-
     r->request_time = apr_time_now();
     ll = r->the_request;
     r->method = ap_getword_white(r->pool, &ll);
 
-#if 0
-/* XXX If we want to keep track of the Method, the protocol module should do
- * it.  That support isn't in the scoreboard yet.  Hopefully next week
- * sometime.   rbb */
-    ap_update_connection_status(AP_CHILD_THREAD_FROM_ID(conn->id), "Method",
-                                r->method);
-#endif
-
     uri = ap_getword_white(r->pool, &ll);
 
     /* Provide quick information about the request method as soon as known */
 
     r->method_number = ap_method_number_of(r->method);
     if (r->method_number == M_GET && r->method[0] == 'H') {
