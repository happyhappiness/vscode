     ap_listen_rec *lr;
     parent_info_t *parent_info;
     char *listener_shm_name;
     int listener_num, num_listeners, slot;
     ULONG rc;
 
-    printf("%s \n", ap_get_server_version());
+    printf("%s \n", ap_get_server_description());
     set_signals();
 
     if (ap_setup_listeners(ap_server_conf) < 1) {
         ap_log_error(APLOG_MARK, APLOG_ALERT, 0, s,
                      "no listening sockets available, shutting down");
         return FALSE;
