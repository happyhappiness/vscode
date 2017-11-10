static void ap_logio_add_bytes_out(conn_rec *c, apr_off_t bytes){
    logio_config_t *cf = ap_get_module_config(c->conn_config, &logio_module);

    cf->bytes_out += bytes;
}