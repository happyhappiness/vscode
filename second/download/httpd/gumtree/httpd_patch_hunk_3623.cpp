         err = ap_proxy_define_balancer(cmd->pool, &balancer, conf, path, "/", 0);
         if (err)
             return apr_pstrcat(cmd->temp_pool, "BalancerMember ", err, NULL);
     }
 
     /* Try to find existing worker */
-    worker = ap_proxy_get_worker(cmd->temp_pool, balancer, conf, de_socketfy(cmd->temp_pool, name));
+    worker = ap_proxy_get_worker(cmd->temp_pool, balancer, conf, ap_proxy_de_socketfy(cmd->temp_pool, name));
     if (!worker) {
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01147)
                      "Defining worker '%s' for balancer '%s'",
                      name, balancer->s->name);
         if ((err = ap_proxy_define_worker(cmd->pool, &worker, balancer, conf, name, 0)) != NULL)
             return apr_pstrcat(cmd->temp_pool, "BalancerMember ", err, NULL);
