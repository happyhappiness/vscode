void
commStartSslClose(const FdeCbParams &params)
{
    assert(&fd_table[params.fd].ssl);
    ssl_shutdown_method(fd_table[params.fd].ssl);
}