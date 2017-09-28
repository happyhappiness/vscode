                 err = "Invalid log level. Must be one of debug, notice, warning";
                 goto loaderr;
             }
         } else if (!strcasecmp(argv[0],"logfile") && argc == 2) {
             FILE *logfp;
 
+            zfree(server.logfile);
             server.logfile = zstrdup(argv[1]);
-            if (!strcasecmp(server.logfile,"stdout")) {
-                zfree(server.logfile);
-                server.logfile = NULL;
-            }
-            if (server.logfile) {
+            if (server.logfile[0] != '\0') {
                 /* Test if we are able to open the file. The server will not
                  * be able to abort just for this problem later... */
                 logfp = fopen(server.logfile,"a");
                 if (logfp == NULL) {
                     err = sdscatprintf(sdsempty(),
                         "Can't open the log file: %s", strerror(errno));
