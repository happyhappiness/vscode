void ssl_io_filter_register(apr_pool_t *p)
{
    /* This filter MUST be after the HTTP_HEADER filter, but it also must be
     * a resource-level filter so it has the request_rec.
     */
    ap_register_output_filter ("UPGRADE_FILTER", ssl_io_filter_Upgrade, NULL, AP_FTYPE_PROTOCOL + 5);

    ap_register_input_filter  (ssl_io_filter, ssl_io_filter_input,  NULL, AP_FTYPE_CONNECTION + 5);
    ap_register_output_filter (ssl_io_filter, ssl_io_filter_output, NULL, AP_FTYPE_CONNECTION + 5);

    ap_register_input_filter  (ssl_io_buffer, ssl_io_filter_buffer, NULL, AP_FTYPE_PROTOCOL - 1);

    return;
}