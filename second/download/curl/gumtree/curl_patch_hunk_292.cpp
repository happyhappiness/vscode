     return 0;
   }
   warnf(config, "You can only select one HTTP request!\n");
   return 1;
 }
 
-static void helpf(const char *fmt, ...)
+static void helpf(FILE *errors, const char *fmt, ...)
 {
   va_list ap;
   if(fmt) {
     va_start(ap, fmt);
-    fputs("curl: ", stderr); /* prefix it */
-    vfprintf(stderr, fmt, ap);
+    fputs("curl: ", errors); /* prefix it */
+    vfprintf(errors, fmt, ap);
     va_end(ap);
   }
-  fprintf(stderr, "curl: try 'curl --help' "
+  fprintf(errors, "curl: try 'curl --help' "
 #ifdef USE_MANUAL
           "or 'curl --manual' "
 #endif
           "for more information\n");
 }
 
