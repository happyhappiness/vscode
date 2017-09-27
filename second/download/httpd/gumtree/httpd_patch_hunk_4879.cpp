             /* now go thru each worker */
             workers = (proxy_worker **)balancer->workers->elts;
             for (j = 0; j < balancer->workers->nelts; j++, workers++) {
                 proxy_worker_shared *shm;
 
                 worker = *workers;
-                if ((rv = storage->grab(balancer->wslot, &index)) != APR_SUCCESS) {
-                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01186) "worker slotmem_grab failed");
-                    return !OK;
 
+                shm = ap_proxy_find_workershm(storage, balancer->wslot, worker, &index);
+                if (shm) {
+                    if ((rv = storage->fgrab(balancer->wslot, index)) != APR_SUCCESS) {
+                        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(02409) "worker slotmem_fgrab failed");
+                        return !OK;
+                    }
                 }
-                if ((rv = storage->dptr(balancer->wslot, index, (void *)&shm)) != APR_SUCCESS) {
-                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01187) "worker slotmem_dptr failed");
-                    return !OK;
+                else {
+                    if ((rv = storage->grab(balancer->wslot, &index)) != APR_SUCCESS) {
+                        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01186) "worker slotmem_grab failed");
+                        return !OK;
+
+                    }
+                    if ((rv = storage->dptr(balancer->wslot, index, (void *)&shm)) != APR_SUCCESS) {
+                        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01187) "worker slotmem_dptr failed");
+                        return !OK;
+                    }
                 }
                 if ((rv = ap_proxy_share_worker(worker, shm, index)) != APR_SUCCESS) {
                     ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01188) "Cannot share worker");
                     return !OK;
                 }
                 worker->s->updated = tstamp;
             }
+            if (conf->bal_persist) {
+                /* We could have just read-in a persisted config. Force a sync. */
+                balancer->wupdated--;
+                ap_proxy_sync_balancer(balancer, s, conf);
+            }
         }
         s = s->next;
     }
 
     return OK;
 }
