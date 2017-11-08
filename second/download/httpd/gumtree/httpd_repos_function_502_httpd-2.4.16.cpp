static const char *log_ttfb(request_rec *r, char *a)
{
    logio_config_t *cf = ap_get_module_config(r->connection->conn_config,
                                              &logio_module);

    if (!cf->first_byte_seen || !cf->ttfb) { 
        return "-";
    }

    return apr_psprintf(r->pool, "%" APR_TIME_T_FMT, cf->ttfb);
}