     /*
      *  Create the new per-server SSL context
      */
     if (protocol == SSL_PROTOCOL_NONE) {
         ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02231)
                 "No SSL protocols available [hint: SSLProtocol]");
-        ssl_die(s);
+        return ssl_die(s);
     }
 
     cp = apr_pstrcat(p,
                      (protocol & SSL_PROTOCOL_SSLV3 ? "SSLv3, " : ""),
                      (protocol & SSL_PROTOCOL_TLSV1 ? "TLSv1, " : ""),
 #ifdef HAVE_TLSV1_X
