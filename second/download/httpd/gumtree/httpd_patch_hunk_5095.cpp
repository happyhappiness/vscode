     if (!APLOGdebug(s)) {
         return;
     }
 
     if (timeout) {
         apr_snprintf(timeout_str, sizeof(timeout_str),
-                     "timeout=%lds ", (timeout - time(NULL)));
+                     "timeout=%lds ", timeout);
     }
 
     ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, s,
                  "Inter-Process Session Cache: "
                  "request=%s status=%s id=%s %s(session %s)",
                  request, status,
