     }
 
     if (num_ranges == 0 && unsatisfiable) {
         /* If all ranges are unsatisfiable, we should return 416 */
         return -1;
     }
-    if (sum_lengths >= clength) {
+    if (sum_lengths > clength) {
         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                      "Sum of ranges not smaller than file, ignoring.");
+                      "Sum of ranges larger than file, ignoring.");
         return 0;
     }
 
     r->status = HTTP_PARTIAL_CONTENT;
     r->range = it;
 
