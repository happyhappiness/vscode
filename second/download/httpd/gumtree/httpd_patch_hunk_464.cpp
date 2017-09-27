         argv0++;
     else
         argv0 = r->filename;
  
     nph = !(strncmp(argv0, "nph-", 4)); 
 
-    if ((argv0 = strrchr(r->filename, '/')) != NULL) 
-        argv0++; 
-    else 
-        argv0 = r->filename; 
+    argv0 = r->filename; 
 
     if (!(ap_allow_options(r) & OPT_EXECCGI) && !is_scriptaliased(r)) 
         return log_scripterror(r, conf, HTTP_FORBIDDEN, 0, 
                                "Options ExecCGI is off in this directory"); 
     if (nph && is_included) 
         return log_scripterror(r, conf, HTTP_FORBIDDEN, 0, 
