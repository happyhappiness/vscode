long ssl_io_data_cb(BIO *bio, int cmd,
                    const char *argp,
                    int argi, long argl, long rc)
{
    SSL *ssl;
    conn_rec *c;
    server_rec *s;

    if ((ssl = (SSL *)BIO_get_callback_arg(bio)) == NULL)
        return rc;
    if ((c = (conn_rec *)SSL_get_app_data(ssl)) == NULL)
        return rc;
    s = mySrvFromConn(c);

    if (   cmd == (BIO_CB_WRITE|BIO_CB_RETURN)
        || cmd == (BIO_CB_READ |BIO_CB_RETURN) ) {
        if (rc >= 0) {
            ap_log_cserror(APLOG_MARK, APLOG_TRACE4, 0, c, s,
                    "%s: %s %ld/%d bytes %s BIO#%pp [mem: %pp] %s",
                    MODSSL_LIBRARY_NAME,
                    (cmd == (BIO_CB_WRITE|BIO_CB_RETURN) ? "write" : "read"),
                    rc, argi, (cmd == (BIO_CB_WRITE|BIO_CB_RETURN) ? "to" : "from"),
                    bio, argp,
                    (argp != NULL ? "(BIO dump follows)" : "(Oops, no memory buffer?)"));
            if ((argp != NULL) && APLOG_CS_IS_LEVEL(c, s, APLOG_TRACE7))
                ssl_io_data_dump(s, argp, rc);
        }
        else {
            ap_log_cserror(APLOG_MARK, APLOG_TRACE4, 0, c, s,
                    "%s: I/O error, %d bytes expected to %s on BIO#%pp [mem: %pp]",
                    MODSSL_LIBRARY_NAME, argi,
                    (cmd == (BIO_CB_WRITE|BIO_CB_RETURN) ? "write" : "read"),
                    bio, argp);
        }
    }
    return rc;
}