     printf("%s \n", ap_get_server_description());
     set_signals();
 
     if (ap_setup_listeners(ap_server_conf) < 1) {
         ap_log_error(APLOG_MARK, APLOG_ALERT, 0, s, APLOGNO(00202)
                      "no listening sockets available, shutting down");
-        return FALSE;
+        return !OK;
     }
 
     /* Allocate a shared memory block for the array of listeners */
     for (num_listeners = 0, lr = ap_listeners; lr; lr = lr->next) {
         num_listeners++;
     }
