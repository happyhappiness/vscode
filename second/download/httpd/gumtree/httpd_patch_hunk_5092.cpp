              *
              * (This is usually the case when the client forces an SSL
              * renegotiation which is handled implicitly by OpenSSL.)
              */
             outctx->rc = APR_EAGAIN;
         }
+        else if (ssl_err == SSL_ERROR_WANT_READ) {
+            /*
+             * If OpenSSL wants to read during write, and we were
+             * nonblocking, set the sense explicitly to read and
+             * report as an EAGAIN.
+             *
+             * (This is usually the case when the client forces an SSL
+             * renegotiation which is handled implicitly by OpenSSL.)
+             */
+            outctx->c->cs->sense = CONN_SENSE_WANT_READ;
+            outctx->rc = APR_EAGAIN;
+        }
         else if (ssl_err == SSL_ERROR_SYSCALL) {
             ap_log_cerror(APLOG_MARK, APLOG_INFO, outctx->rc, c, APLOGNO(01993)
                           "SSL output filter write failed.");
         }
         else /* if (ssl_err == SSL_ERROR_SSL) */ {
             /*
