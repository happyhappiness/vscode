     ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                  "  -l                 : list compiled in modules");
     ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                  "  -L                 : list available configuration "
                  "directives");
     ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                 "  -t -D DUMP_VHOSTS  : show parsed settings (currently only "
-                 "vhost settings)");
+                 "  -t -D DUMP_VHOSTS  : show parsed vhost settings");
+    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
+                 "  -t -D DUMP_RUN_CFG : show parsed run settings");
     ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                 "  -S                 : a synonym for -t -D DUMP_VHOSTS");
+                 "  -S                 : a synonym for -t -D DUMP_VHOSTS -D DUMP_RUN_CFG");
     ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                  "  -t -D DUMP_MODULES : show all loaded modules ");
     ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                  "  -M                 : a synonym for -t -D DUMP_MODULES");
     ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                  "  -t                 : run syntax check for config files");
