      * -N, check the cygwin1.dll version, it needs to be AT LEAST
      * 1.1.3.  execvp had a bit overflow error in a loop..
      */
     /* Connect stdio to /dev/null in daemon mode */
     nullfd = open(_PATH_DEVNULL, O_RDWR | O_TEXT);
 
-    if (nullfd < 0)
-        fatalf(_PATH_DEVNULL " %s\n", xstrerror());
+    if (nullfd < 0) {
+        int xerrno = errno;
+        fatalf(_PATH_DEVNULL " %s\n", xstrerr(xerrno));
+    }
 
     dup2(nullfd, 0);
 
     if (Debug::log_stderr < 0) {
         dup2(nullfd, 1);
         dup2(nullfd, 2);
     }
 
-    // handle shutdown notifications from kids
-    squid_signal(SIGUSR1, sig_shutdown, SA_RESTART);
+    leave_suid();
+    Instance::WriteOurPid();
+    StartUsingConfig();
+    enter_suid();
+
+#if defined(_SQUID_LINUX_THREADS_)
+    squid_signal(SIGQUIT, rotate_logs, 0);
+    squid_signal(SIGTRAP, sigusr2_handle, 0);
+#else
+    squid_signal(SIGUSR1, rotate_logs, 0);
+    squid_signal(SIGUSR2, sigusr2_handle, 0);
+#endif
+
+    squid_signal(SIGHUP, reconfigure, 0);
+
+    squid_signal(SIGTERM, master_shutdown, 0);
+    squid_signal(SIGINT, master_shutdown, 0);
+#ifdef SIGTTIN
+    squid_signal(SIGTTIN, master_shutdown, 0);
+#endif
 
     if (Config.workers > 128) {
         syslog(LOG_ALERT, "Suspiciously high workers value: %d",
                Config.workers);
         // but we keep going in hope that user knows best
     }
     TheKids.init();
 
     syslog(LOG_NOTICE, "Squid Parent: will start %d kids", (int)TheKids.count());
 
     // keep [re]starting kids until it is time to quit
     for (;;) {
-        mainStartScript(argv[0]);
-
+        bool mainStartScriptCalled = false;
         // start each kid that needs to be [re]started; once
-        for (int i = TheKids.count() - 1; i >= 0; --i) {
+        for (int i = TheKids.count() - 1; i >= 0 && !shutting_down; --i) {
             Kid& kid = TheKids.get(i);
             if (!kid.shouldRestart())
                 continue;
 
+            if (!mainStartScriptCalled) {
+                mainStartScript(argv[0]);
+                mainStartScriptCalled = true;
+            }
+
             if ((pid = fork()) == 0) {
                 /* child */
                 openlog(APP_SHORTNAME, LOG_PID | LOG_NDELAY | LOG_CONS, LOG_LOCAL4);
                 prog = argv[0];
                 argv[0] = const_cast<char*>(kid.name().termedBuf());
                 execvp(prog, argv);
-                syslog(LOG_ALERT, "execvp failed: %s", xstrerror());
+                int xerrno = errno;
+                syslog(LOG_ALERT, "execvp failed: %s", xstrerr(xerrno));
             }
 
             kid.start(pid);
             syslog(LOG_NOTICE, "Squid Parent: %s process %d started",
                    kid.name().termedBuf(), pid);
         }
 
         /* parent */
         openlog(APP_SHORTNAME, LOG_PID | LOG_NDELAY | LOG_CONS, LOG_LOCAL4);
 
-        squid_signal(SIGINT, SIG_IGN, SA_RESTART);
-
-#if _SQUID_NEXT_
-
-        pid = wait3(&status, 0, NULL);
-
-#else
-
-        pid = waitpid(-1, &status, 0);
-
-#endif
-        // Loop to collect all stopped kids before we go to sleep below.
-        do {
-            Kid* kid = TheKids.find(pid);
-            if (kid) {
-                kid->stop(status);
-                if (kid->calledExit()) {
-                    syslog(LOG_NOTICE,
-                           "Squid Parent: %s process %d exited with status %d",
-                           kid->name().termedBuf(),
-                           kid->getPid(), kid->exitStatus());
-                } else if (kid->signaled()) {
-                    syslog(LOG_NOTICE,
-                           "Squid Parent: %s process %d exited due to signal %d with status %d",
-                           kid->name().termedBuf(),
-                           kid->getPid(), kid->termSignal(), kid->exitStatus());
-                } else {
-                    syslog(LOG_NOTICE, "Squid Parent: %s process %d exited",
-                           kid->name().termedBuf(), kid->getPid());
-                }
-                if (kid->hopeless()) {
-                    syslog(LOG_NOTICE, "Squid Parent: %s process %d will not"
-                           " be restarted due to repeated, frequent failures",
-                           kid->name().termedBuf(), kid->getPid());
-                }
+        // If Squid received a signal while checking for dying kids (below) or
+        // starting new kids (above), then do a fast check for a new dying kid
+        // (WaitForAnyPid with the WNOHANG option) and continue to forward
+        // signals to kids. Otherwise, wait for a kid to die or for a signal
+        // to abort the blocking WaitForAnyPid() call.
+        // With the WNOHANG option, we could check whether WaitForAnyPid() was
+        // aborted by a dying kid or a signal, but it is not required: The
+        // next do/while loop will check again for any dying kids.
+        int waitFlag = 0;
+        if (masterSignaled())
+            waitFlag = WNOHANG;
+        pid = WaitForAnyPid(status, waitFlag);
+
+        // check for a stopped kid
+        Kid* kid = pid > 0 ? TheKids.find(pid) : NULL;
+        if (kid) {
+            kid->stop(status);
+            if (kid->calledExit()) {
+                syslog(LOG_NOTICE,
+                       "Squid Parent: %s process %d exited with status %d",
+                       kid->name().termedBuf(),
+                       kid->getPid(), kid->exitStatus());
+            } else if (kid->signaled()) {
+                syslog(LOG_NOTICE,
+                       "Squid Parent: %s process %d exited due to signal %d with status %d",
+                       kid->name().termedBuf(),
+                       kid->getPid(), kid->termSignal(), kid->exitStatus());
             } else {
-                syslog(LOG_NOTICE, "Squid Parent: unknown child process %d exited", pid);
+                syslog(LOG_NOTICE, "Squid Parent: %s process %d exited",
+                       kid->name().termedBuf(), kid->getPid());
             }
-#if _SQUID_NEXT_
-        } while ((pid = wait3(&status, WNOHANG, NULL)) > 0);
-#else
+            if (kid->hopeless()) {
+                syslog(LOG_NOTICE, "Squid Parent: %s process %d will not"
+                       " be restarted due to repeated, frequent failures",
+                       kid->name().termedBuf(), kid->getPid());
+            }
+        } else if (pid > 0) {
+            syslog(LOG_NOTICE, "Squid Parent: unknown child process %d exited", pid);
         }
-        while ((pid = waitpid(-1, &status, WNOHANG)) > 0);
-#endif
 
         if (!TheKids.someRunning() && !TheKids.shouldRestartSome()) {
             leave_suid();
             // XXX: Master process has no main loop and, hence, should not call
             // RegisteredRunner::startShutdown which promises a loop iteration.
             RunRegisteredHere(RegisteredRunner::finishShutdown);
