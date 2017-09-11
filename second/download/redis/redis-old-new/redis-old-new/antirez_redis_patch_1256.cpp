@@ -667,16 +667,22 @@ void logCurrentClient(void) {
 }
 
 #if defined(HAVE_PROC_MAPS)
-int memtest_non_destructive(void *addr, size_t size); /* memtest.c */
+uint64_t crc64(uint64_t crc, const unsigned char *s, uint64_t l);
+void memtest_non_destructive_invert(void *addr, size_t size);
+void memtest_non_destructive_swap(void *addr, size_t size);
+#define MEMTEST_MAX_REGIONS 128
 
 int memtest_test_linux_anonymous_maps(void) {
     FILE *fp = fopen("/proc/self/maps","r");
     char line[1024];
     size_t start_addr, end_addr, size;
+    size_t start_vect[MEMTEST_MAX_REGIONS];
+    size_t size_vect[MEMTEST_MAX_REGIONS];
+    int regions = 0, j;
+    uint64_t crc1 = 0, crc2 = 0, crc3 = 0;
 
     while(fgets(line,sizeof(line),fp) != NULL) {
         char *start, *end, *p = line;
-        int j;
 
         start = p;
         p = strchr(p,'-');
@@ -695,17 +701,51 @@ int memtest_test_linux_anonymous_maps(void) {
         start_addr = strtoul(start,NULL,16);
         end_addr = strtoul(end,NULL,16);
         size = end_addr-start_addr;
-        redisLog(REDIS_WARNING,
-            "Testing memory at %lx (%lu bytes)", start_addr, size);
-        for (j = 0; j < 3; j++) {
-            if (memtest_non_destructive((void*)start_addr,size) != 0) {
-                fclose(fp);
-                return 1;
-            }
-        }
+
+        start_vect[regions] = start_addr;
+        size_vect[regions] = size;
+        printf("Testing %lx %lu\n", start_vect[regions], size_vect[regions]);
+        regions++;
     }
+
+    /* Test all the regions as an unique sequential region.
+     * 1) Take the CRC64 of the memory region. */
+    for (j = 0; j < regions; j++) {
+        crc1 = crc64(crc1,(void*)start_vect[j],size_vect[j]);
+    }
+
+    /* 2) Invert bits, swap adiacent words, swap again, invert bits.
+     * This is the error amplification step. */
+    for (j = 0; j < regions; j++)
+        memtest_non_destructive_invert((void*)start_vect[j],size_vect[j]);
+    for (j = 0; j < regions; j++)
+        memtest_non_destructive_swap((void*)start_vect[j],size_vect[j]);
+    for (j = 0; j < regions; j++)
+        memtest_non_destructive_swap((void*)start_vect[j],size_vect[j]);
+    for (j = 0; j < regions; j++)
+        memtest_non_destructive_invert((void*)start_vect[j],size_vect[j]);
+
+    /* 3) Take the CRC64 sum again. */
+    for (j = 0; j < regions; j++)
+        crc2 = crc64(crc2,(void*)start_vect[j],size_vect[j]);
+
+    /* 4) Swap + Swap again */
+    for (j = 0; j < regions; j++)
+        memtest_non_destructive_swap((void*)start_vect[j],size_vect[j]);
+    for (j = 0; j < regions; j++)
+        memtest_non_destructive_swap((void*)start_vect[j],size_vect[j]);
+
+    /* 5) Take the CRC64 sum again. */
+    for (j = 0; j < regions; j++)
+        crc3 = crc64(crc3,(void*)start_vect[j],size_vect[j]);
+
+    /* NOTE: It is very important to close the file descriptor only now
+     * because closing it before may result into unmapping of some memory
+     * region that we are testing. */
     fclose(fp);
-    return 0;
+
+    /* If the two CRC are not the same, we trapped a memory error. */
+    return crc1 != crc2 || crc2 != crc3;
 }
 #endif
 