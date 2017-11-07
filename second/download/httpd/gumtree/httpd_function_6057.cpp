void h2_task_register_hooks(void)
{
    /* This hook runs on new connections before mod_ssl has a say.
     * Its purpose is to prevent mod_ssl from touching our pseudo-connections
     * for streams.
     */
    ap_hook_pre_connection(h2_task_pre_conn,
                           NULL, mod_ssl, APR_HOOK_FIRST);
    /* When the connection processing actually starts, we might 
     * take over, if the connection is for a task.
     */
    ap_hook_process_connection(h2_task_process_conn, 
                               NULL, NULL, APR_HOOK_FIRST);

    ap_register_input_filter("H2_SLAVE_IN", h2_filter_slave_in,
                             NULL, AP_FTYPE_NETWORK);
    ap_register_output_filter("H2_SLAVE_OUT", h2_filter_slave_output,
                              NULL, AP_FTYPE_NETWORK);
    ap_register_output_filter("H2_PARSE_H1", h2_filter_parse_h1,
                              NULL, AP_FTYPE_NETWORK);

    ap_register_input_filter("H2_REQUEST", h2_filter_request_in,
                             NULL, AP_FTYPE_PROTOCOL);
    ap_register_output_filter("H2_RESPONSE", h2_filter_headers_out,
                              NULL, AP_FTYPE_PROTOCOL);
    ap_register_output_filter("H2_TRAILERS_OUT", h2_filter_trailers_out,
                              NULL, AP_FTYPE_PROTOCOL);
}