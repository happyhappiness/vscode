         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                     "internal error: bad expires code: %s", r->filename);
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
     expires = base + additional;
+    if (expires < r->request_time) {
+        expires = r->request_time;
+    }
     apr_table_mergen(t, "Cache-Control",
                      apr_psprintf(r->pool, "max-age=%" APR_TIME_T_FMT,
                                   apr_time_sec(expires - r->request_time)));
     timestr = apr_palloc(r->pool, APR_RFC822_DATE_LEN);
     apr_rfc822_date(timestr, expires);
     apr_table_setn(t, "Expires", timestr);
