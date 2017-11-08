static int open_multi_logs(server_rec *s, apr_pool_t *p)
{
    int i;
    multi_log_state *mls = ap_get_module_config(s->module_config,
                                             &log_config_module);
    config_log_state *clsarray;
    const char *dummy;
    const char *format;

    if (mls->default_format_string) {
        format = apr_table_get(mls->formats, mls->default_format_string);
        if (format) {
            mls->default_format = parse_log_string(p, format, &dummy);
        }
    }

    if (!mls->default_format) {
        mls->default_format = parse_log_string(p, DEFAULT_LOG_FORMAT, &dummy);
    }

    if (mls->config_logs->nelts) {
        clsarray = (config_log_state *) mls->config_logs->elts;
        for (i = 0; i < mls->config_logs->nelts; ++i) {
            config_log_state *cls = &clsarray[i];

            if (cls->format_string) {
                format = apr_table_get(mls->formats, cls->format_string);
                if (format) {
                    cls->format = parse_log_string(p, format, &dummy);
                }
            }

            if (!open_config_log(s, p, cls, mls->default_format)) {
                /* Failure already logged by open_config_log */
                return DONE;
            }
        }
    }
    else if (mls->server_config_logs) {
        clsarray = (config_log_state *) mls->server_config_logs->elts;
        for (i = 0; i < mls->server_config_logs->nelts; ++i) {
            config_log_state *cls = &clsarray[i];

            if (cls->format_string) {
                format = apr_table_get(mls->formats, cls->format_string);
                if (format) {
                    cls->format = parse_log_string(p, format, &dummy);
                }
            }

            if (!open_config_log(s, p, cls, mls->default_format)) {
                /* Failure already logged by open_config_log */
                return DONE;
            }
        }
    }

    return OK;
}