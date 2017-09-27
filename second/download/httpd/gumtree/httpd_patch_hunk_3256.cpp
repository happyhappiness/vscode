                        ap_default_port(r);
             else /* USE_CANONICAL_PHYS_PORT_OFF or USE_CANONICAL_PHYS_PORT_UNSET */
                 port = r->server->port ? r->server->port :
                        ap_default_port(r);
             break;
         default:
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00110)
                          "ap_get_server_port: Invalid UCN Option somehow");
             port = ap_default_port(r);
             break;
     }
 
     return port;
