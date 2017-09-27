 
 AP_DECLARE(int) unixd_setup_child(void)
 {
     if (set_group_privs()) {
         return -1;
     }
+
+    if (NULL != unixd_config.chroot_dir) {
+        if (geteuid()) {
+            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
+                         "Cannot chroot when not started as root");
+            return -1;
+        }
+        if (chdir(unixd_config.chroot_dir) != 0) {
+            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
+                         "Can't chdir to %s", unixd_config.chroot_dir);
+            return -1;
+        }
+        if (chroot(unixd_config.chroot_dir) != 0) {
+            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
+                         "Can't chroot to %s", unixd_config.chroot_dir);
+            return -1;
+        }
+        if (chdir("/") != 0) {
+            ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
+                         "Can't chdir to new root");
+            return -1;
+        }
+    }
+
 #ifdef MPE
     /* Only try to switch if we're running as MANAGER.SYS */
     if (geteuid() == 1 && unixd_config.user_id > 1) {
         GETPRIVMODE();
         if (setuid(unixd_config.user_id) == -1) {
             GETUSERMODE();
