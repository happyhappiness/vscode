static void xlate_insert_filter(request_rec *r)
{
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
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "xlate output filter not added implicitly because %s",
                          !reqinfo->output_ctx ?
                          "no output configuration available" :
                          "another module added the filter");
        }

        if (reqinfo->input_ctx && !configured_on_input(r, XLATEIN_FILTER_NAME)) {
            ap_add_input_filter(XLATEIN_FILTER_NAME, reqinfo->input_ctx, r,
                                r->connection);
        }
        else if (dc->debug >= DBGLVL_FLOW) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "xlate input filter not added implicitly because %s",
                          !reqinfo->input_ctx ?
                          "no input configuration available" :
                          "another module added the filter");
        }
    }
}