 #endif /* DEBUG */
 #else /* __GNUC__ */
 static void
 debug(char *format,...)
 {
 #ifdef DEBUG
-#if _SQUID_MSWIN_
+#if _SQUID_WINDOWS_
     if (debug_enabled) {
         va_list args;
 
         va_start(args,format);
         fprintf(stderr, "nt_auth[%d]: ",getpid());
         vfprintf(stderr, format, args);
         va_end(args);
     }
-#endif /* _SQUID_MSWIN_ */
+#endif /* _SQUID_WINDOWS_ */
 #endif /* DEBUG */
 }
 #endif /* __GNUC__ */
 
 int Valid_User(char *,char *, char *);
 
