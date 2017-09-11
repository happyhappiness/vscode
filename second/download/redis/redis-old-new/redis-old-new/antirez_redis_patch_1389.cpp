@@ -15,6 +15,14 @@
 #error "ULONG_MAX value not supported."
 #endif
 
+#ifdef MEMTEST_32BIT
+#define ULONG_ONEZERO 0xaaaaaaaaaaaaaaaaUL
+#define ULONG_ZEROONE 0x5555555555555555UL
+#else
+#define ULONG_ONEZERO 0xaaaaaaaaUL
+#define ULONG_ZEROONE 0x55555555UL
+#endif
+
 static struct winsize ws;
 size_t progress_printed; /* Printed chars in screen-wide progress bar. */
 size_t progress_full; /* How many chars to write to fill the progress bar. */
@@ -52,7 +60,7 @@ void memtest_progress_step(size_t curr, size_t size, char c) {
  * touch all the pages in the smallest amount of time reducing the
  * effectiveness of caches, and making it hard for the OS to transfer
  * pages on the swap. */
-void memtest_fill(unsigned long *l, size_t bytes) {
+void memtest_fill_random(unsigned long *l, size_t bytes) {
     unsigned long step = 4096/sizeof(unsigned long);
     unsigned long words = bytes/sizeof(unsigned long)/2;
     unsigned long iwords = words/step;  /* words per iteration */
@@ -75,7 +83,40 @@ void memtest_fill(unsigned long *l, size_t bytes) {
             l1 += step;
             l2 += step;
             if ((w & 0xffff) == 0)
-                memtest_progress_step(w+iwords*off,words,'+');
+                memtest_progress_step(w+iwords*off,words,'R');
+        }
+    }
+}
+
+/* Like memtest_fill_random() but uses the two specified values to fill
+ * memory, in an alternated way (v1|v2|v1|v2|...) */
+void memtest_fill_value(unsigned long *l, size_t bytes, unsigned long v1,
+                        unsigned long v2, char sym)
+{
+    unsigned long step = 4096/sizeof(unsigned long);
+    unsigned long words = bytes/sizeof(unsigned long)/2;
+    unsigned long iwords = words/step;  /* words per iteration */
+    unsigned long off, w, *l1, *l2, v;
+
+    assert((bytes & 4095) == 0);
+    for (off = 0; off < step; off++) {
+        l1 = l+off;
+        l2 = l1+words;
+        v = (off & 1) ? v2 : v1;
+        for (w = 0; w < iwords; w++) {
+#ifdef MEMTEST_32BIT
+            *l1 = *l2 = ((unsigned long)     (rand()&0xffff)) |
+                        (((unsigned long)    (rand()&0xffff)) << 16);
+#else
+            *l1 = *l2 = ((unsigned long)     (rand()&0xffff)) |
+                        (((unsigned long)    (rand()&0xffff)) << 16) |
+                        (((unsigned long)    (rand()&0xffff)) << 32) |
+                        (((unsigned long)    (rand()&0xffff)) << 48);
+#endif
+            l1 += step;
+            l2 += step;
+            if ((w & 0xffff) == 0)
+                memtest_progress_step(w+iwords*off,words,sym);
         }
     }
 }
@@ -99,10 +140,20 @@ void memtest_compare(unsigned long *l, size_t bytes) {
     }
 }
 
+void memtest_compare_times(unsigned long *m, size_t bytes, int pass, int times) {
+    int j;
+
+    for (j = 0; j < times; j++) {
+        memtest_progress_start("Compare",pass);
+        memtest_compare(m,bytes);
+        memtest_progress_end();
+    }
+}
+
 void memtest_test(size_t megabytes, int passes) {
     size_t bytes = megabytes*1024*1024;
     unsigned long *m = malloc(bytes);
-    int pass = 0, j;
+    int pass = 0;
 
     if (m == NULL) {
         fprintf(stderr,"Unable to allocate %zu megabytes: %s",
@@ -112,13 +163,19 @@ void memtest_test(size_t megabytes, int passes) {
     while (pass != passes) {
         pass++;
         memtest_progress_start("Random fill",pass);
-        memtest_fill(m,bytes);
+        memtest_fill_random(m,bytes);
         memtest_progress_end();
-        for (j = 0; j < 4; j++) {
-            memtest_progress_start("Compare",pass);
-            memtest_compare(m,bytes);
-            memtest_progress_end();
-        }
+        memtest_compare_times(m,bytes,pass,4);
+
+        memtest_progress_start("Solid fill",pass);
+        memtest_fill_value(m,bytes,0,(unsigned long)-1,'S');
+        memtest_progress_end();
+        memtest_compare_times(m,bytes,pass,4);
+
+        memtest_progress_start("Checkerboard fill",pass);
+        memtest_fill_value(m,bytes,ULONG_ONEZERO,ULONG_ZEROONE,'C');
+        memtest_progress_end();
+        memtest_compare_times(m,bytes,pass,4);
     }
 }
 