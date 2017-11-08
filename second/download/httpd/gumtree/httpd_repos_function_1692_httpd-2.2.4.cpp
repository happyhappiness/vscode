int ssl_proxy_enable(conn_rec *c)
{
    apr_table_set(c->notes, "nwconv-ssl", "Y");

    return 1;
}