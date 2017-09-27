                         else if (*end &&        /* neither empty nor [Bb] */
                                  ((*end != 'B' && *end != 'b') || end[1])) {
                             rv = APR_EGENERAL;
                         }
                     }
                     if (rv != APR_SUCCESS) {
-                        apr_file_printf(errfile, "Invalid limit: %s"
-                                                 APR_EOL_STR APR_EOL_STR, arg);
-                        usage();
+                        usage(apr_psprintf(pool, "Invalid limit: %s"
+                                                 APR_EOL_STR APR_EOL_STR, arg));
                     }
                 } while(0);
                 break;
 
             case 'p':
                 if (proxypath) {
-                    usage();
+                    usage(apr_psprintf(pool, "The option '%c' cannot be specified more than once", (int)opt));
                 }
                 proxypath = apr_pstrdup(pool, arg);
-                if (apr_filepath_set(proxypath, pool) != APR_SUCCESS) {
-                    usage();
+                if ((status = apr_filepath_set(proxypath, pool)) != APR_SUCCESS) {
+                    usage(apr_psprintf(pool, "Could not set filepath to '%s': %s",
+                                       proxypath, apr_strerror(status, errmsg, sizeof errmsg)));
                 }
                 break;
             } /* switch */
         } /* else */
     } /* while */
 
+    if (argc <= 1) {
+        usage(NULL);
+    }
+
     if (o->ind != argc) {
-         usage();
+         usage("Additional parameters specified on the command line, aborting");
     }
 
-    if (isdaemon && (repeat <= 0 || verbose || realclean || dryrun)) {
-         usage();
+    if (isdaemon && repeat <= 0) {
+         usage("Option -d must be greater than zero");
+    }
+
+    if (isdaemon && (verbose || realclean || dryrun)) {
+         usage("Option -d cannot be used with -v, -r or -D");
     }
 
     if (!isdaemon && intelligent) {
-         usage();
+         usage("Option -i cannot be used without -d");
+    }
+
+    if (!proxypath) {
+         usage("Option -p must be specified");
     }
 
-    if (!proxypath || max <= 0) {
-         usage();
+    if (max <= 0) {
+         usage("Option -l must be greater than zero");
     }
 
     if (apr_filepath_get(&path, 0, pool) != APR_SUCCESS) {
-        usage();
+        usage(apr_psprintf(pool, "Could not get the filepath: %s",
+                           apr_strerror(status, errmsg, sizeof errmsg)));
     }
     baselen = strlen(path);
 
 #ifndef DEBUG
     if (isdaemon) {
         apr_file_close(errfile);
