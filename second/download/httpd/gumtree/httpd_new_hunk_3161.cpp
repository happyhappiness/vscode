    ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, srvr,
            "+-------------------------------------------------------------------------+");
    return;
}

long ssl_io_data_cb(BIO *bio, int cmd,
                    const char *argp,
                    int argi, long argl, long rc)
{
    SSL *ssl;
    conn_rec *c;
    server_rec *s;

