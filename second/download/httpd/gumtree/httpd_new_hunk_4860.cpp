    include_server_config *sconf= ap_get_module_config(r->server->module_config,
                                                       &include_module);

    if (!(ap_allow_options(r) & OPT_INCLUDES)) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01374)
                      "mod_include: Options +Includes (or IncludesNoExec) "
                      "wasn't set, INCLUDES filter removed: %s", r->uri);
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, b);
    }

    if (!f->ctx) {
        struct ssi_internal_ctx *intern;
