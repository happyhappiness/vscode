static void reqtimeout_hooks(apr_pool_t *pool)
{
    /*
     * mod_ssl is AP_FTYPE_CONNECTION + 5 and mod_reqtimeout needs to
     * be called before mod_ssl. Otherwise repeated reads during the ssl
     * handshake can prevent the timeout from triggering.
     */
    ap_register_input_filter(reqtimeout_filter_name, reqtimeout_filter, NULL,
                             AP_FTYPE_CONNECTION + 8);

    /*
     * mod_reqtimeout needs to be called before ap_process_http_request (which
     * is run at APR_HOOK_REALLY_LAST) but after all other protocol modules.
     * This ensures that it only influences normal http connections and not
     * e.g. mod_ftp. Also, if mod_reqtimeout used the pre_connection hook, it
     * would be inserted on mod_proxy's backend connections.
     */
    ap_hook_process_connection(reqtimeout_init, NULL, NULL, APR_HOOK_LAST);

    ap_hook_post_read_request(reqtimeout_after_headers, NULL, NULL,
                              APR_HOOK_MIDDLE);
    ap_hook_log_transaction(reqtimeout_after_body, NULL, NULL,
                            APR_HOOK_MIDDLE);
}