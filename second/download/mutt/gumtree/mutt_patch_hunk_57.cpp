 #if ICONV_NONTRANS
 	"+ICONV_NONTRANS  "
 #else
 	"-ICONV_NONTRANS  "
 #endif
 
+#if HAVE_LIBIDN
+	"+HAVE_LIBIDN  "
+#else
+	"-HAVE_LIBIDN  "
+#endif
+	
 #if HAVE_GETSID
 	"+HAVE_GETSID  "
 #else
 	"-HAVE_GETSID  "
 #endif
 
-#if HAVE_GETADDRINFO
-	"+HAVE_GETADDRINFO  "
+#if USE_HCACHE
+	"+USE_HCACHE  "
 #else
-	"-HAVE_GETADDRINFO  "
+	"-USE_HCACHE  "
 #endif
 
 	);
 
 #ifdef ISPELL
   printf ("ISPELL=\"%s\"\n", ISPELL);
