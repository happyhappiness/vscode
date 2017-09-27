     char id[16];
     int i;
 
     pconf = p;
 
     /* the reverse of pre_config, we want this only the first time around */
-    if (retained->module_loads == 1) {
+    if (retained->mpm->module_loads == 1) {
         startup = 1;
         level_flags |= APLOG_STARTUP;
     }
 
     if ((num_listensocks = ap_setup_listeners(ap_server_conf)) < 1) {
         ap_log_error(APLOG_MARK, APLOG_ALERT | level_flags, 0,
