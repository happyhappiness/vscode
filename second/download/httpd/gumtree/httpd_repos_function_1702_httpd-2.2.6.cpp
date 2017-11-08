static int ssl_is_https(conn_rec *c)
{
    secsocket_data *csd_data = (secsocket_data*)ap_get_module_config(c->conn_config, &nwssl_module);

    return isSecureConn (c->base_server, c) || (csd_data && csd_data->is_secure);
}