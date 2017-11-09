int h2_allows_h2_upgrade(conn_rec *c)
{
    const h2_config *cfg = h2_config_get(c);
    int h2_upgrade = h2_config_geti(cfg, H2_CONF_UPGRADE);
    
    return h2_upgrade > 0 || (h2_upgrade < 0 && !h2_h2_is_tls(c));
}