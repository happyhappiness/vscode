     }
 
     return APR_SUCCESS;
 }
 #endif
 
-#if PROXY_HAS_SCOREBOARD
-PROXY_DECLARE(void*) ap_proxy_set_scoreboard_lb(proxy_worker *worker,
-                                                proxy_balancer *balancer,
-                                                server_rec *server)
-{
-    if (ap_scoreboard_image && !worker->s) {
-        server_rec *id_server;
-        int i = 0;
-        proxy_worker_stat *free_slot = NULL;
-        proxy_worker_stat *s;
-        unsigned char digest[APR_MD5_DIGESTSIZE];
-        apr_md5_ctx_t ctx;
-
-        /* The scoreboard entry must be unique per server and balancer,
-         * so when asked to (given by the caller) use their respective
-         * unique identifiers for the hash.
-         */
-        apr_md5_init(&ctx);
-        apr_md5_update(&ctx, (unsigned char *)worker->name,
-                       strlen(worker->name));
-        if (balancer) {
-            apr_md5_update(&ctx, (unsigned char *)balancer->name,
-                           strlen(balancer->name));
-        }
-        if (worker->server) {
-            id_server = worker->server;
-        }
-        else {
-            id_server = server;
-        }
-        if (id_server) {
-            server_addr_rec *addr;
-            /* Assumes the unique identifier of a vhost is its address(es)
-             * plus the ServerName:Port. Should two or more vhosts have this
-             * same identifier, the first one would always be elected to
-             * handle the requests, so this shouldn't be an issue...
-             */
-            for (addr = id_server->addrs; addr; addr = addr->next) {
-                char host_ip[64]; /* for any IPv[46] string */
-                apr_sockaddr_ip_getbuf(host_ip, sizeof host_ip,
-                                       addr->host_addr);
-                apr_md5_update(&ctx, (unsigned char *)host_ip,
-                               strlen(host_ip));
-                apr_md5_update(&ctx, (unsigned char *)&addr->host_port,
-                               sizeof(addr->host_port));
-            }
-            apr_md5_update(&ctx, (unsigned char *)id_server->server_hostname,
-                           strlen(id_server->server_hostname));
-            apr_md5_update(&ctx, (unsigned char *)&id_server->port,
-                           sizeof(id_server->port));
-        }
-        apr_md5_final(digest, &ctx);
-
-        /* Try to find out the right shared memory according to the hash */
-        while ((s = (proxy_worker_stat *)ap_get_scoreboard_lb(i++)) != NULL) {
-            if ((s->status & PROXY_WORKER_INITIALIZED) == 0) {
-                if (free_slot == NULL) {
-                    free_slot = s;
-                }
-                continue;
-            }
-            if (memcmp(s->digest, digest, APR_MD5_DIGESTSIZE) == 0) {
-                worker->s = s;
-                return s;
-            }
-        }
-
-        /* We failed to find out shared memory, so just use a free slot (if any) */
-        if (free_slot) {
-            memcpy(free_slot->digest, digest, APR_MD5_DIGESTSIZE);
-            worker->s = free_slot;
-        }
-    }
-    return worker->s;
-}
-#endif
-
 /*
  * ap_proxy_initialize_worker_share() concerns itself
  * with initializing those parts of worker which
  * are, or could be, shared. Basically worker->s
  */
 PROXY_DECLARE(void) ap_proxy_initialize_worker_share(proxy_server_conf *conf,
                                                      proxy_worker *worker,
                                                      server_rec *s)
 {
-    void *score = NULL;
+    proxy_worker_stat *score = NULL;
 
     if (PROXY_WORKER_IS_INITIALIZED(worker)) {
         /* The worker share is already initialized */
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-              "proxy: worker %s already initialized",
-              worker->name);
+        ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
+                     "proxy: worker %s already initialized",
+                     worker->name);
         return;
     }
-#if PROXY_HAS_SCOREBOARD
-    /* Get scoreboard slot */
-    if (ap_scoreboard_image) {
-        if (!ap_proxy_set_scoreboard_lb(worker, NULL, s)) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
-                  "proxy: ap_proxy_set_scoreboard_lb(%d) failed in child %" APR_PID_T_FMT " for worker %s",
-                  worker->id, getpid(), worker->name);
+    if (!worker->s) {
+        /* Get scoreboard slot */
+        if (ap_scoreboard_image) {
+            score = (proxy_worker_stat *) ap_get_scoreboard_lb(worker->id);
+            if (!score) {
+                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+                      "proxy: ap_get_scoreboard_lb(%d) failed in child %" APR_PID_T_FMT " for worker %s",
+                      worker->id, getpid(), worker->name);
+            }
+            else {
+                 ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
+                      "proxy: grabbed scoreboard slot %d in child %" APR_PID_T_FMT " for worker %s",
+                      worker->id, getpid(), worker->name);
+            }
         }
-        else {
-             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-                  "proxy: grabbed scoreboard slot %d in child %" APR_PID_T_FMT " for worker %s",
-                  worker->id, getpid(), worker->name);
-             score = worker->s;
+        if (!score) {
+            score = (proxy_worker_stat *) apr_pcalloc(conf->pool, sizeof(proxy_worker_stat));
+            ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
+                  "proxy: initialized plain memory in child %" APR_PID_T_FMT " for worker %s",
+                  getpid(), worker->name);
+        }
+        worker->s = score;
+        /*
+         * recheck to see if we've already been here. Possible
+         * if proxy is using scoreboard to hold shared stats
+         */
+        if (PROXY_WORKER_IS_INITIALIZED(worker)) {
+            /* The worker share is already initialized */
+            ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
+                         "proxy: worker %s already initialized",
+                         worker->name);
+            return;
         }
-    }
-#endif
-    if (!score) {
-        score = apr_pcalloc(conf->pool, sizeof(proxy_worker_stat));
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-              "proxy: initialized plain memory in child %" APR_PID_T_FMT " for worker %s",
-              getpid(), worker->name);
-        worker->s = (proxy_worker_stat *)score;
-    }
-    /*
-     * recheck to see if we've already been here. Possible
-     * if proxy is using scoreboard to hold shared stats
-     */
-    if (PROXY_WORKER_IS_INITIALIZED(worker)) {
-        /* The worker share is already initialized */
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-              "proxy: worker %s already initialized",
-              worker->name);
-        return;
     }
     if (worker->route) {
         strcpy(worker->s->route, worker->route);
     }
     else {
         *worker->s->route = '\0';
