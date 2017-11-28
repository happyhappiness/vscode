 #endif
 
         eventAdd("SquidTerminate", &StopEventLoop, NULL, 0, 1, false);
     }
 
     void doShutdown(time_t wait);
+    void handleStoppedChild();
+
+#if KILL_PARENT_OPT
+    bool parentKillNotified;
+    pid_t parentPid;
+#endif
 };
 
 int
-SignalEngine::checkEvents(int timeout)
+SignalEngine::checkEvents(int)
 {
     PROF_start(SignalEngine_checkEvents);
 
-    if (do_reconfigure) {
-        if (!reconfiguring && configured_once) {
-            mainReconfigureStart();
-            do_reconfigure = 0;
-        } // else wait until previous reconfigure is done
-    } else if (do_rotate) {
+    if (do_reconfigure)
+        mainReconfigureStart();
+    else if (do_rotate)
         mainRotate();
-        do_rotate = 0;
-    } else if (do_shutdown) {
+    else if (do_shutdown)
         doShutdown(do_shutdown > 0 ? (int) Config.shutdownLifetime : 0);
-        do_shutdown = 0;
-    }
-    BroadcastSignalIfAny(DebugSignal);
-    BroadcastSignalIfAny(RotateSignal);
-    BroadcastSignalIfAny(ReconfigureSignal);
-    BroadcastSignalIfAny(ShutdownSignal);
-
+    if (do_handle_stopped_child)
+        handleStoppedChild();
     PROF_stop(SignalEngine_checkEvents);
     return EVENT_IDLE;
 }
 
+/// Decides whether the signal-controlled action X should be delayed, canceled,
+/// or executed immediately. Clears do_X (via signalVar) as needed.
+static bool
+AvoidSignalAction(const char *description, volatile int &signalVar)
+{
+    const char *avoiding = "delaying";
+    const char *currentEvent = "none";
+    if (shutting_down) {
+        currentEvent = "shutdown";
+        avoiding = "canceling";
+        // do not avoid repeated shutdown signals
+        // which just means the user wants to skip/abort shutdown timeouts
+        if (strcmp(currentEvent, description) == 0)
+            return false;
+        signalVar = 0;
+    }
+    else if (!configured_once)
+        currentEvent = "startup";
+    else if (reconfiguring)
+        currentEvent = "reconfiguration";
+    else {
+        signalVar = 0;
+        return false; // do not avoid (i.e., execute immediately)
+        // the caller may produce a signal-specific debugging message
+    }
+
+    debugs(1, DBG_IMPORTANT, avoiding << ' ' << description <<
+           " request during " << currentEvent);
+    return true;
+}
+
 void
 SignalEngine::doShutdown(time_t wait)
 {
+    if (AvoidSignalAction("shutdown", do_shutdown))
+        return;
+
     debugs(1, DBG_IMPORTANT, "Preparing for shutdown after " << statCounter.client_http.requests << " requests");
     debugs(1, DBG_IMPORTANT, "Waiting " << wait << " seconds for active connections to finish");
 
-    shutting_down = 1;
+#if KILL_PARENT_OPT
+    if (!IamMasterProcess() && !parentKillNotified && ShutdownSignal > 0 && parentPid > 1) {
+        debugs(1, DBG_IMPORTANT, "Killing master process, pid " << parentPid);
+        if (kill(parentPid, ShutdownSignal) < 0) {
+            int xerrno = errno;
+            debugs(1, DBG_IMPORTANT, "kill " << parentPid << ": " << xstrerr(xerrno));
+        }
+        parentKillNotified = true;
+    }
+#endif
+
+    if (shutting_down) {
+#if !KILL_PARENT_OPT
+        // Already a shutdown signal has received and shutdown is in progress.
+        // Shutdown as soon as possible.
+        wait = 0;
+#endif
+    } else {
+        shutting_down = 1;
+
+        /* run the closure code which can be shared with reconfigure */
+        serverConnectionsClose();
+
+        RunRegisteredHere(RegisteredRunner::startShutdown);
+    }
 
 #if USE_WIN32_SERVICE
     WIN32_svcstatusupdate(SERVICE_STOP_PENDING, (wait + 1) * 1000);
 #endif
 
-    /* run the closure code which can be shared with reconfigure */
-    serverConnectionsClose();
-    RunRegisteredHere(RegisteredRunner::startShutdown);
     eventAdd("SquidShutdown", &FinalShutdownRunners, this, (double) (wait + 1), 1, false);
 }
 
+void
+SignalEngine::handleStoppedChild()
+{
+    // no AvoidSignalAction() call: This code can run at any time because it
+    // does not depend on Squid state. It does not need debugging because it
+    // handles an "internal" signal, not an external/admin command.
+    do_handle_stopped_child = 0;
+#if !_SQUID_WINDOWS_
+    PidStatus status;
+    pid_t pid;
+
+    do {
+        pid = WaitForAnyPid(status, WNOHANG);
+
+#if HAVE_SIGACTION
+
+    } while (pid > 0);
+
+#else
+
+    }
+    while (pid > 0 || (pid < 0 && errno == EINTR));
+#endif
+#endif
+}
+
 static void
 usage(void)
 {
     fprintf(stderr,
-            "Usage: %s [-cdhvzCFNRVYX] [-n name] [-s | -l facility] [-f config-file] [-[au] port] [-k signal]"
+            "Usage: %s [-cdzCFNRVYX] [-n name] [-s | -l facility] [-f config-file] [-[au] port] [-k signal]"
 #if USE_WIN32_SERVICE
             "[-ir] [-O CommandLine]"
 #endif
             "\n"
+            "    -h | --help       Print help message.\n"
+            "    -v | --version    Print version details.\n"
+            "\n"
             "       -a port   Specify HTTP port number (default: %d).\n"
             "       -d level  Write debugging to stderr also.\n"
             "       -f file   Use given config-file instead of\n"
             "                 %s\n"
-            "       -h        Print help message.\n"
 #if USE_WIN32_SERVICE
             "       -i        Installs as a Windows Service (see -n option).\n"
 #endif
             "       -k reconfigure|rotate|shutdown|"
 #ifdef SIGTTIN
             "restart|"
