     void *sconf = r->server->module_config;
     proxy_server_conf *conf = (proxy_server_conf *)
         ap_get_module_config(sconf, &proxy_module);
     proxy_balancer *balancer = NULL;
     proxy_worker **worker = NULL;
 
-    if (flags & AP_STATUS_SHORT || conf->balancers->nelts == 0 ||
+    if ((flags & AP_STATUS_SHORT) || conf->balancers->nelts == 0 ||
         conf->proxy_status == status_off)
         return OK;
 
     balancer = (proxy_balancer *)conf->balancers->elts;
     for (i = 0; i < conf->balancers->nelts; i++) {
         ap_rputs("<hr />\n<h1>Proxy LoadBalancer Status for ", r);
