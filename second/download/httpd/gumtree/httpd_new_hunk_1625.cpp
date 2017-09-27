    if (length > 0)
        cf->bytes_in += length;

    return status;
}

/*
 * The hooks...
 */

static int logio_pre_conn(conn_rec *c, void *csd) {
    logio_config_t *cf = apr_pcalloc(c->pool, sizeof(*cf));

    ap_set_module_config(c->conn_config, &logio_module, cf);

    ap_add_input_filter(logio_filter_name, NULL, NULL, c);

    return OK;
}

static int logio_pre_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp)
{
