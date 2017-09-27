                     }
                     if (inctx->block == APR_NONBLOCK_READ) {
                         break;
                     }
                     continue;  /* Blocking and nothing yet?  Try again. */
                 }
+                else if (APR_STATUS_IS_TIMEUP(inctx->rc)) {
+                    /* just return it, the calling layer might be fine with it,
+                       and we do not want to bloat the log. */
+                }
                 else {
                     ap_log_cerror(APLOG_MARK, APLOG_INFO, inctx->rc, c, APLOGNO(01991)
                                   "SSL input filter read failed.");
                 }
             }
             else /* if (ssl_err == SSL_ERROR_SSL) */ {
