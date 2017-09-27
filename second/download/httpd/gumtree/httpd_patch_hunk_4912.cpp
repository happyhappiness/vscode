         ap_listeners = lr;
     }
 
     /* Open the pipe to the parent process to receive the inherited socket
      * data. The sockets have been set to listening in the parent process.
      *
-     * *** We now do this was back in winnt_rewrite_args
+     * *** We now do this way back in winnt_rewrite_args
      * pipe = GetStdHandle(STD_INPUT_HANDLE);
      */
     for (lr = ap_listeners; lr; lr = lr->next, ++lcnt) {
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00403)
                      "Child: Waiting for data for listening socket %pI",
                      lr->bind_addr);
