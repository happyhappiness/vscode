                                "attempt to include NPH CGI script");
 
 #if defined(OS2) || defined(WIN32)
 #error mod_cgid does not work on this platform.  If you teach it to, look
 #error at mod_cgi.c for required code in this path.
 #else
-    if (r->finfo.filetype == 0)
+    if (r->finfo.filetype == APR_NOFILE)
         return log_scripterror(r, conf, HTTP_NOT_FOUND, 0,
                                "script not found or unable to stat");
 #endif
     if (r->finfo.filetype == APR_DIR)
         return log_scripterror(r, conf, HTTP_FORBIDDEN, 0,
                                "attempt to invoke directory as script");
