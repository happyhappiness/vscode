int h2_tls_disable(conn_rec *c)
{
    if (opt_ssl_engine_disable) {
        return opt_ssl_engine_disable(c);
    }
    return 0;
}