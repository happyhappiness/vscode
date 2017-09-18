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
