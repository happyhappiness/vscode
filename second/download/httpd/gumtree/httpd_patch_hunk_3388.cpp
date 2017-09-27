 #if APR_HAVE_IPV6
     SOCKADDR_STORAGE ss_listen;
     int namelen = sizeof(ss_listen);
 #endif
     u_long zero = 0;
 
-    core_sconf = ap_get_module_config(ap_server_conf->module_config,
-                                      &core_module);
+    core_sconf = ap_get_core_module_config(ap_server_conf->module_config);
     accf_name = apr_table_get(core_sconf->accf_map, lr->protocol);
 
     if (strcmp(accf_name, "data") == 0)
         accf = 2;
     else if (strcmp(accf_name, "connect") == 0)
         accf = 1;
     else if (strcmp(accf_name, "none") == 0)
         accf = 0;
     else {
         accf = 0;
         accf_name = "none";
-        ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_netos_error(), 
-                     ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf, APLOGNO(00331)
                      "winnt_accept: unrecognized AcceptFilter '%s', "
                      "only 'data', 'connect' or 'none' are valid. "
                      "Using 'none' instead", accf_name);
     }
 
     apr_os_sock_get(&nlsd, lr->sd);
 
 #if APR_HAVE_IPV6
     if (getsockname(nlsd, (struct sockaddr *)&ss_listen, &namelen) == SOCKET_ERROR) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_netos_error(), 
-                     ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_netos_error(),
+                     ap_server_conf, APLOGNO(00332)
                      "winnt_accept: getsockname error on listening socket, "
                      "is IPv6 available?");
         return 1;
    }
 #endif
 
