     }
 
 #if !defined(MPE) && !defined(OS2) && !defined(TPF) && !defined(BEOS)
     /* Don't detach for MPE because child processes can't survive the death of
      * the parent. */
     if (daemonize) {
-	    if ((x = fork()) > 0) {
-	        exit(0);
+        if ((x = fork()) > 0) {
+            exit(0);
         }
-	    else if (x == -1) {
-	        perror("fork");
-	        fprintf(stderr, "unable to fork new process\n");
-	        exit(1);  /* we can't do anything here, so just exit. */
-	    }
-	    /* RAISE_SIGSTOP(DETACH); */
+        else if (x == -1) {
+            perror("fork");
+            fprintf(stderr, "unable to fork new process\n");
+            exit(1);  /* we can't do anything here, so just exit. */
+        }
+        /* RAISE_SIGSTOP(DETACH); */
     }
 #endif
 
 #ifdef HAVE_SETSID
     /* A setsid() failure is not fatal if we didn't just fork().
      * The calling process may be the process group leader, in
