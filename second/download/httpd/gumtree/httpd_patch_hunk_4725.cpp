 
         child = child->next;
     }
 
     if (ret != OK) {
         ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, APR_SUCCESS, s, APLOGNO(01624)
-                     "%s",
-                     apr_pstrcat(p, (is_conf
-                                     ? "<Directory>, <Location>, or similar"
-                                     : format_authz_command(p, section)),
-                                 " directive contains only negative "
-                                 "authorization directives", NULL));
+                     "%s directive contains only negative authorization directives",
+                     is_conf ? "<Directory>, <Location>, or similar"
+                             : format_authz_command(p, section));
     }
 
     return ret;
 }
 
 static int authz_core_pre_config(apr_pool_t *p, apr_pool_t *plog,
