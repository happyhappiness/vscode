 #ifdef PKZIP_BUG_WORKAROUND
     flags += 1L << 20;
 #endif
 #ifdef FASTEST
     flags += 1L << 21;
 #endif
-#ifdef STDC
+#if defined(STDC) || defined(Z_HAVE_STDARG_H)
 #  ifdef NO_vsnprintf
-        flags += 1L << 25;
+    flags += 1L << 25;
 #    ifdef HAS_vsprintf_void
-        flags += 1L << 26;
+    flags += 1L << 26;
 #    endif
 #  else
 #    ifdef HAS_vsnprintf_void
-        flags += 1L << 26;
+    flags += 1L << 26;
 #    endif
 #  endif
 #else
-        flags += 1L << 24;
+    flags += 1L << 24;
 #  ifdef NO_snprintf
-        flags += 1L << 25;
+    flags += 1L << 25;
 #    ifdef HAS_sprintf_void
-        flags += 1L << 26;
+    flags += 1L << 26;
 #    endif
 #  else
 #    ifdef HAS_snprintf_void
-        flags += 1L << 26;
+    flags += 1L << 26;
 #    endif
 #  endif
 #endif
     return flags;
 }
 
 #ifdef DEBUG
 
 #  ifndef verbose
 #    define verbose 0
 #  endif
-int z_verbose = verbose;
+int ZLIB_INTERNAL z_verbose = verbose;
 
-void z_error (m)
+void ZLIB_INTERNAL z_error (m)
     char *m;
 {
     fprintf(stderr, "%s\n", m);
     exit(1);
 }
 #endif
