@@ -2547,6 +2547,15 @@ void bytesToHuman(char *s, unsigned long long n) {
     } else if (n < (1024LL*1024*1024*1024)) {
         d = (double)n/(1024LL*1024*1024);
         sprintf(s,"%.2fG",d);
+    } else if (n < (1024LL*1024*1024*1024*1024)) {
+        d = (double)n/(1024LL*1024*1024*1024);
+        sprintf(s,"%.2fT",d);
+    } else if (n < (1024LL*1024*1024*1024*1024*1024)) {
+        d = (double)n/(1024LL*1024*1024*1024*1024);
+        sprintf(s,"%.2fP",d);
+    } else {
+        /* Let's hope we never need this */
+        sprintf(s,"%lluB",n);
     }
 }
 