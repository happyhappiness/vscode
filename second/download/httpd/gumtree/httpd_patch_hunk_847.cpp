 	GETUSERMODE();
     }
 #else
     /* Only try to switch if we're running as root */
     if (!geteuid() && (
 #ifdef _OSD_POSIX
-	os_init_job_environment(server_conf, unixd_config.user_name, one_process) != 0 || 
+        os_init_job_environment(NULL, unixd_config.user_name, ap_exists_config_define("DEBUG")) != 0 ||
 #endif
 	setuid(unixd_config.user_id) == -1)) {
 	ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
 		    "setuid: unable to change to uid: %ld",
                     (long) unixd_config.user_id);
 	return -1;
     }
-#if defined(HAVE_PRCTL) && defined(PR_SET_DUMPABLE) 
+#if defined(HAVE_PRCTL) && defined(PR_SET_DUMPABLE)
     /* this applies to Linux 2.4+ */
 #ifdef AP_MPM_WANT_SET_COREDUMPDIR
     if (ap_coredumpdir_configured) {
         if (prctl(PR_SET_DUMPABLE, 1)) {
             ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                          "set dumpable failed - this child will not coredump"
