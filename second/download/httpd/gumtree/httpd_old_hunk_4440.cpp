    }
    
    ngh2 = nghttp2_version(0);
    ap_log_error( APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(03090)
                 "mod_http2 (v%s, feats=%s%s%s, nghttp2 %s), initializing...",
                 MOD_HTTP2_VERSION, 
                 myfeats.change_prio? "CHPRIO" : "", sep, 
                 myfeats.sha256?      "SHA256" : "",
                 ngh2?                ngh2->version_str : "unknown");
    
    switch (h2_conn_mpm_type()) {
        case H2_MPM_SIMPLE:
        case H2_MPM_MOTORZ:
        case H2_MPM_NETWARE:
