 	ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                      "WARNING: Require ThreadLimit > 0, setting to 1");
 	thread_limit = 1;
     }
     return NULL;
 }
+static const char *set_disable_acceptex(cmd_parms *cmd, void *dummy, char *arg) 
+{
+    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
+    if (err != NULL) {
+        return err;
+    }
+    if (use_acceptex) {
+        use_acceptex = 0;
+        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, NULL, 
+                     "Disabled use of AcceptEx() WinSock2 API");
+    }
+    return NULL;
+}
 
 static const command_rec winnt_cmds[] = {
 LISTEN_COMMANDS,
 AP_INIT_TAKE1("ThreadsPerChild", set_threads_per_child, NULL, RSRC_CONF,
   "Number of threads each child creates" ),
 AP_INIT_TAKE1("ThreadLimit", set_thread_limit, NULL, RSRC_CONF,
   "Maximum worker threads in a server for this run of Apache"),
+AP_INIT_NO_ARGS("Win32DisableAcceptEx", set_disable_acceptex, NULL, RSRC_CONF,
+  "Disable use of the high performance AcceptEx WinSock2 API to work around buggy VPN or Firewall software"),
 { NULL }
 };
 
 
 /*
  * Signalling Apache on NT.
