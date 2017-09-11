@@ -912,6 +912,10 @@ void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
     bugReportStart();
     serverLog(LL_WARNING,
         "    Redis %s crashed by signal: %d", REDIS_VERSION, sig);
+    if (sig == SIGSEGV) {
+        serverLog(LL_WARNING,
+        "    SIGSEGV caused by address: %p", (void*)info->si_addr);
+    }
     serverLog(LL_WARNING,
         "    Failed assertion: %s (%s:%d)", server.assert_failed,
                         server.assert_file, server.assert_line);