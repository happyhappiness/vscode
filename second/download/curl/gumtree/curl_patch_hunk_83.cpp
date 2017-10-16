   if(fmt) {
     va_start(ap, fmt);
     fputs("curl: ", stderr); /* prefix it */
     vfprintf(stderr, fmt, ap);
     va_end(ap);
   }
-  fprintf(stderr, "curl: try 'curl --help' or "
-          "'curl --manual' for more information\n");
+  fprintf(stderr, "curl: try 'curl --help' "
+#ifdef USE_MANUAL
+          "or 'curl --manual' "
+#endif
+          "for more information\n");
 }
 
 /*
  * A chain of these nodes contain URL to get and where to put the URL's
  * contents.
  */
