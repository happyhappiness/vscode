int ssl_proxy_enable(conn_rec *c)
{
    apr_table_setn(c->notes, "nwconv-ssl", "Y");

    return 1;
}