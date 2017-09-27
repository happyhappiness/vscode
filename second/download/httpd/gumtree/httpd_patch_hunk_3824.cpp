     }
 
     ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, s,
                  "Inter-Process Session Cache: "
                  "request=%s status=%s id=%s %s(session %s)",
                  request, status,
-                 SSL_SESSION_id2sz(id, idlen, buf, sizeof(buf)),
+                 modssl_SSL_SESSION_id2sz(id, idlen, buf, sizeof(buf)),
                  timeout_str, result);
 }
 
 /*
  *  This callback function is executed by OpenSSL whenever a new SSL_SESSION is
  *  added to the internal OpenSSL session cache. We use this hook to spread the
