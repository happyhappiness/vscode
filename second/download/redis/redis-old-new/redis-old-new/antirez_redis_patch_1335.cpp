@@ -2042,7 +2042,7 @@ sds genRedisInfoString(char *section) {
         }
     }
 
-    /* Clusetr */
+    /* Cluster */
     if (allsections || defsections || !strcasecmp(section,"cluster")) {
         if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,