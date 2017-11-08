apr_int64_t h2_config_geti64(const h2_config *conf, h2_config_var_t var)
{
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
        case H2_CONF_MODERN_TLS_ONLY:
            return H2_CONFIG_GET(conf, &defconf, modern_tls_only);
        case H2_CONF_UPGRADE:
            return H2_CONFIG_GET(conf, &defconf, h2_upgrade);
        case H2_CONF_DIRECT:
            return H2_CONFIG_GET(conf, &defconf, h2_direct);
        case H2_CONF_SESSION_FILES:
            return H2_CONFIG_GET(conf, &defconf, session_extra_files);
        case H2_CONF_TLS_WARMUP_SIZE:
            return H2_CONFIG_GET(conf, &defconf, tls_warmup_size);
        case H2_CONF_TLS_COOLDOWN_SECS:
            return H2_CONFIG_GET(conf, &defconf, tls_cooldown_secs);
        case H2_CONF_PUSH:
            return H2_CONFIG_GET(conf, &defconf, h2_push);
        case H2_CONF_PUSH_DIARY_SIZE:
            return H2_CONFIG_GET(conf, &defconf, push_diary_size);
        case H2_CONF_COPY_FILES:
            return H2_CONFIG_GET(conf, &defconf, copy_files);
        case H2_CONF_EARLY_HINTS:
            return H2_CONFIG_GET(conf, &defconf, early_hints);
        default:
            return DEF_VAL;
    }
}