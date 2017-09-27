                 found = 1;
                 break;
             }
         }
         if (!found) {
             ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, plog,
-                          "No Listen directive found for upgradeable listener %s:%d",
-                          slu->addr, slu->port);
+                         "No Listen directive found for upgradeable listener %s:%d", slu->addr, slu->port);
         }
     }
 
-    build_cert_list(pconf);
+    build_cert_list(s->process->pool);
 
     return OK;
 }
 
 static void *nwssl_config_server_create(apr_pool_t *p, server_rec *s)
 {
