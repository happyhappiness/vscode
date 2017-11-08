static int logio_post_read_request(request_rec *r)
{
    logio_config_t *cf = ap_get_module_config(r->connection->conn_config,
                                              &logio_module);
    if (cf) { 
        cf->r = r;
    }
    return OK;
}