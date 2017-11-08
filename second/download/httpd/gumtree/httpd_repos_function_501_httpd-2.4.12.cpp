static const char *log_bytes_combined(request_rec *r, char *a)
{
    logio_config_t *cf = ap_get_module_config(r->connection->conn_config,
                                              &logio_module);

    return apr_off_t_toa(r->pool, cf->bytes_out + cf->bytes_in);
}