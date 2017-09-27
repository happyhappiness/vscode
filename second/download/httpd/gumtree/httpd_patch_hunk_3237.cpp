         /* Make user name all upper case - for some versions of ufork() */
         ap_str_toupper(username);
 
         pid = ufork(username);
         if (pid == -1 && errno == EPERM) {
             ap_log_error(APLOG_MARK, APLOG_EMERG, errno,
-                         NULL, "ufork: Possible mis-configuration "
+                         ap_server_conf, APLOGNO(02171) "ufork: Possible mis-configuration "
                          "for user %s - Aborting.", user);
             exit(1);
         }
         break;
 
       default:
