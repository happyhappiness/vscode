@@ -39,6 +39,9 @@
 #include <ucontext.h>
 #include <fcntl.h>
 #include "bio.h"
+#include <unistd.h>
+#define _GNU_SOURCE
+#include <dlfcn.h>
 #endif /* HAVE_BACKTRACE */
 
 #ifdef __CYGWIN__
@@ -669,6 +672,8 @@ static void *getMcontextEip(ucontext_t *uc) {
     return (void*) uc->uc_mcontext.gregs[16]; /* Linux 64 */
     #elif defined(__ia64__) /* Linux IA64 */
     return (void*) uc->uc_mcontext.sc_ip;
+    #elif defined(__arm__) /* Linux ARM */
+    return (void*) uc->uc_mcontext.arm_pc;
     #endif
 #else
     return NULL;
@@ -1036,6 +1041,23 @@ void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
     /* free(messages); Don't call free() with possibly corrupted memory. */
     if (server.daemonize && server.supervised == 0) unlink(server.pidfile);
 
+    if (eip != NULL) {
+        Dl_info info;
+        if (dladdr(eip, &info) != 0)
+        {
+            serverLog(LL_WARNING,
+                "symbol: %s (base %p), in module: %s (base: %p)",
+                info.dli_sname, info.dli_saddr, info.dli_fname, info.dli_fbase);
+            size_t len = (long)eip - (long)info.dli_saddr;
+            long sz = sysconf(_SC_PAGESIZE);
+            if (len < 1<<13) { /* we don't have functions over 8k (verified) */
+                long end = ((long)eip + sz) & ~(sz-1); /* round up to page boundary */
+                len = end - (long)info.dli_saddr;
+                serverLogHexDump(LL_WARNING, "dump of function", info.dli_saddr ,len);
+            }
+        }
+    }
+
     /* Make sure we exit with the right signal at the end. So for instance
      * the core will be dumped if enabled. */
     sigemptyset (&act.sa_mask);