 
 #ifdef TPF
 int tpf_child = 0;
 char tpf_server_name[INETD_SERVNAME_LENGTH+1];
 #endif /* TPF */
 
-static int die_now = 0;
+static volatile int die_now = 0;
 
 #ifdef GPROF
-/* 
+/*
  * change directory for gprof to plop the gmon.out file
  * configure in httpd.conf:
  * GprofDir $RuntimeDir/   -> $ServerRoot/$RuntimeDir/gmon.out
  * GprofDir $RuntimeDir/%  -> $ServerRoot/$RuntimeDir/gprof.$pid/gmon.out
  */
 static void chdir_for_gprof(void)
 {
-    core_server_config *sconf = 
-	ap_get_module_config(ap_server_conf->module_config, &core_module);    
+    core_server_config *sconf =
+        ap_get_module_config(ap_server_conf->module_config, &core_module);
     char *dir = sconf->gprof_dir;
     const char *use_dir;
 
     if(dir) {
         apr_status_t res;
-	char buf[512];
+        char *buf = NULL ;
 	int len = strlen(sconf->gprof_dir) - 1;
 	if(*(dir + len) == '%') {
 	    dir[len] = '\0';
-	    apr_snprintf(buf, sizeof(buf), "%sgprof.%d", dir, (int)getpid());
-	} 
-	use_dir = ap_server_root_relative(pconf, buf[0] ? buf : dir);
-	res = apr_dir_make(use_dir, 0755, pconf);
+            buf = ap_append_pid(pconf, dir, "gprof.");
+        }
+        use_dir = ap_server_root_relative(pconf, buf ? buf : dir);
+        res = apr_dir_make(use_dir,
+                           APR_UREAD | APR_UWRITE | APR_UEXECUTE |
+                           APR_GREAD | APR_GEXECUTE |
+                           APR_WREAD | APR_WEXECUTE, pconf);
 	if(res != APR_SUCCESS && !APR_STATUS_IS_EEXIST(res)) {
-	    ap_log_error(APLOG_MARK, APLOG_ERR, errno, ap_server_conf,
+            ap_log_error(APLOG_MARK, APLOG_ERR, res, ap_server_conf,
 			 "gprof: error creating directory %s", dir);
 	}
     }
     else {
 	use_dir = ap_server_root_relative(pconf, DEFAULT_REL_RUNTIMEDIR);
     }
