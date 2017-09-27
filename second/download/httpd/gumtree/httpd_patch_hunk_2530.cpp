     info->request_time = r->request_time;
 
     /* check last-modified date */
     if (lastmod != APR_DATE_BAD && lastmod > date) {
         /* if it's in the future, then replace by date */
         lastmod = date;
-        lastmods = dates;
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
-                     r->server,
-                     "cache: Last modified is in the future, "
-                     "replacing with now");
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0,
+                r, APLOGNO(00771) "cache: Last modified is in the future, "
+                "replacing with now");
     }
 
     /* if no expiry date then
      *   if Cache-Control: max-age
      *      expiry date = date + max-age
      *   else if lastmod
      *      expiry date = date + min((date - lastmod) * factor, maxexpire)
      *   else
      *      expire date = date + defaultexpire
      */
     if (exp == APR_DATE_BAD) {
-        char *max_age_val;
 
-        if (ap_cache_liststr(r->pool, cc_out, "max-age", &max_age_val) &&
-            max_age_val != NULL) {
+        if (control.max_age) {
             apr_int64_t x;
 
             errno = 0;
-            x = apr_atoi64(max_age_val);
+            x = control.max_age_value;
             if (errno) {
-                x = conf->defex;
+                x = dconf->defex;
             }
             else {
                 x = x * MSEC_ONE_SEC;
             }
-            if (x < conf->minex) {
-                x = conf->minex;
+            if (x < dconf->minex) {
+                x = dconf->minex;
             }
-            if (x > conf->maxex) {
-                x = conf->maxex;
+            if (x > dconf->maxex) {
+                x = dconf->maxex;
             }
             exp = date + x;
         }
         else if ((lastmod != APR_DATE_BAD) && (lastmod < date)) {
             /* if lastmod == date then you get 0*conf->factor which results in
              * an expiration time of now. This causes some problems with
              * freshness calculations, so we choose the else path...
              */
-            apr_time_t x = (apr_time_t) ((date - lastmod) * conf->factor);
+            apr_time_t x = (apr_time_t) ((date - lastmod) * dconf->factor);
 
-            if (x < conf->minex) {
-                x = conf->minex;
+            if (x < dconf->minex) {
+                x = dconf->minex;
             }
-            if (x > conf->maxex) {
-                x = conf->maxex;
+            if (x > dconf->maxex) {
+                x = dconf->maxex;
             }
             exp = date + x;
         }
         else {
-            exp = date + conf->defex;
+            exp = date + dconf->defex;
         }
     }
     info->expire = exp;
 
     /* We found a stale entry which wasn't really stale. */
     if (cache->stale_handle) {
