     printf(" -D BUFFERED_LOGS\n");
 #ifdef PIPE_BUF
     printf(" -D PIPE_BUF=%ld\n",(long)PIPE_BUF);
 #endif
 #endif
 
+    printf(" -D DYNAMIC_MODULE_LIMIT=%ld\n",(long)DYNAMIC_MODULE_LIMIT);
+
 #if APR_CHARSET_EBCDIC
     printf(" -D APR_CHARSET_EBCDIC\n");
 #endif
 
-#ifdef APACHE_XLATE
-    printf(" -D APACHE_XLATE\n");
-#endif
-
 #ifdef NEED_HASHBANG_EMUL
     printf(" -D NEED_HASHBANG_EMUL\n");
 #endif
 
 #ifdef SHARED_CORE
     printf(" -D SHARED_CORE\n");
