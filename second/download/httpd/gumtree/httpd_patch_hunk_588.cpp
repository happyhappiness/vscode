  * 20020529 (2.0.37-dev) Standardized the names of some apr_pool_*_set funcs
  * 20020602 (2.0.37-dev) Bucket API change (metadata buckets)
  * 20020612 (2.0.38-dev) Changed server_rec->[keep_alive_]timeout to apr time
  * 20020625 (2.0.40-dev) Changed conn_rec->keepalive to an enumeration
  * 20020628 (2.0.40-dev) Added filter_init to filter registration functions
  * 20020903 (2.0.41-dev) APR's error constants changed
+ * 20020903.1 (2.1.0-dev) allow_encoded_slashes added to core_dir_config
  * 20020903.2 (2.0.46-dev) add ap_escape_logitem
- * 20020903.3 (2.0.46-dev) allow_encoded_slashes added to core_dir_config
- * 20020903.4 (2.0.47-dev) add ap_is_recursion_limit_exceeded()
- * 20020903.5 (2.0.49-dev) add ap_escape_errorlog_item()
- * 20020903.6 (2.0.49-dev) add insert_error_filter hook
- * 20020903.7 (2.0.49-dev) added XHTML Doctypes
- * 20020903.8 (2.0.50-dev) export ap_set_sub_req_protocol and
- *                         ap_finalize_sub_req_protocol on Win32 and NetWare
- * 20020903.9 (2.0.51-dev) create pcommands and initialize arrays before
- *                         calling ap_setup_prelinked_modules
- * 20020903.10 (2.0.55-dev) add ap_log_cerror()
- * 20020903.11 (2.0.55-dev) added trace_enable to core_server_config
- * 20020903.12 (2.0.56-dev) added ap_get_server_revision / ap_version_t
- * 20020903.13 (2.0.62-dev) Add *ftp_directory_charset to proxy_dir_conf
- * 20020903.14 (2.0.64-dev) added ap_vhost_iterate_given_conn
- * 20020903.15 (2.0.65-dev) added state_set, options_set, baseurl_set to
- *                          rewrite_server_conf and rewrite_perdir_conf
- * 20020903.16 (2.0.65)     add max_ranges to core_dir_config and add
- *                          ap_set_accept_ranges()
+ * 20030213.1 (2.1.0-dev) changed log_writer optional fn's to return previous
+ *                        handler
+ * 20030821 (2.1.0-dev) bumped mod_include's entire API
+ * 20030821.1 (2.1.0-dev) added XHTML doctypes
+ * 20030821.2 (2.1.0-dev) added ap_escape_errorlog_item
+ * 20030821.3 (2.1.0-dev) added ap_get_server_revision / ap_version_t
+ * 20040425 (2.1.0-dev) removed ap_add_named_module API
+ *                      changed ap_add_module, ap_add_loaded_module,
+ *                      ap_setup_prelinked_modules, ap_process_resource_config
+ * 20040425.1 (2.1.0-dev) Added ap_module_symbol_t and ap_prelinked_module_symbols
+ * 20050101.0 (2.1.2-dev) Axed misnamed http_method for http_scheme (which it was!)
+ * 20050127.0 (2.1.3-dev) renamed regex_t->ap_regex_t, regmatch_t->ap_regmatch_t,
+ *                        REG_*->AP_REG_*, removed reg* in place of ap_reg*;
+ *                        added ap_regex.h
+ * 20050217.0 (2.1.3-dev) Axed find_child_by_pid, mpm_*_completion_context (winnt mpm)
+ *                        symbols from the public sector, and decorated real_exit_code
+ *                        with ap_ in the win32 os.h.
+ * 20050305.0 (2.1.4-dev) added pid and generation fields to worker_score
+ * 20050305.1 (2.1.5-dev) added ap_vhost_iterate_given_conn.
+ * 20050305.2 (2.1.5-dev) added AP_INIT_TAKE_ARGV.
+ * 20050305.3 (2.1.5-dev) added Protocol Framework.
+ * 20050701.0 (2.1.7-dev) Bump MODULE_MAGIC_COOKIE to "AP21"!
+ * 20050701.1 (2.1.7-dev) trace_enable member added to core server_config
+ * 20050708.0 (2.1.7-dev) Bump MODULE_MAGIC_COOKIE to "AP22"!
+ * 20050708.1 (2.1.7-dev) add proxy request_status hook (minor)
+ * 20051006.0 (2.1.8-dev) NET_TIME filter eliminated
+ * 20051115.0 (2.1.10-dev/2.2.0) add use_canonical_phys_port to core_dir_config
  */
 
-#define MODULE_MAGIC_COOKIE 0x41503230UL /* "AP20" */
+#define MODULE_MAGIC_COOKIE 0x41503232UL /* "AP22" */
 
 #ifndef MODULE_MAGIC_NUMBER_MAJOR
-#define MODULE_MAGIC_NUMBER_MAJOR 20020903
+#define MODULE_MAGIC_NUMBER_MAJOR 20051115
 #endif
-#define MODULE_MAGIC_NUMBER_MINOR 16                    /* 0...n */
+#define MODULE_MAGIC_NUMBER_MINOR 0                     /* 0...n */
 
 /**
  * Determine if the server's current MODULE_MAGIC_NUMBER is at least a
  * specified value.
  * <pre>
  * Useful for testing for features.
