                 break;
             }
             buf[bsize - 1] = 0;
             t = strchr(buf, ' ');
             if (t) {
                 ip = apr_pstrmemdup(pool, buf, t - buf);
-            } else {
+            }
+            else {
                 ip = NULL;
             }
+
             if (!ip || buf[0] == '#') {
                 /* copy things we can't process */
                 apr_file_printf(fp, "%s\n", buf);
-            } else if (strcmp(ip, s->ip) !=0 ) {
+            }
+            else if (strcmp(ip, s->ip) != 0 ) {
                 hm_server_t node;
                 apr_time_t seen;
+                const char *val;
+
                 /* Update seen time according to the last file modification */
                 apr_table_clear(hbt);
                 qs_to_table(apr_pstrdup(pool, t), hbt, pool);
-                if (apr_table_get(hbt, "busy")) {
-                    node.busy = atoi(apr_table_get(hbt, "busy"));
-                } else {
+                if ((val = apr_table_get(hbt, "busy"))) {
+                    node.busy = atoi(val);
+                }
+                else {
                     node.busy = 0;
                 }
 
-                if (apr_table_get(hbt, "ready")) {
-                    node.ready = atoi(apr_table_get(hbt, "ready"));
-                } else {
+                if ((val = apr_table_get(hbt, "ready"))) {
+                    node.ready = atoi(val);
+                }
+                else {
                     node.ready = 0;
                 }
 
-                if (apr_table_get(hbt, "lastseen")) {
-                    node.seen = atoi(apr_table_get(hbt, "lastseen"));
-                } else {
+                if ((val = apr_table_get(hbt, "lastseen"))) {
+                    node.seen = atoi(val);
+                }
+                else {
                     node.seen = SEEN_TIMEOUT;
                 }
                 seen = fage + node.seen;
 
-                if (apr_table_get(hbt, "port")) {
-                    node.port = atoi(apr_table_get(hbt, "port"));
-                } else {
+                if ((val = apr_table_get(hbt, "port"))) {
+                    node.port = atoi(val);
+                }
+                else {
                     node.port = 80;
                 }
                 apr_file_printf(fp, "%s &ready=%u&busy=%u&lastseen=%u&port=%u\n",
                                 ip, node.ready, node.busy, (unsigned int) seen, node.port);
-            } else {
+            }
+            else {
                 apr_time_t seen;
                 seen = apr_time_sec(now - s->seen);
                 apr_file_printf(fp, "%s &ready=%u&busy=%u&lastseen=%u&port=%u\n",
                                 s->ip, s->ready, s->busy, (unsigned int) seen, s->port);
                 updated = 1;
             }
