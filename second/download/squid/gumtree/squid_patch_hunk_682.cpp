     setbuf(stderr, NULL);
 
     my_program_name = argv[0];
 
     process_options(argc, argv);
 
-    debug("%s build " __DATE__ ", " __TIME__ " starting up...\n", my_program_name);
+    debug("%s " VERSION " " SQUID_BUILD_INFO " starting up...\n", my_program_name);
 
     while (fgets(buf, HELPER_INPUT_BUFFER, stdin) != NULL) {
         char *p;
 
         if ((p = strchr(buf, '\n')) != NULL) {
-            *p = '\0';		/* strip \n */
+            *p = '\0';      /* strip \n */
             buflen = p - buf;   /* length is known already */
         } else
             buflen = strlen(buf);   /* keep this so we only scan the buffer for \0 once per loop */
 
         debug("Got %d bytes '%s' from Squid\n", buflen, buf);
 
-        /* send 'no-change' result back to Squid */
-        fprintf(stdout,"\n");
+        p = NULL;
+        int64_t channelId = strtoll(buf, &p, 10);
+        if (*p != ' ') {
+            /* send 'no-change' result back to Squid in non-concurrent format */
+            fprintf(stdout,"ERR\n");
+        } else {
+            /* send 'no-change' result back to Squid in concurrent format */
+            fprintf(stdout, "%" PRId64 " ERR\n", channelId);
+        }
     }
-    debug("%s build " __DATE__ ", " __TIME__ " shutting down...\n", my_program_name);
-    exit(0);
+    debug("%s " VERSION " " SQUID_BUILD_INFO " shutting down...\n", my_program_name);
+    return 0;
 }
+
