                              sc->vhost_id_len);

    if (!SSL_set_session_id_context(ssl, (unsigned char *)vhost_md5,
                                    APR_MD5_DIGESTSIZE*2))
    {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
                      "Unable to set session id context to `%s'", vhost_md5);
        ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, server);

        c->aborted = 1;

        return DECLINED; /* XXX */
    }

    SSL_set_app_data(ssl, c);
    SSL_set_app_data2(ssl, NULL); /* will be request_rec */

    sslconn->ssl = ssl;

    SSL_set_verify_result(ssl, X509_V_OK);

    ssl_io_filter_init(c, ssl);

    return APR_SUCCESS;
}

static const char *ssl_hook_http_scheme(const request_rec *r)
{
