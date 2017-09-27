     if (access_status == DECLINED && *balancer == NULL) {
         *worker = ap_proxy_get_worker(r->pool, NULL, conf, *url);
         if (*worker) {
             ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                           "%s: found worker %s for %s",
                           (*worker)->s->scheme, (*worker)->s->name, *url);
-
             *balancer = NULL;
+            fix_uds_filename(r, url);
             access_status = OK;
         }
         else if (r->proxyreq == PROXYREQ_PROXY) {
             if (conf->forward) {
                 ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                               "*: found forward proxy worker for %s", *url);
