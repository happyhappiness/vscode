@@ -336,6 +336,11 @@ void loadServerConfigFromString(char *config) {
             server.client_obuf_limits[class].hard_limit_bytes = hard;
             server.client_obuf_limits[class].soft_limit_bytes = soft;
             server.client_obuf_limits[class].soft_limit_seconds = soft_seconds;
+        } else if (!strcasecmp(argv[0],"stop-writes-on-bgsave-error") &&
+                   argc == 2) {
+            if ((server.stop_writes_on_bgsave_err = yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
         } else {
             err = "Bad directive or wrong number of arguments"; goto loaderr;
         }
@@ -604,7 +609,11 @@ void configSetCommand(redisClient *c) {
             server.client_obuf_limits[class].soft_limit_seconds = soft_seconds;
         }
         sdsfreesplitres(v,vlen);
+    } else if (!strcasecmp(c->argv[2]->ptr,"stop-writes-on-bgsave-error")) {
+        int yn = yesnotoi(o->ptr);
 
+        if (yn == -1) goto badfmt;
+        server.stop_writes_on_bgsave_err = yn;
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
@@ -822,6 +831,11 @@ void configGetCommand(redisClient *c) {
         sdsfree(buf);
         matches++;
     }
+    if (stringmatch(pattern,"stop-writes-on-bgsave-error",0)) {
+        addReplyBulkCString(c,"stop-writes-on-bgsave-error");
+        addReplyBulkCString(c,server.stop_writes_on_bgsave_err ? "yes" : "no");
+        matches++;
+    }
     setDeferredMultiBulkLength(c,replylen,matches*2);
 }
 