         }
     }
     
     if (eb) {
         int st = eb->status;
         apr_brigade_cleanup(bb);
-        ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, f->c,
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, f->c,
                       "h2_from_h1(%d): err bucket status=%d", 
                       from_h1->stream_id, st);
         ap_die(st, r);
         return AP_FILTER_ERROR;
     }
     
