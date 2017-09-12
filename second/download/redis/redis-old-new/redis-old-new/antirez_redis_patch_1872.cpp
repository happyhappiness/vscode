@@ -538,7 +538,8 @@ void printErrorStack(entry *e) {
 
     /* display error stack */
     for (i = 0; i < errors.level; i++) {
-        printf("0x%08lx - %s\n", errors.offset[i], errors.error[i]);
+        printf("0x%08lx - %s\n",
+            (unsigned long) errors.offset[i], errors.error[i]);
     }
 }
 