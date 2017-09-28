                     err = sdscatprintf(sdsempty(),
                         "Can't open the log file: %s", strerror(errno));
                     goto loaderr;
                 }
                 fclose(logfp);
             }
+        } else if (!strcasecmp(argv[0],"always-show-logo") && argc == 2) {
+            if ((server.always_show_logo = yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
         } else if (!strcasecmp(argv[0],"syslog-enabled") && argc == 2) {
             if ((server.syslog_enabled = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
         } else if (!strcasecmp(argv[0],"syslog-ident") && argc == 2) {
             if (server.syslog_ident) zfree(server.syslog_ident);
