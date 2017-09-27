    const char **protos = is_tls? h2_tls_protos : h2_clear_protos;
    
    (void)s;
    if (strcmp(AP_PROTOCOL_HTTP1, ap_get_protocol(c))) {
        /* We do not know how to switch from anything else but http/1.1.
         */
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                      "protocol switch: current proto != http/1.1, declined");
        return DECLINED;
    }
    
    if (!h2_is_acceptable_connection(c, 0)) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                      "protocol propose: connection requirements not met");
        return DECLINED;
    }
    
    if (r) {
        /* So far, this indicates an HTTP/1 Upgrade header initiated
