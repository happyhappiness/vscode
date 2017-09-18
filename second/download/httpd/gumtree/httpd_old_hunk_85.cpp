    if (reqinfo) {
        if (reqinfo->output_ctx && !configured_on_output(r, XLATEOUT_FILTER_NAME)) {
            ap_add_output_filter(XLATEOUT_FILTER_NAME, reqinfo->output_ctx, r, 
                                 r->connection);
        }
        else if (dc->debug >= DBGLVL_FLOW) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r,
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
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r,
                          "xlate input filter not added implicitly because %s",
                          !reqinfo->input_ctx ?
                          "no input configuration available" :
                          "another module added the filter");
        }
    }
