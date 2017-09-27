    if (length > 0)
        cf->bytes_in += length;

    return status;
}

static apr_status_t logio_out_filter(ap_filter_t *f,
                                     apr_bucket_brigade *bb) {
    apr_bucket *b = APR_BRIGADE_LAST(bb);

    /* End of data, make sure we flush */
    if (APR_BUCKET_IS_EOS(b)) {
        APR_BUCKET_INSERT_BEFORE(b,
                                 apr_bucket_flush_create(f->c->bucket_alloc));
    }

    return ap_pass_brigade(f->next, bb);
}

/*
 * The hooks...
 */

static int logio_pre_conn(conn_rec *c, void *csd) {
    logio_config_t *cf = apr_pcalloc(c->pool, sizeof(*cf));

    ap_set_module_config(c->conn_config, &logio_module, cf);

    ap_add_input_filter(logio_filter_name, NULL, NULL, c);
    ap_add_output_filter(logio_filter_name, NULL, NULL, c);

    return OK;
}

static int logio_pre_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp)
{
