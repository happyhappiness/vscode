         return log_scripterror(r, conf, HTTP_FORBIDDEN, 0,
                                "Options ExecCGI is off in this directory");
     if (nph && is_included)
         return log_scripterror(r, conf, HTTP_FORBIDDEN, 0,
                                "attempt to include NPH CGI script");
 
-    if (r->finfo.filetype == 0)
+    if (r->finfo.filetype == APR_NOFILE)
         return log_scripterror(r, conf, HTTP_NOT_FOUND, 0,
                                "script not found or unable to stat");
     if (r->finfo.filetype == APR_DIR)
         return log_scripterror(r, conf, HTTP_FORBIDDEN, 0,
                                "attempt to invoke directory as script");
 
