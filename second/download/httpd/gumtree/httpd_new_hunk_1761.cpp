        apr_cpystrn(buf+strlen(buf), " ", sizeof(buf)-strlen(buf));
        for (j = 0; j < DUMP_WIDTH; j++) {
            if (((i * DUMP_WIDTH) + j) >= len)
                apr_cpystrn(buf+strlen(buf), " ", sizeof(buf)-strlen(buf));
            else {
                ch = ((unsigned char)*((char *)(s) + i * DUMP_WIDTH + j)) & 0xff;
#if APR_CHARSET_EBCDIC
                apr_snprintf(tmp, sizeof(tmp), "%c", (ch >= 0x20 && ch <= 0x7F) ? ebcdic_text[j] : '.');
#else /* APR_CHARSET_EBCDIC */
                apr_snprintf(tmp, sizeof(tmp), "%c", ((ch >= ' ') && (ch <= '~')) ? ch : '.');
#endif /* APR_CHARSET_EBCDIC */
                apr_cpystrn(buf+strlen(buf), tmp, sizeof(buf)-strlen(buf));
            }
        }
        apr_cpystrn(buf+strlen(buf), " |", sizeof(buf)-strlen(buf));
        ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, srvr,
                     "%s", buf);
    }
    if (trunc > 0)
        ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, srvr,
                "| %04ld - <SPACES/NULS>", len + trunc);
    ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, srvr,
            "+-------------------------------------------------------------------------+");
    return;
}

long ssl_io_data_cb(BIO *bio, int cmd,
                    MODSSL_BIO_CB_ARG_TYPE *argp,
                    int argi, long argl, long rc)
{
    SSL *ssl;
    conn_rec *c;
    server_rec *s;
    SSLSrvConfigRec *sc;

    if ((ssl = (SSL *)BIO_get_callback_arg(bio)) == NULL)
        return rc;
    if ((c = (conn_rec *)SSL_get_app_data(ssl)) == NULL)
        return rc;
    s = mySrvFromConn(c);
    sc = mySrvConfig(s);

    if (   cmd == (BIO_CB_WRITE|BIO_CB_RETURN)
        || cmd == (BIO_CB_READ |BIO_CB_RETURN) ) {
        if (rc >= 0) {
            ap_log_error(APLOG_MARK, APLOG_TRACE4, 0, s,
                    "%s: %s %ld/%d bytes %s BIO#%pp [mem: %pp] %s",
                    SSL_LIBRARY_NAME,
                    (cmd == (BIO_CB_WRITE|BIO_CB_RETURN) ? "write" : "read"),
                    rc, argi, (cmd == (BIO_CB_WRITE|BIO_CB_RETURN) ? "to" : "from"),
                    bio, argp,
                    (argp != NULL ? "(BIO dump follows)" : "(Oops, no memory buffer?)"));
            if ((argp != NULL) && APLOGctrace7(c))
                ssl_io_data_dump(s, argp, rc);
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_TRACE4, 0, s,
                    "%s: I/O error, %d bytes expected to %s on BIO#%pp [mem: %pp]",
                    SSL_LIBRARY_NAME, argi,
                    (cmd == (BIO_CB_WRITE|BIO_CB_RETURN) ? "write" : "read"),
                    bio, argp);
        }
    }
