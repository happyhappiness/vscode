     isa->report_version = 0x500; /* Revision 5.0 */
     isa->timeout = 300 * 1000000; /* microsecs, not used */
 
     rv = apr_dso_load(&isa->handle, isa->filename, p);
     if (rv)
     {
-        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
-                     "ISAPI: failed to load %s", isa->filename);
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(02107)
+                     "failed to load %s", isa->filename);
         isa->handle = NULL;
         return rv;
     }
 
     rv = apr_dso_sym((void**)&isa->GetExtensionVersion, isa->handle,
                      "GetExtensionVersion");
     if (rv)
     {
-        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
-                     "ISAPI: missing GetExtensionVersion() in %s",
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(02108)
+                     "missing GetExtensionVersion() in %s",
                      isa->filename);
         apr_dso_unload(isa->handle);
         isa->handle = NULL;
         return rv;
     }
 
     rv = apr_dso_sym((void**)&isa->HttpExtensionProc, isa->handle,
                      "HttpExtensionProc");
     if (rv)
     {
-        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
-                     "ISAPI: missing HttpExtensionProc() in %s",
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(02109)
+                     "missing HttpExtensionProc() in %s",
                      isa->filename);
         apr_dso_unload(isa->handle);
         isa->handle = NULL;
         return rv;
     }
 
