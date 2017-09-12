@@ -1498,6 +1498,15 @@ sds genRedisInfoString(char *section) {
         }
     }
 
+    /* Clusetr */
+    if (allsections || defsections || !strcasecmp(section,"cluster")) {
+        if (sections++) info = sdscat(info,"\r\n");
+        info = sdscatprintf(info,
+        "# Cluster\r\n"
+        "cluster_enabled:%d\r\n",
+        server.cluster_enabled);
+    }
+
     /* Key space */
     if (allsections || defsections || !strcasecmp(section,"keyspace")) {
         if (sections++) info = sdscat(info,"\r\n");