
    return ret;
}

void ssl_io_filter_init(conn_rec *c, SSL *ssl)
{
    SSLFilterRec *filter;

    filter = apr_palloc(c->pool, sizeof(SSLFilterRec));

    filter->pOutputFilter   = ap_add_output_filter(ssl_io_filter,
                                                   filter, NULL, c);
