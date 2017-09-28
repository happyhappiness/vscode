 #if defined(HAVE_PROC_MAPS)
     /* Test memory */
     serverLogRaw(LL_WARNING|LL_RAW, "\n------ FAST MEMORY TEST ------\n");
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
