                         }
                         return HTTP_BAD_REQUEST;
                     }
                     /* sync all timestamps */
                     bsel->wupdated = bsel->s->wupdated = nworker->s->updated = apr_time_now();
                     /* by default, all new workers are disabled */
-                    ap_proxy_set_wstatus('D', 1, nworker);
+                    ap_proxy_set_wstatus(PROXY_WORKER_DISABLED_FLAG, 1, nworker);
                 }
                 if ((rv = PROXY_GLOBAL_UNLOCK(bsel)) != APR_SUCCESS) {
                     ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01203)
                                   "%s: Unlock failed for adding worker",
                                   bsel->s->name);
                 }
