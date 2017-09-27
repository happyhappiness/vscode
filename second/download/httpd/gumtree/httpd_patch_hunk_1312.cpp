     *indexes = apr_array_make(r->pool, ranges, sizeof(indexes_t));
     while ((cur = ap_getword(r->pool, &range, ','))) {
         char *dash;
         char *errp;
         apr_off_t number, start, end;
 
-        if (!(dash = strchr(cur, '-'))) {
+        if (!*cur)
             break;
+
+        /*
+         * Per RFC 2616 14.35.1: If there is at least one syntactically invalid
+         * byte-range-spec, we must ignore the whole header.
+         */
+
+        if (!(dash = strchr(cur, '-'))) {
+            return 0;
         }
 
-        if (dash == range) {
+        if (dash == cur) {
             /* In the form "-5" */
             if (apr_strtoff(&number, dash+1, &errp, 10) || *errp) {
-                break;
+                return 0;
+            }
+            if (number < 1) {
+                return 0;
             }
             start = clength - number;
             end = clength - 1;
         }
         else {
             *dash++ = '\0';
             if (apr_strtoff(&number, cur, &errp, 10) || *errp) {
-                break;
+                return 0;
             }
             start = number;
             if (*dash) {
                 if (apr_strtoff(&number, dash, &errp, 10) || *errp) {
-                    break;
+                    return 0;
                 }
                 end = number;
+                if (start > end) {
+                    return 0;
+                }
             }
             else {                  /* "5-" */
                 end = clength - 1;
             }
         }
 
         if (start < 0) {
             start = 0;
         }
+        if (start >= clength) {
+            unsatisfiable = 1;
+            continue;
+        }
         if (end >= clength) {
             end = clength - 1;
         }
 
-        if (start > end) {
-            /* ignore? count? */
-            break;
-        }
-
         idx = (indexes_t *)apr_array_push(*indexes);
         idx->start = start;
         idx->end = end;
         sum_lengths += end - start + 1;
         /* new set again */
         num_ranges++;
     }
 
+    if (num_ranges == 0 && unsatisfiable) {
+        /* If all ranges are unsatisfiable, we should return 416 */
+        return -1;
+    }
     if (sum_lengths >= clength) {
         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                       "Sum of ranges not smaller than file, ignoring.");
         return 0;
     }
 
