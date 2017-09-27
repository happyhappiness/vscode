     if (s == NULL) {
         return s;
     }
 
     init_config_globals(p);
 
+    if (ap_exists_config_define("DUMP_INCLUDES")) {
+        apr_file_t *out = NULL;
+        apr_file_open_stdout(&out, p);
+
+        /* Included files will be dumped as the config is walked; print a
+         * header.
+         */
+        apr_file_printf(out, "Included configuration files:\n");
+    }
+
     /* All server-wide config files now have the SAME syntax... */
     error = process_command_config(s, ap_server_pre_read_config, conftree,
                                    p, ptemp);
     if (error) {
         ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, 0, NULL, "%s: %s",
                      ap_server_argv0, error);
