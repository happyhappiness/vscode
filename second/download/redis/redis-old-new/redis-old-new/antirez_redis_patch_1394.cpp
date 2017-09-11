@@ -4,6 +4,8 @@
 #include <assert.h>
 #include <limits.h>
 #include <errno.h>
+#include <termios.h>
+#include <sys/ioctl.h>
 
 #if (ULONG_MAX == 4294967295UL)
 #define MEMTEST_32BIT
@@ -13,6 +15,37 @@
 #error "ULONG_MAX value not supported."
 #endif
 
+static struct winsize ws;
+size_t progress_printed; /* Printed chars in screen-wide progress bar. */
+size_t progress_full; /* How many chars to write to fill the progress bar. */
+
+void memtest_progress_start(char *title, int pass) {
+    int j;
+
+    printf("\x1b[H\x1b[2J");    /* Cursor home, clear screen. */
+    /* Fill with dots. */
+    for (j = 0; j < ws.ws_col*ws.ws_row; j++) printf(".");
+    printf("\x1b[H\x1b[2K");          /* Cursor home, clear current line.  */
+    printf("%s [%d]\n", title, pass); /* Print title. */
+    progress_printed = 0;
+    progress_full = ws.ws_col*(ws.ws_row-1);
+    fflush(stdout);
+}
+
+void memtest_progress_end(void) {
+    printf("\x1b[H\x1b[2J");    /* Cursor home, clear screen. */
+}
+
+void memtest_progress_step(size_t curr, size_t size, char c) {
+    size_t chars = (curr*progress_full)/size, j;
+
+    for (j = 0; j < chars-progress_printed; j++) {
+        printf("%c",c);
+        progress_printed++;
+    }
+    fflush(stdout);
+}
+
 /* Fill words stepping a single page at every write, so we continue to
  * touch all the pages in the smallest amount of time reducing the
  * effectiveness of caches, and making it hard for the OS to transfer
@@ -39,6 +72,8 @@ void memtest_fill(unsigned long *l, size_t bytes) {
 #endif
             l1 += step;
             l2 += step;
+            if ((w & 0xffff) == 0)
+                memtest_progress_step(w+iwords*off,words,'+');
         }
     }
 }
@@ -58,13 +93,14 @@ void memtest_compare(unsigned long *l, size_t bytes) {
         }
         l1 ++;
         l2 ++;
+        if ((w & 0xffff) == 0) memtest_progress_step(w,words,'=');
     }
 }
 
 void memtest_test(size_t megabytes, int passes) {
     size_t bytes = megabytes*1024*1024;
     unsigned long *m = malloc(bytes);
-    int pass = 0;
+    int pass = 0, j;
 
     if (m == NULL) {
         fprintf(stderr,"Unable to allocate %zu megabytes: %s",
@@ -73,15 +109,22 @@ void memtest_test(size_t megabytes, int passes) {
     }
     while (pass != passes) {
         pass++;
-        printf("PASS %d... ", pass);
-        fflush(stdout);
+        memtest_progress_start("Random fill",pass);
         memtest_fill(m,bytes);
-        memtest_compare(m,bytes);
-        printf("ok\n");
+        memtest_progress_end();
+        for (j = 0; j < 4; j++) {
+            memtest_progress_start("Compare",pass);
+            memtest_compare(m,bytes);
+            memtest_progress_end();
+        }
     }
 }
 
 void memtest(size_t megabytes, int passes) {
+    if (ioctl(1, TIOCGWINSZ, &ws) == -1) {
+        ws.ws_col = 80;
+        ws.ws_row = 20;
+    }
     memtest_test(megabytes,passes);
     printf("\nYour memory passed this test.\n");
     printf("Please if you are stil in doubt use the following two tools:\n");