@@ -975,6 +975,32 @@ int memtest_test_linux_anonymous_maps(void) {
 }
 #endif
 
+/* Scans the (assumed) x86 code starting at addr, for a max of `len`
+ * bytes, searching for E8 (callq) opcodes, and dumping the symbols
+ * and the call offset if they appear to be valid. */
+void dumpX86Calls(void *addr, size_t len) {
+    size_t j;
+    unsigned char *p = addr;
+    Dl_info info;
+    /* Hash table to best-effort avoid printing the same symbol
+     * multiple times. */
+    unsigned long ht[256] = {0};
+
+    if (len < 5) return;
+    for (j = 0; j < len-4; j++) {
+        if (p[j] != 0xE8) continue; /* Not an E8 CALL opcode. */
+        unsigned long target = (unsigned long)addr+j+5;
+        target += *((int32_t*)(p+j+1));
+        if (dladdr((void*)target, &info) != 0 && info.dli_sname != NULL) {
+            if (ht[target&0xff] != target) {
+                printf("Function at 0x%lx is %s\n",target,info.dli_sname);
+                ht[target&0xff] = target;
+            }
+            j += 4; /* Skip the 32 bit immediate. */
+        }
+    }
+}
+
 void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
     ucontext_t *uc = (ucontext_t*) secret;
     void *eip = getMcontextEip(uc);
@@ -1025,39 +1051,52 @@ void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
     bioKillThreads();
     if (memtest_test_linux_anonymous_maps()) {
         serverLogRaw(LL_WARNING|LL_RAW,
-            "!!! MEMORY ERROR DETECTED! Check your memory ASAP !!!");
+            "!!! MEMORY ERROR DETECTED! Check your memory ASAP !!!\n");
     } else {
         serverLogRaw(LL_WARNING|LL_RAW,
-            "Fast memory test PASSED, however your memory can still be broken. Please run a memory test for several hours if possible.");
+            "Fast memory test PASSED, however your memory can still be broken. Please run a memory test for several hours if possible.\n");
     }
 #endif
 
+    if (eip != NULL) {
+        Dl_info info;
+        if (dladdr(eip, &info) != 0) {
+            serverLog(LL_WARNING|LL_RAW,
+                "\n------ DUMPING CODE AROUND EIP ------\n"
+                "Symbol: %s (base: %p)\n"
+                "Module: %s (base %p)\n"
+                "$ xxd -r -p /tmp/dump.hex /tmp/dump.bin\n"
+                "$ objdump --adjust-vma=%p -D -b binary -m i386:x86-64 /tmp/dump.bin\n"
+                "------\n",
+                info.dli_sname, info.dli_saddr, info.dli_fname, info.dli_fbase,
+                info.dli_saddr);
+            size_t len = (long)eip - (long)info.dli_saddr;
+            unsigned long sz = sysconf(_SC_PAGESIZE);
+            if (len < 1<<13) { /* we don't have functions over 8k (verified) */
+                /* Find the address of the next page, which is our "safety"
+                 * limit when dumping. Then try to dump just 128 bytes more
+                 * than EIP if there is room, or stop sooner. */
+                unsigned long next = ((unsigned long)eip + sz) & ~(sz-1);
+                unsigned long end = (unsigned long)eip + 128;
+                if (end > next) end = next;
+                len = end - (unsigned long)info.dli_saddr;
+                serverLogHexDump(LL_WARNING, "dump of function",
+                    info.dli_saddr ,len);
+                dumpX86Calls(info.dli_saddr,len);
+            }
+        }
+    }
+
     serverLogRaw(LL_WARNING|LL_RAW,
 "\n=== REDIS BUG REPORT END. Make sure to include from START to END. ===\n\n"
 "       Please report the crash by opening an issue on github:\n\n"
 "           http://github.com/antirez/redis/issues\n\n"
 "  Suspect RAM error? Use redis-server --test-memory to verify it.\n\n"
 );
+
     /* free(messages); Don't call free() with possibly corrupted memory. */
     if (server.daemonize && server.supervised == 0) unlink(server.pidfile);
 
-    if (eip != NULL) {
-        Dl_info info;
-        if (dladdr(eip, &info) != 0)
-        {
-            serverLog(LL_WARNING,
-                "symbol: %s (base %p), in module: %s (base: %p)",
-                info.dli_sname, info.dli_saddr, info.dli_fname, info.dli_fbase);
-            size_t len = (long)eip - (long)info.dli_saddr;
-            long sz = sysconf(_SC_PAGESIZE);
-            if (len < 1<<13) { /* we don't have functions over 8k (verified) */
-                long end = ((long)eip + sz) & ~(sz-1); /* round up to page boundary */
-                len = end - (long)info.dli_saddr;
-                serverLogHexDump(LL_WARNING, "dump of function", info.dli_saddr ,len);
-            }
-        }
-    }
-
     /* Make sure we exit with the right signal at the end. So for instance
      * the core will be dumped if enabled. */
     sigemptyset (&act.sa_mask);
@@ -1075,7 +1114,7 @@ void serverLogHexDump(int level, char *descr, void *value, size_t len) {
     unsigned char *v = value;
     char charset[] = "0123456789abcdef";
 
-    serverLog(level,"%s (hexdump):", descr);
+    serverLog(level,"%s (hexdump of %zu bytes):", descr, len);
     b = buf;
     while(len) {
         b[0] = charset[(*v)>>4];