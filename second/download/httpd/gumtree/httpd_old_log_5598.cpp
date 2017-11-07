ap_log_error( APLOG_MARK, APLOG_INFO, 0, s,
                 "mod_http2 (v%s, nghttp2 %s), initializing...",
                 MOD_HTTP2_VERSION, ngh2? ngh2->version_str : "unknown");