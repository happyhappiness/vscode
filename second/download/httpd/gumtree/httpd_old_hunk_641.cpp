 * 20020529 (2.0.37-dev) Standardized the names of some apr_pool_*_set funcs
 * 20020602 (2.0.37-dev) Bucket API change (metadata buckets)
 * 20020612 (2.0.38-dev) Changed server_rec->[keep_alive_]timeout to apr time
 * 20020625 (2.0.40-dev) Changed conn_rec->keepalive to an enumeration
 * 20020628 (2.0.40-dev) Added filter_init to filter registration functions
 * 20020903 (2.0.41-dev) APR's error constants changed
 * 20020903.2 (2.0.46-dev) add ap_escape_logitem
 * 20020903.3 (2.0.46-dev) allow_encoded_slashes added to core_dir_config
 * 20020903.4 (2.0.47-dev) add ap_is_recursion_limit_exceeded()
 * 20020903.5 (2.0.49-dev) add ap_escape_errorlog_item()
 * 20020903.6 (2.0.49-dev) add insert_error_filter hook
 * 20020903.7 (2.0.49-dev) added XHTML Doctypes
 * 20020903.8 (2.0.50-dev) export ap_set_sub_req_protocol and
 *                         ap_finalize_sub_req_protocol on Win32 and NetWare
 * 20020903.9 (2.0.51-dev) create pcommands and initialize arrays before
 *                         calling ap_setup_prelinked_modules
 * 20020903.10 (2.0.55-dev) add ap_log_cerror()
 * 20020903.11 (2.0.55-dev) added trace_enable to core_server_config
 * 20020903.12 (2.0.56-dev) added ap_get_server_revision / ap_version_t
 * 20020903.13 (2.0.62-dev) Add *ftp_directory_charset to proxy_dir_conf
 * 20020903.14 (2.0.64-dev) added ap_vhost_iterate_given_conn
 * 20020903.15 (2.0.65-dev) added state_set, options_set, baseurl_set to
 *                          rewrite_server_conf and rewrite_perdir_conf
 * 20020903.16 (2.0.65)     add max_ranges to core_dir_config and add
 *                          ap_set_accept_ranges()
 */

#define MODULE_MAGIC_COOKIE 0x41503230UL /* "AP20" */

#ifndef MODULE_MAGIC_NUMBER_MAJOR
#define MODULE_MAGIC_NUMBER_MAJOR 20020903
#endif
#define MODULE_MAGIC_NUMBER_MINOR 16                    /* 0...n */

/**
 * Determine if the server's current MODULE_MAGIC_NUMBER is at least a
 * specified value.
 * <pre>
 * Useful for testing for features.
