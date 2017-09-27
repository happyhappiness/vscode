 
 static int connect_to_daemon(int *sdptr, request_rec *r,
                              cgid_server_conf *conf)
 {
     int sd;
     int connect_tries;
+    int connect_errno;
     apr_interval_time_t sliding_timer;
 
     connect_tries = 0;
     sliding_timer = 100000; /* 100 milliseconds */
     while (1) {
+        connect_errno = 0;
         ++connect_tries;
         if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
             return log_scripterror(r, conf, HTTP_INTERNAL_SERVER_ERROR, errno,
                                    APLOGNO(01255) "unable to create socket to cgi daemon");
         }
         if (connect(sd, (struct sockaddr *)server_addr, server_addr_len) < 0) {
-            if (errno == ECONNREFUSED && connect_tries < DEFAULT_CONNECT_ATTEMPTS) {
+            /* Save errno for later */
+            connect_errno = errno;
+            /* ECONNREFUSED means the listen queue is full; ENOENT means that
+             * the cgid server either hasn't started up yet, or we're pointing
+             * at the wrong socket file */
+            if ((errno == ECONNREFUSED || errno == ENOENT) && 
+                 connect_tries < DEFAULT_CONNECT_ATTEMPTS) {
                 ap_log_rerror(APLOG_MARK, APLOG_DEBUG, errno, r, APLOGNO(01256)
                               "connect #%d to cgi daemon failed, sleeping before retry",
                               connect_tries);
                 close(sd);
                 apr_sleep(sliding_timer);
                 if (sliding_timer < apr_time_from_sec(2)) {
