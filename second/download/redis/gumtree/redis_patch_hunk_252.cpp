         refreshGoodSlavesCount();
     } else if (!strcasecmp(c->argv[2]->ptr,"min-slaves-max-lag")) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
             ll < 0) goto badfmt;
         server.repl_min_slaves_max_lag = ll;
         refreshGoodSlavesCount();
+    } else if (!strcasecmp(c->argv[2]->ptr,"cluster-require-full-coverage")) {
+        int yn = yesnotoi(o->ptr);
+
+        if (yn == -1) goto badfmt;
+        server.cluster_require_full_coverage = yn;
+    } else if (!strcasecmp(c->argv[2]->ptr,"cluster-node-timeout")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
+            ll <= 0) goto badfmt;
+        server.cluster_node_timeout = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"cluster-migration-barrier")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
+            ll < 0) goto badfmt;
+        server.cluster_migration_barrier = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"cluster-slave-validity-factor")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
+            ll < 0) goto badfmt;
+        server.cluster_slave_validity_factor = ll;
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
         return;
     }
     addReply(c,shared.ok);
