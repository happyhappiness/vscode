int h2_allows_h2_direct(conn_rec *c)
{
    const h2_config *cfg = h2_config_get(c);
    int is_tls = h2_h2_is_tls(c);
    const char *needed_protocol = is_tls? "h2" : "h2c";
    int h2_direct = h2_config_geti(cfg, H2_CONF_DIRECT);
    
    if (h2_direct < 0) {
        h2_direct = is_tls? 0 : 1;
    }
    return (h2_direct 
            && ap_is_allowed_protocol(c, NULL, NULL, needed_protocol));
}