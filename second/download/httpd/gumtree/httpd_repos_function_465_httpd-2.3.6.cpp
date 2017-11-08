static apr_off_t ap_logio_get_last_bytes(conn_rec *c)
{
    logio_config_t *cf = ap_get_module_config(c->conn_config, &logio_module);

    return cf->bytes_last_request;
}