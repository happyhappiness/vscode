@@ -90,7 +90,7 @@ void memtest_progress_step(size_t curr, size_t size, char c) {
 /* Test that addressing is fine. Every location is populated with its own
  * address, and finally verified. This test is very fast but may detect
  * ASAP big issues with the memory subsystem. */
-void memtest_addressing(unsigned long *l, size_t bytes) {
+int memtest_addressing(unsigned long *l, size_t bytes, int interactive) {
     unsigned long words = bytes/sizeof(unsigned long);
     unsigned long j, *p;
 
@@ -99,26 +99,32 @@ void memtest_addressing(unsigned long *l, size_t bytes) {
     for (j = 0; j < words; j++) {
         *p = (unsigned long)p;
         p++;
-        if ((j & 0xffff) == 0) memtest_progress_step(j,words*2,'A');
+        if ((j & 0xffff) == 0 && interactive)
+            memtest_progress_step(j,words*2,'A');
     }
     /* Test */
     p = l;
     for (j = 0; j < words; j++) {
         if (*p != (unsigned long)p) {
-            printf("\n*** MEMORY ADDRESSING ERROR: %p contains %lu\n",
-                (void*) p, *p);
-            exit(1);
+            if (interactive) {
+                printf("\n*** MEMORY ADDRESSING ERROR: %p contains %lu\n",
+                    (void*) p, *p);
+                exit(1);
+            }
+            return 1;
         }
         p++;
-        if ((j & 0xffff) == 0) memtest_progress_step(j+words,words*2,'A');
+        if ((j & 0xffff) == 0 && interactive)
+            memtest_progress_step(j+words,words*2,'A');
     }
+    return 0;
 }
 
 /* Fill words stepping a single page at every write, so we continue to
  * touch all the pages in the smallest amount of time reducing the
  * effectiveness of caches, and making it hard for the OS to transfer
  * pages on the swap. */
-void memtest_fill_random(unsigned long *l, size_t bytes) {
+void memtest_fill_random(unsigned long *l, size_t bytes, int interactive) {
     unsigned long step = 4096/sizeof(unsigned long);
     unsigned long words = bytes/sizeof(unsigned long)/2;
     unsigned long iwords = words/step;  /* words per iteration */
@@ -140,7 +146,7 @@ void memtest_fill_random(unsigned long *l, size_t bytes) {
 #endif
             l1 += step;
             l2 += step;
-            if ((w & 0xffff) == 0)
+            if ((w & 0xffff) == 0 && interactive)
                 memtest_progress_step(w+iwords*off,words,'R');
         }
     }
@@ -149,7 +155,7 @@ void memtest_fill_random(unsigned long *l, size_t bytes) {
 /* Like memtest_fill_random() but uses the two specified values to fill
  * memory, in an alternated way (v1|v2|v1|v2|...) */
 void memtest_fill_value(unsigned long *l, size_t bytes, unsigned long v1,
-                        unsigned long v2, char sym)
+                        unsigned long v2, char sym, int interactive)
 {
     unsigned long step = 4096/sizeof(unsigned long);
     unsigned long words = bytes/sizeof(unsigned long)/2;
@@ -173,13 +179,13 @@ void memtest_fill_value(unsigned long *l, size_t bytes, unsigned long v1,
 #endif
             l1 += step;
             l2 += step;
-            if ((w & 0xffff) == 0)
+            if ((w & 0xffff) == 0 && interactive)
                 memtest_progress_step(w+iwords*off,words,sym);
         }
     }
 }
 
-void memtest_compare(unsigned long *l, size_t bytes) {
+int memtest_compare(unsigned long *l, size_t bytes, int interactive) {
     unsigned long words = bytes/sizeof(unsigned long)/2;
     unsigned long w, *l1, *l2;
 
@@ -188,58 +194,81 @@ void memtest_compare(unsigned long *l, size_t bytes) {
     l2 = l1+words;
     for (w = 0; w < words; w++) {
         if (*l1 != *l2) {
-            printf("\n*** MEMORY ERROR DETECTED: %p != %p (%lu vs %lu)\n",
-                (void*)l1, (void*)l2, *l1, *l2);
-            exit(1);
+            if (interactive) {
+                printf("\n*** MEMORY ERROR DETECTED: %p != %p (%lu vs %lu)\n",
+                    (void*)l1, (void*)l2, *l1, *l2);
+                exit(1);
+            }
+            return 1;
         }
         l1 ++;
         l2 ++;
-        if ((w & 0xffff) == 0) memtest_progress_step(w,words,'=');
+        if ((w & 0xffff) == 0 && interactive)
+            memtest_progress_step(w,words,'=');
     }
+    return 0;
 }
 
-void memtest_compare_times(unsigned long *m, size_t bytes, int pass, int times) {
+int memtest_compare_times(unsigned long *m, size_t bytes, int pass, int times,
+                          int interactive)
+{
     int j;
+    int errors = 0;
 
     for (j = 0; j < times; j++) {
-        memtest_progress_start("Compare",pass);
-        memtest_compare(m,bytes);
-        memtest_progress_end();
+        if (interactive) memtest_progress_start("Compare",pass);
+        errors += memtest_compare(m,bytes,interactive);
+        if (interactive) memtest_progress_end();
     }
+    return errors;
 }
 
-void memtest_test(size_t megabytes, int passes) {
-    size_t bytes = megabytes*1024*1024;
-    unsigned long *m = malloc(bytes);
+/* Test the specified memory. The number of bytes must be multiple of 4096.
+ * If interactive is true the program exists with an error and prints
+ * ASCII arts to show progresses. Instead when interactive is 0, it can
+ * be used as an API call, and returns 1 if memory errors were found or
+ * 0 if there were no errors detected. */
+int memtest_test(unsigned long *m, size_t bytes, int passes, int interactive) {
     int pass = 0;
+    int errors = 0;
 
-    if (m == NULL) {
-        fprintf(stderr,"Unable to allocate %zu megabytes: %s",
-            megabytes, strerror(errno));
-        exit(1);
-    }
     while (pass != passes) {
         pass++;
 
-        memtest_progress_start("Addressing test",pass);
-        memtest_addressing(m,bytes);
-        memtest_progress_end();
+        if (interactive) memtest_progress_start("Addressing test",pass);
+        errors += memtest_addressing(m,bytes,interactive);
+        if (interactive) memtest_progress_end();
 
-        memtest_progress_start("Random fill",pass);
-        memtest_fill_random(m,bytes);
-        memtest_progress_end();
-        memtest_compare_times(m,bytes,pass,4);
+        if (interactive) memtest_progress_start("Random fill",pass);
+        memtest_fill_random(m,bytes,interactive);
+        if (interactive) memtest_progress_end();
+        errors += memtest_compare_times(m,bytes,pass,4,interactive);
 
-        memtest_progress_start("Solid fill",pass);
-        memtest_fill_value(m,bytes,0,(unsigned long)-1,'S');
-        memtest_progress_end();
-        memtest_compare_times(m,bytes,pass,4);
+        if (interactive) memtest_progress_start("Solid fill",pass);
+        memtest_fill_value(m,bytes,0,(unsigned long)-1,'S',interactive);
+        if (interactive) memtest_progress_end();
+        errors += memtest_compare_times(m,bytes,pass,4,interactive);
 
-        memtest_progress_start("Checkerboard fill",pass);
-        memtest_fill_value(m,bytes,ULONG_ONEZERO,ULONG_ZEROONE,'C');
-        memtest_progress_end();
-        memtest_compare_times(m,bytes,pass,4);
+        if (interactive) memtest_progress_start("Checkerboard fill",pass);
+        memtest_fill_value(m,bytes,ULONG_ONEZERO,ULONG_ZEROONE,'C',interactive);
+        if (interactive) memtest_progress_end();
+        errors += memtest_compare_times(m,bytes,pass,4,interactive);
+    }
+    free(m);
+    return errors;
+}
+
+/* Perform an interactive test allocating the specified number of megabytes. */
+void memtest_alloc_and_test(size_t megabytes, int passes) {
+    size_t bytes = megabytes*1024*1024;
+    unsigned long *m = malloc(bytes);
+
+    if (m == NULL) {
+        fprintf(stderr,"Unable to allocate %zu megabytes: %s",
+            megabytes, strerror(errno));
+        exit(1);
     }
+    memtest_test(m,bytes,passes,1);
     free(m);
 }
 
@@ -274,7 +303,7 @@ void memtest(size_t megabytes, int passes) {
         ws.ws_col = 80;
         ws.ws_row = 20;
     }
-    memtest_test(megabytes,passes);
+    memtest_alloc_and_test(megabytes,passes);
     printf("\nYour memory passed this test.\n");
     printf("Please if you are still in doubt use the following two tools:\n");
     printf("1) memtest86: http://www.memtest86.com/\n");