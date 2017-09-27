                 }
                 next = next->next;
             }
         }
     }
     else {
+        fbased = 0;
         fname = "none";
     }
 
     /* first try to attach to existing shared memory */
-    fbased = (name != NULL);
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02300)
+                 "create %s: %"APR_SIZE_T_FMT"/%u", fname, item_size,
+                 item_num);
     if (fbased) {
         rv = apr_shm_attach(&shm, fname, gpool);
     }
     else {
         rv = APR_EINVAL;
     }
