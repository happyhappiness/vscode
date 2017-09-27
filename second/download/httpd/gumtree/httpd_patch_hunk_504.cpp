  * 20020903.6 (2.0.49-dev) add insert_error_filter hook
  * 20020903.7 (2.0.49-dev) added XHTML Doctypes
  * 20020903.8 (2.0.50-dev) export ap_set_sub_req_protocol and
  *                         ap_finalize_sub_req_protocol on Win32 and NetWare
  * 20020903.9 (2.0.51-dev) create pcommands and initialize arrays before
  *                         calling ap_setup_prelinked_modules
+ * 20020903.10 (2.0.55-dev) add ap_log_cerror()
+ * 20020903.11 (2.0.55-dev) added trace_enable to core_server_config
  */
 
 #define MODULE_MAGIC_COOKIE 0x41503230UL /* "AP20" */
 
 #ifndef MODULE_MAGIC_NUMBER_MAJOR
 #define MODULE_MAGIC_NUMBER_MAJOR 20020903
 #endif
-#define MODULE_MAGIC_NUMBER_MINOR 9                     /* 0...n */
+#define MODULE_MAGIC_NUMBER_MINOR 11                    /* 0...n */
 
 /**
  * Determine if the server's current MODULE_MAGIC_NUMBER is at least a
  * specified value.
  * <pre>
  * Useful for testing for features.
