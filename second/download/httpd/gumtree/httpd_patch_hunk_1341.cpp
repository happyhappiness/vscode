             "proxy: BALANCER: (%s). Unlock failed for post_request",
             balancer->name);
     }
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                  "proxy_balancer_post_request for (%s)", balancer->name);
 
-    if (worker && worker->s->busy)
-        worker->s->busy--;
-
     return OK;
-
 }
 
 static void recalc_factors(proxy_balancer *balancer)
 {
     int i;
     proxy_worker *workers;
