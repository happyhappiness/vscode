    /* Hey... don't be so quick to use reqinfo->dc here; reqinfo may be NULL */
    charset_req_t *reqinfo = ap_get_module_config(r->request_config,
                                                  &charset_lite_module);
    charset_dir_t *dc = ap_get_module_config(r->per_dir_config,
                                             &charset_lite_module);

    if (reqinfo) {
        if (reqinfo->output_ctx && !configured_on_output(r, XLATEOUT_FILTER_NAME)) {
            ap_add_output_filter(XLATEOUT_FILTER_NAME, reqinfo->output_ctx, r,
                                 r->connection);
        }
        else if (dc->debug >= DBGLVL_FLOW) {
