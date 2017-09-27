                                                   w->name, s,
                                                   wd_server_conf->pool, 0);
                         if (rv != APR_SUCCESS) {
                             return rv;
                         }
                     }
+                    ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, s, APLOGNO(02979)
+                            "Watchdog: Created child worker thread (%s).", w->name);
                     wd_server_conf->child_workers++;
                 }
             }
         }
     }
     return OK;
