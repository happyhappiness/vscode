int h2_allows_h2_direct(conn_rec *c)
{
    const h2_config *cfg = h2_config_get(c);
    int h2_direct = h2_config_geti(cfg, H2_CONF_DIRECT);
    
    if (h2_direct < 0) {
        if (h2_h2_is_tls(c)) {
            /* disabled by default on TLS */
            h2_direct = 0;
        }
        else {
            /* enabled if "Protocols h2c" is configured */
            h2_direct = ap_is_allowed_protocol(c, NULL, NULL, "h2c");
        }
    }
    return !!h2_direct;
}