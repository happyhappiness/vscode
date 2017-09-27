 *                         ap_add_loaded_module. Add ap_find_module_short_name
 * 20100723.0 (2.3.7-dev)  Remove ct_output_filters from core rec
 * 20100723.1 (2.3.7-dev)  Added ap_proxy_hashfunc() and hash elements to
 *                         proxy worker structs
 * 20100723.2 (2.3.7-dev)  Add ap_request_has_body()
 * 20100723.3 (2.3.8-dev)  Add ap_check_mpm()
 * 20100905.0 (2.3.9-dev)  Add log_id to conn and req recs. Add error log
 *                         format handlers. Support AP_CTIME_OPTION_COMPACT in
 *                         ap_recent_ctime_ex().
 * 20100905.1 (2.3.9-dev)  Add ap_cache_check_allowed()
 * 20100912.0 (2.3.9-dev)  Add an additional "out" brigade parameter to the
 *                         mod_cache store_body() provider function.
 * 20100916.0 (2.3.9-dev)  Add commit_entity() to the mod_cache provider
 *                         interface.
 * 20100918.0 (2.3.9-dev)  Move the request_rec within mod_include to be
 *                         exposed within include_ctx_t.
 * 20100919.0 (2.3.9-dev)  Authz providers: Add parsed_require_line parameter
 *                         to check_authorization() function. Add
 *                         parse_require_line() function.
 * 20100919.1 (2.3.9-dev)  Introduce ap_rxplus util/API
 * 20100921.0 (2.3.9-dev)  Add an apr_bucket_brigade to the create_entity
 *                         provider interface for mod_cache.h.
 * 20100922.0 (2.3.9-dev)  Move cache_* functions from mod_cache.h to a
 *                         private header file.
 * 20100923.0 (2.3.9-dev)  Remove MOD_CACHE_REQUEST_REC, remove deprecated
 *                         ap_cache_cacheable_hdrs_out, trim cache_object_t,
 *                         make ap_cache_accept_headers, ap_cache_accept_headers
 *                         ap_cache_try_lock, ap_cache_check_freshness,
 *                         cache_server_conf, cache_enable, cache_disable,
 *                         cache_request_rec and cache_provider_list private.
 * 20100923.1 (2.3.9-dev)  Add cache_status hook.
 * 20100923.2 (2.3.9-dev)  Add generate_log_id hook.
 *                         Make root parameter of ap_expr_eval() const.
 * 20100923.3 (2.3.9-dev)  Add "last" member to ap_directive_t
 * 20101012.0 (2.3.9-dev)  Add header to cache_status hook.
 * 20101016.0 (2.3.9-dev)  Remove ap_cache_check_allowed().
 * 20101017.0 (2.3.9-dev)  Make ap_cache_control() public, add cache_control_t
 *                         to mod_disk_cache format.
 * 20101106.0 (2.3.9-dev)  Replace the ap_expr parser derived from
 *                         mod_include's parser with one derived from
 *                         mod_ssl's parser. Clean up ap_expr's public
 *                         interface.
 * 20101106.1 (2.3.9-dev)  Add ap_pool_cleanup_set_null() generic cleanup
 * 20101106.2 (2.3.9-dev)  Add suexec_disabled_reason field to ap_unixd_config
 * 20101113.0 (2.3.9-dev)  Add source address to mod_proxy.h
 * 20101113.1 (2.3.9-dev)  Add ap_set_flag_slot_char()
 * 20101113.2 (2.3.9-dev)  Add ap_expr_exec_re()
 * 20101204.0 (2.3.10-dev) Add _t to ap_expr's typedef names
 * 20101223.0 (2.3.11-dev) Remove cleaned from proxy_conn_rec.
 * 20101223.1 (2.3.11-dev) Rework mod_proxy, et.al. Remove proxy_worker_stat
 *                         and replace w/ proxy_worker_shared; remove worker
 *                         info from scoreboard and use slotmem; Allow
 *                         dynamic growth of balancer members; Remove
 *                         BalancerNonce in favor of 'nonce' parameter.
 * 20110117.0 (2.3.11-dev) Merge <If> sections in separate step (ap_if_walk).
 *                         Add core_dir_config->sec_if. Add ap_add_if_conf().
 *                         Add pool argument to ap_add_file_conf().
 * 20110117.1 (2.3.11-dev) Add ap_pstr2_alnum() and ap_str2_alnum()
 * 20110203.0 (2.3.11-dev) Raise DYNAMIC_MODULE_LIMIT to 256
 * 20110203.1 (2.3.11-dev) Add ap_state_query()
 * 20110203.2 (2.3.11-dev) Add ap_run_pre_read_request() hook and
 *                         ap_parse_form_data() util
 * 20110312.0 (2.3.12-dev) remove uldap_connection_cleanup and add
                           util_ldap_state_t.connectionPoolTTL,
                           util_ldap_connection_t.freed, and
                           util_ldap_connection_t.rebind_pool.
 * 20110312.1 (2.3.12-dev) Add core_dir_config.decode_encoded_slashes.
 * 20110328.0 (2.3.12-dev) change type and name of connectionPoolTTL in util_ldap_state_t
                           connectionPoolTTL (connection_pool_ttl, int->apr_interval_t)
 * 20110329.0 (2.3.12-dev) Change single-bit signed fields to unsigned in
 *                         proxy and cache interfaces.
 *                         Change ap_configfile_t/ap_cfg_getline()/
 *                         ap_cfg_getc() API, add ap_pcfg_strerror()
 *                         Axe mpm_note_child_killed hook, change
 *                         ap_reclaim_child_process and ap_recover_child_process
 *                         interfaces.
 * 20110329.1 (2.3.12-dev) Add ap_reserve_module_slots()/ap_reserve_module_slots_directive()
 *                         change AP_CORE_DECLARE to AP_DECLARE: ap_create_request_config()
 *                         change AP_DECLARE to AP_CORE_DECLARE: ap_register_log_hooks()
 * 20110329.2 (2.3.12-dev) Add child_status and end_generation hooks.
 * 20110329.3 (2.3.12-dev) Add format field to ap_errorlog_info.
 * 20110329.4 (2.3.13-dev) bgrowth and max_balancers to proxy_server_conf.
 * 20110329.5 (2.3.13-dev) Add ap_regexec_len()
 * 20110329.6 (2.3.13-dev) Add AP_EXPR_FLAGS_RESTRICTED, ap_expr_eval_ctx_t->data,
 *                         ap_expr_exec_ctx()
 * 20110604.0 (2.3.13-dev) Make ap_rputs() inline
 * 20110605.0 (2.3.13-dev) add core_dir_config->condition_ifelse, change return
 *                         type of ap_add_if_conf().
 *                         Add members of core_request_config: document_root,
 *                         context_document_root, context_prefix.
 *                         Add ap_context_*(), ap_set_context_info(), ap_set_document_root()
 * 20110605.1 (2.3.13-dev) add ap_(get|set)_core_module_config()
 * 20110605.2 (2.3.13-dev) add ap_get_conn_socket()
 * 20110619.0 (2.3.13-dev) add async connection infos to process_score in scoreboard,
 *                         add ap_start_lingering_close(),
 *                         add conn_state_e:CONN_STATE_LINGER_NORMAL and CONN_STATE_LINGER_SHORT
 * 20110619.1 (2.3.13-dev) add ap_str_toupper()
 * 20110702.0 (2.3.14-dev) make ap_expr_parse_cmd() macro wrapper for new
 *                         ap_expr_parse_cmd_mi() function, add ap_expr_str_*() functions,
 *                         rename AP_EXPR_FLAGS_* -> AP_EXPR_FLAG_*
 * 20110702.1 (2.3.14-dev) Add ap_scan_script_header_err*_ex functions
 * 20110723.0 (2.3.14-dev) Revert addition of ap_ldap*
 * 20110724.0 (2.3.14-dev) Add override_list as parameter to ap_parse_htaccess
 *                         Add member override_list to cmd_parms_struct,
 *                         core_dir_config and htaccess_result
 * 20110724.1 (2.3.15-dev) add NOT_IN_HTACCESS
 * 20110724.2 (2.3.15-dev) retries and retry_delay in util_ldap_state_t
 * 20110724.3 (2.3.15-dev) add util_varbuf.h / ap_varbuf API
 * 20110724.4 (2.3.15-dev) add max_ranges to core_dir_config
 * 20110724.5 (2.3.15-dev) add ap_set_accept_ranges()
 * 20110724.6 (2.3.15-dev) add max_overlaps and max_reversals to core_dir_config
 * 20110724.7 (2.3.15-dev) add ap_random_insecure_bytes(), ap_random_pick()
 * 20110724.8 (2.3.15-dev) add ap_abort_on_oom(), ap_malloc(), ap_calloc(),
 *                         ap_realloc()
 * 20110724.9 (2.3.15-dev) add ap_varbuf_pdup() and ap_varbuf_regsub()
 * 20110724.10(2.3.15-dev) Export ap_max_mem_free
 * 20111009.0 (2.3.15-dev) Remove ap_proxy_removestr(),
 *                         add ap_unixd_config.group_name
 * 20111014.0 (2.3.15-dev) Remove cookie_path_str and cookie_domain_str from
 *                         proxy_dir_conf
 * 20111025.0 (2.3.15-dev) Add return value and maxlen to ap_varbuf_regsub(),
 *                         add ap_pregsub_ex()
 * 20111025.1 (2.3.15-dev) Add ap_escape_urlencoded(), ap_escape_urlencoded_buffer()
 *                         and ap_unescape_urlencoded().
 * 20111025.2 (2.3.15-dev) Add ap_lua_ssl_val to mod_lua
 * 20111025.3 (2.4.0-dev)  Add reclvl to ap_expr_eval_ctx_t
 * 20111122.0 (2.4.0-dev)  Remove parts of conn_state_t that are private to the MPM
 * 20111123.0 (2.4.0-dev)  Pass ap_errorlog_info struct to error_log hook,
 *                         add pool to ap_errorlog_info.
 * 20111130.0 (2.4.0-dev)  c->remote_ip becomes c->peer_ip and r->client_ip,
 *                         c->remote_addr becomes c->peer_addr and r->client_addr
 * 20111201.0 (2.4.0-dev)  Add invalidate_entity() to the cache provider.
 * 20111202.0 (2.4.0-dev)  Use apr_status_t across mod_session API.
 * 20111202.1 (2.4.0-dev)  add APLOGNO()
 * 20111203.0 (2.4.0-dev)  Optional ap_proxy_retry_worker(), remove
 *                         ap_proxy_string_read(), ap_cache_liststr(),
 *                         ap_proxy_buckets_lifetime_transform(),
 *                         ap_proxy_date_canon(), ap_proxy_is_ipaddr(),
 *                         ap_proxy_is_domainname(), ap_proxy_is_hostname(),
 *                         ap_proxy_is_word(), ap_proxy_hex2sec(),
 *                         ap_proxy_sec2hex(), ap_proxy_make_fake_req(),
 *                         ap_proxy_strmatch_path, ap_proxy_strmatch_domain,
 *                         ap_proxy_table_unmerge(), proxy_lb_workers.
 * 20120109.0 (2.4.1-dev)  Changes sizeof(overrides_t) in core config.
 * 20120109.1 (2.4.1-dev)  remove sb_type in global_score.
 * 20120109.2 (2.4.1-dev)  Make core_output_filter_ctx_t and core_ctx_t
 *                         private;
 *                         move core_net rec definition to http_core.h;
 *                         add insert_network_bucket hook, AP_DECLINED
 * 20120211.0 (2.4.1-dev)  Change re_nsub in ap_regex_t from apr_size_t to int.
 */

#define MODULE_MAGIC_COOKIE 0x41503234UL /* "AP24" */

#ifndef MODULE_MAGIC_NUMBER_MAJOR
#define MODULE_MAGIC_NUMBER_MAJOR 20120211
#endif
#define MODULE_MAGIC_NUMBER_MINOR 0                   /* 0...n */

/**
 * Determine if the server's current MODULE_MAGIC_NUMBER is at least a
 * specified value.
 *
 * Useful for testing for features.
