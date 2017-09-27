             }
 
             /* move to next continuation record */
             m = m->next;
         }
 #if MIME_MAGIC_DEBUG
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01535)
                     MODNAME ": matched after %d rules", rule_counter);
 #endif
         return 1;  /* all through */
     }
 #if MIME_MAGIC_DEBUG
-    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01536)
                 MODNAME ": failed after %d rules", rule_counter);
 #endif
     return 0;  /* no match at all */
 }
 
 static void mprint(request_rec *r, union VALUETYPE *p, struct magic *m)
