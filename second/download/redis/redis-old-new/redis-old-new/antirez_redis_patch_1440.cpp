@@ -315,6 +315,27 @@ void loadServerConfigFromString(char *config) {
             server.slowlog_log_slower_than = strtoll(argv[1],NULL,10);
         } else if (!strcasecmp(argv[0],"slowlog-max-len") && argc == 2) {
             server.slowlog_max_len = strtoll(argv[1],NULL,10);
+        } else if (!strcasecmp(argv[0],"client-output-buffer-limit") &&
+                   argc == 5)
+        {
+            int class = getClientLimitClassByName(argv[1]);
+            unsigned long long hard, soft;
+            int soft_seconds;
+
+            if (class == -1) {
+                err = "Unrecognized client limit class";
+                goto loaderr;
+            }
+            hard = memtoll(argv[2],NULL);
+            soft = memtoll(argv[3],NULL);
+            soft_seconds = atoi(argv[4]);
+            if (soft_seconds < 0) {
+                err = "Negative number of seconds in soft limt is invalid";
+                goto loaderr;
+            }
+            server.client_obuf_limits[class].hard_limit_bytes = hard;
+            server.client_obuf_limits[class].soft_limit_bytes = soft;
+            server.client_obuf_limits[class].soft_limit_seconds = soft_seconds;
         } else {
             err = "Bad directive or wrong number of arguments"; goto loaderr;
         }
@@ -537,6 +558,53 @@ void configSetCommand(redisClient *c) {
         } else {
             goto badfmt;
         }
+    } else if (!strcasecmp(c->argv[2]->ptr,"client-output-buffer-limit")) {
+        int vlen, j;
+        sds *v = sdssplitlen(o->ptr,sdslen(o->ptr)," ",1,&vlen);
+
+        /* We need a multiple of 4: <class> <hard> <soft> <soft_seconds> */
+        if (vlen % 4) {
+            sdsfreesplitres(v,vlen);
+            goto badfmt;
+        }
+
+        /* Sanity check of single arguments, so that we either refuse the
+         * whole configuration string or accept it all, even if a single
+         * error in a single client class is present. */
+        for (j = 0; j < vlen; j++) {
+            char *eptr;
+            long val;
+
+            if ((j % 4) == 0) {
+                if (getClientLimitClassByName(v[j]) == -1) {
+                    sdsfreesplitres(v,vlen);
+                    goto badfmt;
+                }
+            } else {
+                val = strtoll(v[j], &eptr, 10);
+                if (eptr[0] != '\0' || val < 0) {
+                    sdsfreesplitres(v,vlen);
+                    goto badfmt;
+                }
+            }
+        }
+        /* Finally set the new config */
+        for (j = 0; j < vlen; j += 4) {
+            int class;
+            unsigned long long hard, soft;
+            int soft_seconds;
+
+            class = getClientLimitClassByName(v[j]);
+            hard = strtoll(v[j+1],NULL,10);
+            soft = strtoll(v[j+2],NULL,10);
+            soft_seconds = strtoll(v[j+3],NULL,10);
+
+            server.client_obuf_limits[class].hard_limit_bytes = hard;
+            server.client_obuf_limits[class].soft_limit_bytes = soft;
+            server.client_obuf_limits[class].soft_limit_seconds = soft_seconds;
+        }
+        sdsfreesplitres(v,vlen);
+
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
@@ -736,6 +804,24 @@ void configGetCommand(redisClient *c) {
         addReplyBulkCString(c,s);
         matches++;
     }
+    if (stringmatch(pattern,"client-output-buffer-limit",0)) {
+        sds buf = sdsempty();
+        int j;
+
+        for (j = 0; j < REDIS_CLIENT_LIMIT_NUM_CLASSES; j++) {
+            buf = sdscatprintf(buf,"%s %llu %llu %ld",
+                    getClientLimitClassName(j),
+                    server.client_obuf_limits[j].hard_limit_bytes,
+                    server.client_obuf_limits[j].soft_limit_bytes,
+                    (long) server.client_obuf_limits[j].soft_limit_seconds);
+            if (j != REDIS_CLIENT_LIMIT_NUM_CLASSES-1)
+                buf = sdscatlen(buf," ",1);
+        }
+        addReplyBulkCString(c,"client-output-buffer-limit");
+        addReplyBulkCString(c,buf);
+        sdsfree(buf);
+        matches++;
+    }
     setDeferredMultiBulkLength(c,replylen,matches*2);
 }
 