@@ -483,6 +483,18 @@ void configSetCommand(redisClient *c) {
     } else if (!strcasecmp(c->argv[2]->ptr,"slowlog-max-len")) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
         server.slowlog_max_len = (unsigned)ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"loglevel")) {
+        if (!strcasecmp(o->ptr,"warning")) {
+            server.verbosity = REDIS_WARNING;
+        } else if (!strcasecmp(o->ptr,"notice")) {
+            server.verbosity = REDIS_NOTICE;
+        } else if (!strcasecmp(o->ptr,"verbose")) {
+            server.verbosity = REDIS_VERBOSE;
+        } else if (!strcasecmp(o->ptr,"debug")) {
+            server.verbosity = REDIS_DEBUG;
+        } else {
+            goto badfmt;
+        }
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
@@ -668,6 +680,20 @@ void configGetCommand(redisClient *c) {
         addReplyBulkLongLong(c,server.slowlog_max_len);
         matches++;
     }
+    if (stringmatch(pattern,"loglevel",0)) {
+        char *s;
+
+        switch(server.verbosity) {
+        case REDIS_WARNING: s = "warning"; break;
+        case REDIS_VERBOSE: s = "verbose"; break;
+        case REDIS_NOTICE: s = "notice"; break;
+        case REDIS_DEBUG: s = "debug"; break;
+        default: s = "unknown"; break; /* too harmless to panic */
+        }
+        addReplyBulkCString(c,"loglevel");
+        addReplyBulkCString(c,s);
+        matches++;
+    }
     setDeferredMultiBulkLength(c,replylen,matches*2);
 }
 