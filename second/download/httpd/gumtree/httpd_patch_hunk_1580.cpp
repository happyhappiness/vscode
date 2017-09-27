     if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
         ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server,
                      "Couldn't create unix domain socket");
         return errno;
     }
 
-    memset(&unix_addr, 0, sizeof(unix_addr));
-    unix_addr.sun_family = AF_UNIX;
-    apr_cpystrn(unix_addr.sun_path, sockname, sizeof unix_addr.sun_path);
-
     omask = umask(0077); /* so that only Apache can use socket */
-    rc = bind(sd, (struct sockaddr *)&unix_addr, sizeof(unix_addr));
+    rc = bind(sd, (struct sockaddr *)server_addr, server_addr_len);
     umask(omask); /* can't fail, so can't clobber errno */
     if (rc < 0) {
         ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server,
                      "Couldn't bind unix domain socket %s",
                      sockname);
         return errno;
