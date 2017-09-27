  * Create an already defined balancer and free up memory.
  */
 PROXY_DECLARE(apr_status_t) ap_proxy_share_balancer(proxy_balancer *balancer,
                                                     proxy_balancer_shared *shm,
                                                     int i)
 {
+    apr_status_t rv = APR_SUCCESS;
     proxy_balancer_method *lbmethod;
+    char *action = "copying";
     if (!shm || !balancer->s)
         return APR_EINVAL;
 
-    memcpy(shm, balancer->s, sizeof(proxy_balancer_shared));
-    if (balancer->s->was_malloced)
-        free(balancer->s);
+    if ((balancer->s->hash.def != shm->hash.def) ||
+        (balancer->s->hash.fnv != shm->hash.fnv)) {
+        memcpy(shm, balancer->s, sizeof(proxy_balancer_shared));
+        if (balancer->s->was_malloced)
+            free(balancer->s);
+    } else {
+        action = "re-using";
+    }
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02337)
+                 "%s shm[%d] (0x%pp) for %s", action, i, (void *)shm,
+                 balancer->s->name);
     balancer->s = shm;
     balancer->s->index = i;
     /* the below should always succeed */
     lbmethod = ap_lookup_provider(PROXY_LBMETHOD, balancer->s->lbpname, "0");
-    if (lbmethod)
+    if (lbmethod) {
         balancer->lbmethod = lbmethod;
-    return APR_SUCCESS;
+    } else {
+        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ap_server_conf, APLOGNO(02432)
+                     "Cannot find LB Method: %s", balancer->s->lbpname);
+        return APR_EINVAL;
+    }
+    if (*balancer->s->nonce == PROXY_UNSET_NONCE) {
+        char nonce[APR_UUID_FORMATTED_LENGTH + 1];
+        apr_uuid_t uuid;
+        /* Retrieve a UUID and store the nonce for the lifetime of
+         * the process.
+         */
+        apr_uuid_get(&uuid);
+        apr_uuid_format(nonce, &uuid);
+        rv = PROXY_STRNCPY(balancer->s->nonce, nonce);
+    }
+    return rv;
 }
 
 PROXY_DECLARE(apr_status_t) ap_proxy_initialize_balancer(proxy_balancer *balancer, server_rec *s, apr_pool_t *p)
 {
     apr_status_t rv = APR_SUCCESS;
     ap_slotmem_provider_t *storage = balancer->storage;
