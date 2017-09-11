@@ -47,7 +47,7 @@ void memtest_progress_end(void) {
 }
 
 void memtest_progress_step(size_t curr, size_t size, char c) {
-    size_t chars = (curr*progress_full)/size, j;
+    size_t chars = ((unsigned long long)curr*progress_full)/size, j;
 
     for (j = 0; j < chars-progress_printed; j++) {
         printf("%c",c);