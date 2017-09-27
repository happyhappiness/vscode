             /* Shared memory already created for this proxy_server_conf.
              */
             s = s->next;
             continue;
         }
         if (conf->bal_persist) {
-            type = AP_SLOTMEM_TYPE_PREGRAB | AP_SLOTMEM_TYPE_PERSIST;
+            type = AP_SLOTMEM_TYPE_PERSIST;
         } else {
-            type = AP_SLOTMEM_TYPE_PREGRAB;
+            type = 0;
         }
         if (conf->balancers->nelts) {
             conf->max_balancers = conf->balancers->nelts + conf->bgrowth;
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01178) "Doing balancers create: %d, %d (%d)",
                          (int)ALIGNED_PROXY_BALANCER_SHARED_SIZE,
                          (int)conf->balancers->nelts, conf->max_balancers);
