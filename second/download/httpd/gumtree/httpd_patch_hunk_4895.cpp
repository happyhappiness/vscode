             (*runtime)->s = shm;
             (*runtime)->tmutex = NULL;
             if ((rv = ap_proxy_initialize_worker(*runtime, s, conf->pool)) != APR_SUCCESS) {
                 ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(00966) "Cannot init worker");
                 return rv;
             }
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02403)
+                         "grabbing shm[%d] (0x%pp) for worker: %s", i, (void *)shm,
+                         (*runtime)->s->name);
         }
     }
     if (b->s->need_reset) {
         if (b->lbmethod && b->lbmethod->reset)
             b->lbmethod->reset(b, s);
         b->s->need_reset = 0;
     }
     b->wupdated = b->s->wupdated;
     return APR_SUCCESS;
 }
 
+PROXY_DECLARE(proxy_worker_shared *) ap_proxy_find_workershm(ap_slotmem_provider_t *storage,
+                                                               ap_slotmem_instance_t *slot,
+                                                               proxy_worker *worker,
+                                                               unsigned int *index)
+{
+    proxy_worker_shared *shm;
+    unsigned int i, limit;
+    limit = storage->num_slots(slot);
+    for (i = 0; i < limit; i++) {
+        if (storage->dptr(slot, i, (void *)&shm) != APR_SUCCESS) {
+            return NULL;
+        }
+        if ((worker->s->hash.def == shm->hash.def) &&
+            (worker->s->hash.fnv == shm->hash.fnv)) {
+            *index = i;
+            return shm;
+        }
+    }
+    return NULL;
+}
+
+PROXY_DECLARE(proxy_balancer_shared *) ap_proxy_find_balancershm(ap_slotmem_provider_t *storage,
+                                                                 ap_slotmem_instance_t *slot,
+                                                                 proxy_balancer *balancer,
+                                                                 unsigned int *index)
+{
+    proxy_balancer_shared *shm;
+    unsigned int i, limit;
+    limit = storage->num_slots(slot);
+    for (i = 0; i < limit; i++) {
+        if (storage->dptr(slot, i, (void *)&shm) != APR_SUCCESS) {
+            return NULL;
+        }
+        if ((balancer->s->hash.def == shm->hash.def) &&
+            (balancer->s->hash.fnv == shm->hash.fnv)) {
+            *index = i;
+            return shm;
+        }
+    }
+    return NULL;
+}
+
 void proxy_util_register_hooks(apr_pool_t *p)
 {
     APR_REGISTER_OPTIONAL_FN(ap_proxy_retry_worker);
 }
