     } else {
         Debug::parseOptions(Debug::debugOptions);
         state = 0;
     }
 
 #if !HAVE_SIGACTION
-    if (signal(sig, sigusr2_handle) == SIG_ERR) /* reinstall */
-        debugs(50, DBG_CRITICAL, "signal: sig=" << sig << " func=sigusr2_handle: " << xstrerror());
-
+    /* reinstall */
+    if (signal(sig, sigusr2_handle) == SIG_ERR) {
+        int xerrno = errno;
+        debugs(50, DBG_CRITICAL, "signal: sig=" << sig << " func=sigusr2_handle: " << xstrerr(xerrno));
+    }
 #endif
 }
 
 void
 debug_trap(const char *message)
 {
     if (!opt_catch_signals)
         fatal_dump(message);
 
     _db_print("WARNING: %s\n", message);
 }
 
-void
-sig_child(int sig)
-{
-#if !_SQUID_WINDOWS_
-#if _SQUID_NEXT_
-    union wait status;
-#else
-
-    int status;
-#endif
-
-    pid_t pid;
-
-    do {
-#if _SQUID_NEXT_
-        pid = wait3(&status, WNOHANG, NULL);
-#else
-
-        pid = waitpid(-1, &status, WNOHANG);
-#endif
-        /* no debugs() here; bad things happen if the signal is delivered during _db_print() */
-#if HAVE_SIGACTION
-
-    } while (pid > 0);
-
-#else
-
-    }
-
-    while (pid > 0 || (pid < 0 && errno == EINTR));
-    signal(sig, sig_child);
-
-#endif
-#endif
-}
-
-void
-sig_shutdown(int sig)
-{
-    shutting_down = 1;
-}
-
 const char *
 getMyHostname(void)
 {
     LOCAL_ARRAY(char, host, SQUIDHOSTNAMELEN + 1);
     static int present = 0;
     struct addrinfo *AI = NULL;
