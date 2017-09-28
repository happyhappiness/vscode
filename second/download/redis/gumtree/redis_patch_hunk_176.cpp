 
     /* sentinel current-epoch is a global state valid for all the masters. */
     line = sdscatprintf(sdsempty(),
         "sentinel current-epoch %llu", (unsigned long long) sentinel.current_epoch);
     rewriteConfigRewriteLine(state,"sentinel",line,1);
 
+    /* sentinel announce-ip. */
+    if (sentinel.announce_ip) {
+        line = sdsnew("sentinel announce-ip ");
+        line = sdscatrepr(line, sentinel.announce_ip, sdslen(sentinel.announce_ip));
+        rewriteConfigRewriteLine(state,"sentinel",line,1);
+    }
+
+    /* sentinel announce-port. */
+    if (sentinel.announce_port) {
+        line = sdscatprintf(sdsempty(),"sentinel announce-port %d",
+                            sentinel.announce_port);
+        rewriteConfigRewriteLine(state,"sentinel",line,1);
+    }
+
     dictReleaseIterator(di);
 }
 
 /* This function uses the config rewriting Redis engine in order to persist
  * the state of the Sentinel in the current configuration file.
  *
