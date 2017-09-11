@@ -958,8 +958,8 @@ unsigned long long sendSync(int fd) {
             fprintf(stderr,"Error reading bulk length while SYNCing\n");
             exit(1);
         }
-        if (*p == '\n') break;
-        p++;
+        if (*p == '\n' && p != buf) break;
+        if (*p != '\n') p++;
     }
     *p = '\0';
     if (buf[0] == '-') {