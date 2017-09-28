     kill(getpid(),sig);
 }
 #endif /* HAVE_BACKTRACE */
 
 /* ==================== Logging functions for debugging ===================== */
 
-void redisLogHexDump(int level, char *descr, void *value, size_t len) {
+void serverLogHexDump(int level, char *descr, void *value, size_t len) {
     char buf[65], *b;
     unsigned char *v = value;
     char charset[] = "0123456789abcdef";
 
-    redisLog(level,"%s (hexdump):", descr);
+    serverLog(level,"%s (hexdump):", descr);
     b = buf;
     while(len) {
         b[0] = charset[(*v)>>4];
         b[1] = charset[(*v)&0xf];
         b[2] = '\0';
         b += 2;
         len--;
         v++;
         if (b-buf == 64 || len == 0) {
-            redisLogRaw(level|REDIS_LOG_RAW,buf);
+            serverLogRaw(level|LL_RAW,buf);
             b = buf;
         }
     }
-    redisLogRaw(level|REDIS_LOG_RAW,"\n");
+    serverLogRaw(level|LL_RAW,"\n");
 }
 
 /* =========================== Software Watchdog ============================ */
 #include <sys/time.h>
 
 void watchdogSignalHandler(int sig, siginfo_t *info, void *secret) {
 #ifdef HAVE_BACKTRACE
     ucontext_t *uc = (ucontext_t*) secret;
 #endif
-    REDIS_NOTUSED(info);
-    REDIS_NOTUSED(sig);
+    UNUSED(info);
+    UNUSED(sig);
 
-    redisLogFromHandler(REDIS_WARNING,"\n--- WATCHDOG TIMER EXPIRED ---");
+    serverLogFromHandler(LL_WARNING,"\n--- WATCHDOG TIMER EXPIRED ---");
 #ifdef HAVE_BACKTRACE
     logStackTrace(uc);
 #else
-    redisLogFromHandler(REDIS_WARNING,"Sorry: no support for backtrace().");
+    serverLogFromHandler(LL_WARNING,"Sorry: no support for backtrace().");
 #endif
-    redisLogFromHandler(REDIS_WARNING,"--------\n");
+    serverLogFromHandler(LL_WARNING,"--------\n");
 }
 
 /* Schedule a SIGALRM delivery after the specified period in milliseconds.
  * If a timer is already scheduled, this function will re-schedule it to the
  * specified time. If period is 0 the current timer is disabled. */
 void watchdogScheduleSignal(int period) {
