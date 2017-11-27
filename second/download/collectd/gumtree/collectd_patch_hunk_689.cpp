   for (size_t i = 0; i < values_num; i++) {
     if (isnan(values[i])) {
       if (!nan_is_error_g)
         continue;
 
       printf("CRITICAL: Data source \"%s\" is NaN\n", values_names[i]);
-      return (RET_CRITICAL);
+      return RET_CRITICAL;
     }
 
     total += values[i];
     total_num++;
   }
 
   if (total_num == 0) {
     printf("WARNING: No defined values found\n");
-    return (RET_WARNING);
+    return RET_WARNING;
   }
 
   average = total / total_num;
 
   if (match_range(&range_critical_g, average) != 0) {
     status_str = "CRITICAL";
