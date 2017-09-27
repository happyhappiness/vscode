 
     ap_log_cerror(APLOG_MARK, APLOG_TRACE7, 0, c,
                   "mod_dumpio: %s [%s-%s] %" APR_OFF_T_FMT " readbytes",
                   f->frec->name,
                   whichmode(mode),
                   ((block) == APR_BLOCK_READ) ? "blocking" : "nonblocking",
-                  readbytes) ;
+                  readbytes);
 
     ret = ap_get_brigade(f->next, bb, mode, block, readbytes);
 
     if (ret == APR_SUCCESS) {
         for (b = APR_BRIGADE_FIRST(bb); b != APR_BRIGADE_SENTINEL(bb); b = APR_BUCKET_NEXT(b)) {
           dumpit(f, b, ptr);
         }
-    } else {
+    }
+    else {
         ap_log_cerror(APLOG_MARK, APLOG_TRACE7, 0, c,
                       "mod_dumpio: %s - %d", f->frec->name, ret) ;
         return ret;
     }
 
     return APR_SUCCESS ;
