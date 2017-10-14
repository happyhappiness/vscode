ap_log_error( APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(03090)
                 "mod_http2 (v%s, feats=%s%s%s, nghttp2 %s), initializing...",
                 MOD_HTTP2_VERSION, 
                 myfeats.change_prio? "CHPRIO"  : "", 
                 myfeats.sha256?      "+SHA256" : "",
                 myfeats.inv_headers? "+INVHD"  : "",
                 ngh2?                ngh2->version_str : "unknown");