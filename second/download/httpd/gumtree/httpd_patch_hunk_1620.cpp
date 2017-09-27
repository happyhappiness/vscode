      * In addition, we make HTTP/1.1 age calculations and write them away
      * too.
      */
 
     /* Read the date. Generate one if one is not supplied */
     dates = apr_table_get(r->err_headers_out, "Date");
-    if (dates != NULL) {
-        date_in_errhdr = 1;
-    }
-    else {
+    if (dates == NULL) {
         dates = apr_table_get(r->headers_out, "Date");
     }
     if (dates != NULL) {
         info->date = apr_date_parse_http(dates);
     }
     else {
         info->date = APR_DATE_BAD;
     }
 
     now = apr_time_now();
     if (info->date == APR_DATE_BAD) {  /* No, or bad date */
-        char *dates;
         /* no date header (or bad header)! */
-        /* add one; N.B. use the time _now_ rather than when we were checking
-         * the cache
-         */
-        if (date_in_errhdr == 1) {
-            apr_table_unset(r->err_headers_out, "Date");
-        }
-        date = now;
-        dates = apr_pcalloc(r->pool, MAX_STRING_LEN);
-        apr_rfc822_date(dates, now);
-        apr_table_set(r->headers_out, "Date", dates);
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                     "cache: Added date header");
-        info->date = date;
-    }
-    else {
-        date = info->date;
+        info->date = now;
     }
+    date = info->date;
 
     /* set response_time for HTTP/1.1 age calculations */
     info->response_time = now;
 
     /* get the request time */
     info->request_time = r->request_time;
