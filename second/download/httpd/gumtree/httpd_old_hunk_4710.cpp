{
    int proposed = 0;
    int is_tls = h2_h2_is_tls(c);
    const char **protos = is_tls? h2_tls_protos : h2_clear_protos;
    
    (void)s;
    if (strcmp(AP_PROTOCOL_HTTP1, ap_get_protocol(c))) {
        /* We do not know how to switch from anything else but http/1.1.
         */
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(03083)
                      "protocol switch: current proto != http/1.1, declined");
        return DECLINED;
