                     encoding_len++;
                     continue;
                 }
                 else {
                     /* should not be possible */
                     /* abandon malfunctioning module */
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01510)
                                 MODNAME ": bad state %d (ns)", state);
                     return DECLINED;
                 }
                 /* NOTREACHED */
             }
             /* NOTREACHED */
