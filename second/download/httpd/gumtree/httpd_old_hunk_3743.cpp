            len = -1;
            apr_brigade_length(bb, 0, &len);
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02440)
                          "read %" APR_OFF_T_FMT
                          " bytes from %s", len, name);
#endif
            rv = ap_pass_brigade(c_o->output_filters, bb);
            if (rv == APR_SUCCESS) {
                ap_fflush(c_o->output_filters, bb);
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(02441)
