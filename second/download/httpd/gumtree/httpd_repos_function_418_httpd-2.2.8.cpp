static void *merge_config_log_state(apr_pool_t *p, void *basev, void *addv)
{
    multi_log_state *base = (multi_log_state *) basev;
    multi_log_state *add = (multi_log_state *) addv;

    add->server_config_logs = base->config_logs;
    if (!add->default_format) {
        add->default_format_string = base->default_format_string;
        add->default_format = base->default_format;
    }
    add->formats = apr_table_overlay(p, base->formats, add->formats);

    return add;
}