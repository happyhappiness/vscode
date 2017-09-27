      *
      * The tricky bit, they aren't really a per-dir sort of
      * config, they will always be constant across every
      * reference to the .dll no matter what context (vhost,
      * location, etc) they apply to.
      */
-    isa->report_version = MAKELONG(0, 5); /* Revision 5.0 */
+    isa->report_version = 0x500; /* Revision 5.0 */
     isa->timeout = 300 * 1000000; /* microsecs, not used */
 
     rv = apr_dso_load(&isa->handle, isa->filename, p);
     if (rv)
     {
         ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
