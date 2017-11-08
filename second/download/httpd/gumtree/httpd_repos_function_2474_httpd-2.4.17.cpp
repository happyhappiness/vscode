int h2_config_geti(h2_config *conf, h2_config_var_t var)
{
    int n;
    switch(var) {
        case H2_CONF_MAX_STREAMS:
            return H2_CONFIG_GET(conf, &defconf, h2_max_streams);
        case H2_CONF_WIN_SIZE:
            return H2_CONFIG_GET(conf, &defconf, h2_window_size);
        case H2_CONF_MIN_WORKERS:
            return H2_CONFIG_GET(conf, &defconf, min_workers);
        case H2_CONF_MAX_WORKERS:
            return H2_CONFIG_GET(conf, &defconf, max_workers);
        case H2_CONF_MAX_WORKER_IDLE_SECS:
            return H2_CONFIG_GET(conf, &defconf, max_worker_idle_secs);
        case H2_CONF_STREAM_MAX_MEM:
            return H2_CONFIG_GET(conf, &defconf, stream_max_mem_size);
        case H2_CONF_ALT_SVC_MAX_AGE:
            return H2_CONFIG_GET(conf, &defconf, alt_svc_max_age);
        case H2_CONF_SER_HEADERS:
            return H2_CONFIG_GET(conf, &defconf, serialize_headers);
        case H2_CONF_DIRECT:
            return H2_CONFIG_GET(conf, &defconf, h2_direct);
        case H2_CONF_SESSION_FILES:
            n = H2_CONFIG_GET(conf, &defconf, session_extra_files);
            if (n < 0) {
                n = files_per_session;
            }
            return n;
        default:
            return DEF_VAL;
    }
}