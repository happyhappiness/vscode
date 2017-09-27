         if (ssl_err == SSL_ERROR_ZERO_RETURN) {
             /*
              * The case where the connection was closed before any data
              * was transferred. That's not a real error and can occur
              * sporadically with some clients.
              */
-            ap_log_cerror(APLOG_MARK, APLOG_INFO, rc, c,
+            ap_log_cerror(APLOG_MARK, APLOG_INFO, rc, c, APLOGNO(02006)
                          "SSL handshake stopped: connection was closed");
         }
         else if (ssl_err == SSL_ERROR_WANT_READ) {
             /*
              * This is in addition to what was present earlier. It is
              * borrowed from openssl_state_machine.c [mod_tls].
