             if (slu->port == lr->bind_addr->port) {
                 found = 1;
                 break;
             }
         }
         if (!found) {
-            ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, plog,
+            ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, plog, APLOGNO(02130)
                          "No Listen directive found for upgradeable listener %s:%d", slu->addr, slu->port);
         }
     }
 
     build_cert_list(s->process->pool);
 
