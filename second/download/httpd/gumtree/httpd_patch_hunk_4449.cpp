         (*route)++;
     if ((*route) && (**route)) {
         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01161) "Found route %s", *route);
         /* We have a route in path or in cookie
          * Find the worker that has this route defined.
          */
-        worker = find_route_worker(balancer, *route, r);
+        worker = find_route_worker(balancer, *route, r, 1);
         if (worker && strcmp(*route, worker->s->route)) {
             /*
              * Notice that the route of the worker chosen is different from
              * the route supplied by the client.
              */
             apr_table_setn(r->subprocess_env, "BALANCER_ROUTE_CHANGED", "1");
