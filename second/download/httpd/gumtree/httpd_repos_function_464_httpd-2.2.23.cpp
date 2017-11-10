static int logio_transaction(request_rec *r)
{
    logio_config_t *cf = ap_get_module_config(r->connection->conn_config,
                                              &logio_module);

    cf->bytes_in = cf->bytes_out = 0;

    return OK;
}