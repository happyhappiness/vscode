
    return ret;
}

void ssl_io_filter_init(conn_rec *c, SSL *ssl)
{
    SSLSrvConfigRec *sc = mySrvConfig(c->base_server);
    SSLFilterRec *filter;

    filter = apr_palloc(c->pool, sizeof(SSLFilterRec));

    filter->pOutputFilter   = ap_add_output_filter(ssl_io_filter,
                                                   filter, NULL, c);
