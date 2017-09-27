             }
 
             apr_pool_cleanup_register(pconf, (void *)s, lock_remove,
                                       apr_pool_cleanup_null);
 
             /* setup shm for balancers */
-            if ((rv = storage->grab(conf->bslot, &index)) != APR_SUCCESS) {
-                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01181) "balancer slotmem_grab failed");
-                return !OK;
-
+            bshm = ap_proxy_find_balancershm(storage, conf->bslot, balancer, &index);
+            if (bshm) {
+                if ((rv = storage->fgrab(conf->bslot, index)) != APR_SUCCESS) {
+                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(02408) "balancer slotmem_fgrab failed");
+                    return !OK;
+                }
             }
-            if ((rv = storage->dptr(conf->bslot, index, (void *)&bshm)) != APR_SUCCESS) {
-                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01182) "balancer slotmem_dptr failed");
-                return !OK;
+            else {
+                if ((rv = storage->grab(conf->bslot, &index)) != APR_SUCCESS) {
+                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01181) "balancer slotmem_grab failed");
+                    return !OK;
+                }
+                if ((rv = storage->dptr(conf->bslot, index, (void *)&bshm)) != APR_SUCCESS) {
+                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01182) "balancer slotmem_dptr failed");
+                    return !OK;
+                }
             }
             if ((rv = ap_proxy_share_balancer(balancer, bshm, index)) != APR_SUCCESS) {
                 ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01183) "Cannot share balancer");
                 return !OK;
             }
 
             /* create slotmem slots for workers */
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01184) "Doing workers create: %s (%s), %d, %d",
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01184) "Doing workers create: %s (%s), %d, %d [%u]",
                          balancer->s->name, balancer->s->sname,
                          (int)ALIGNED_PROXY_WORKER_SHARED_SIZE,
-                         (int)balancer->max_workers);
+                         (int)balancer->max_workers, i);
 
             rv = storage->create(&new, balancer->s->sname,
                                  ALIGNED_PROXY_WORKER_SHARED_SIZE,
-                                 balancer->max_workers, AP_SLOTMEM_TYPE_PREGRAB, pconf);
+                                 balancer->max_workers, type, pconf);
             if (rv != APR_SUCCESS) {
                 ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01185) "worker slotmem_create failed");
                 return !OK;
             }
             balancer->wslot = new;
             balancer->storage = storage;
