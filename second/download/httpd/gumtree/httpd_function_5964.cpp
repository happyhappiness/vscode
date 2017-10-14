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
     * We need to pause timeout detection in between requests, for
     * speculative and non-blocking reads, so between each outgoing EOR
     * and the next pre_read_request call.
     */
    ap_register_output_filter(reqtimeout_filter_name, reqtimeout_eor, NULL,
                              AP_FTYPE_CONNECTION);

    /*
     * mod_reqtimeout needs to be called before ap_process_http_request (which
     * is run at APR_HOOK_REALLY_LAST) but after all other protocol modules.
     * This ensures that it only influences normal http connections and not
     * e.g. mod_ftp. Also, if mod_reqtimeout used the pre_connection hook, it
     * would be inserted on mod_proxy's backend connections.
     */
    ap_hook_process_connection(reqtimeout_init, NULL, NULL, APR_HOOK_LAST);

    ap_hook_pre_read_request(reqtimeout_before_header, NULL, NULL,
                             APR_HOOK_MIDDLE);
    ap_hook_post_read_request(reqtimeout_before_body, NULL, NULL,
                              APR_HOOK_MIDDLE);

#if MRT_DEFAULT_HEADER_MIN_RATE > 0
    default_header_rate_factor = apr_time_from_sec(1) / MRT_DEFAULT_HEADER_MIN_RATE;
#endif
#if MRT_DEFAULT_BODY_MIN_RATE > 0
    default_body_rate_factor = apr_time_from_sec(1) / MRT_DEFAULT_BODY_MIN_RATE;
#endif
}