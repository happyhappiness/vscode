@@ -1231,13 +1231,34 @@ void rewriteConfigRewriteLine(struct rewriteConfigState *state, char *option, sd
     sdsfree(o);
 }
 
+/* Write the long long 'bytes' value as a string in a way that is parsable
+ * inside redis.conf. If possible uses the GB, MB, KB notation. */
+int rewriteConfigFormatMemory(char *buf, size_t len, long long bytes) {
+    int gb = 1024*1024*1024;
+    int mb = 1024*1024;
+    int kb = 1024;
+
+    if (bytes && (bytes % gb) == 0) {
+        return snprintf(buf,len,"%lldgb",bytes/gb);
+    } else if (bytes && (bytes % mb) == 0) {
+        return snprintf(buf,len,"%lldmb",bytes/mb);
+    } else if (bytes && (bytes % kb) == 0) {
+        return snprintf(buf,len,"%lldkb",bytes/kb);
+    } else {
+        return snprintf(buf,len,"%lld",bytes);
+    }
+}
+
 /* Rewrite a simple "option-name <bytes>" configuration option. */
 void rewriteConfigBytesOption(struct rewriteConfigState *state, char *option, long long value, long long defvalue) {
+    char buf[64];
     int force = value != defvalue;
-    /* TODO: check if we can write it using MB, GB, or other suffixes. */
-    sds line = sdscatprintf(sdsempty(),"%s %lld",option,value);
+    sds line;
 
+    rewriteConfigFormatMemory(buf,sizeof(buf),value);
+    line = sdscatprintf(sdsempty(),"%s %s",option,buf);
     rewriteConfigRewriteLine(state,option,line,force);
+
 }
 
 /* Rewrite a yes/no option. */
@@ -1401,12 +1422,15 @@ void rewriteConfigClientoutputbufferlimitOption(struct rewriteConfigState *state
                     (server.client_obuf_limits[j].soft_limit_seconds !=
                     clientBufferLimitsDefaults[j].soft_limit_seconds);
         sds line;
+        char hard[64], soft[64];
+
+        rewriteConfigFormatMemory(hard,sizeof(hard),
+                server.client_obuf_limits[j].hard_limit_bytes);
+        rewriteConfigFormatMemory(soft,sizeof(soft),
+                server.client_obuf_limits[j].soft_limit_bytes);
 
-        line = sdscatprintf(sdsempty(),"%s %s %llu %llu %ld",
-                option,
-                getClientLimitClassName(j),
-                server.client_obuf_limits[j].hard_limit_bytes,
-                server.client_obuf_limits[j].soft_limit_bytes,
+        line = sdscatprintf(sdsempty(),"%s %s %s %s %ld",
+                option, getClientLimitClassName(j), hard, soft,
                 (long) server.client_obuf_limits[j].soft_limit_seconds);
         rewriteConfigRewriteLine(state,option,line,force);
     }