         memcpy(shm, balancer->s, sizeof(proxy_balancer_shared));
         if (balancer->s->was_malloced)
             free(balancer->s);
     } else {
         action = "re-using";
     }
+    balancer->s = shm;
+    balancer->s->index = i;
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02337)
                  "%s shm[%d] (0x%pp) for %s", action, i, (void *)shm,
                  balancer->s->name);
-    balancer->s = shm;
-    balancer->s->index = i;
     /* the below should always succeed */
     lbmethod = ap_lookup_provider(PROXY_LBMETHOD, balancer->s->lbpname, "0");
     if (lbmethod) {
         balancer->lbmethod = lbmethod;
     } else {
         ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ap_server_conf, APLOGNO(02432)
