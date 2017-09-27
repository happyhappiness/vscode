                  proxy_function, worker->s->hostname);
 
     (*conn)->worker = worker;
     (*conn)->close  = 0;
     (*conn)->inreslist = 0;
 
-    if (*worker->s->uds_path) {
-        if ((*conn)->uds_path == NULL) {
-            /* use (*conn)->pool instead of worker->cp->pool to match lifetime */
-            (*conn)->uds_path = apr_pstrdup((*conn)->pool, worker->s->uds_path);
-        }
-        if ((*conn)->uds_path) {
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02545)
-                         "%s: has determined UDS as %s",
-                         proxy_function, (*conn)->uds_path);
-        }
-        else {
-            /* should never happen */
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02546)
-                         "%s: cannot determine UDS (%s)",
-                         proxy_function, worker->s->uds_path);
-
-        }
-    }
-    else {
-        (*conn)->uds_path = NULL;
-    }
-
-
     return OK;
 }
 
 PROXY_DECLARE(int) ap_proxy_release_connection(const char *proxy_function,
                                                proxy_conn_rec *conn,
                                                server_rec *s)
